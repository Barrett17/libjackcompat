/*
    Copyright 2013 Dario Casalinuovo. All rights reserved.

    This file is part of libjackcompat.

    libjackcompat is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libjackcompat is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libjackcompat.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "JackClient.h"

#include <Autolock.h>
#include <BufferGroup.h>
#include <MediaDefs.h>
#include <MediaEventLooper.h>
#include <String.h>
#include <TimeSource.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jack/jack.h"
#include "jack/types.h"


int32
JackClient::ProcessThread(void* cookie)
{
	while (1) {
		JackClient* client = (JackClient*) cookie;
		if (client->CountPorts() == 0)
			snooze(10000);

		if (client->CountPorts() != 0
			|| client->PortsReady()) {
			printf("The client is starting now\n");
			client->ActivateNode();
			return 0;
		}
		snooze(100);
	}
}


JackClient::JackClient(const char* client_name,
	jack_options_t options, jack_status_t *status)
	:
	fStatus(status),
	fOptions(options),
	fName(client_name)
{
	fInputPorts = new JackPortList(true);
	fOutputPorts = new JackPortList(true);

	fLock = new BLocker("JackClient lock");

	fRoster = BMediaRoster::Roster();
	fClientNode = NULL;
	fActivated = false;
	fOpen = false;
}


JackClient::~JackClient()
{
	if (fActivated)
		DeActivate();

	if (fOpen)
		Close();

	delete fInputPorts;
	delete fOutputPorts;
	delete fLock;
}


jack_client_t*
JackClient::Client() const
{
	return (jack_client_t*) this;
}


jack_nframes_t
JackClient::BufferSize() const
{
	return fFormat.u.raw_audio.buffer_size / sizeof(float);
}


jack_nframes_t
JackClient::SampleRate() const
{
	return (jack_nframes_t)fFormat.u.raw_audio.frame_rate;
}


int
JackClient::Open()
{
	BAutolock _(fLock);

	printf("JackClient::Open\n");

	if (fClientNode != NULL)
		delete fClientNode;

	fClientNode = new ClientNode(fName, this);

	status_t err = fRoster->RegisterNode(fClientNode);
	if (err != B_OK) {
		printf("%s\n", strerror(err));
		return -1;
	}

	fProcessThread = spawn_thread(ProcessThread,
		"memento audere semper", B_NORMAL_PRIORITY, this);

	if (fProcessThread < B_OK) {
  		printf("error spawning thread\n");
		return -1;
	}

	fOpen = true;
	return 0;
}


int
JackClient::Close()
{
	BAutolock _(fLock);

	printf("JackClient::Close\n");

	if (fClientNode != NULL
		&& fRoster->UnregisterNode(fClientNode) == B_OK) {

		delete fClientNode;
		fClientNode = NULL;

		fOpen = false;
		return 0;
	}
	return -1;
}



status_t
JackClient::ActivateNode()
{
	BAutolock _(fLock);

	printf("JackClient::ActivateNode\n");

	if (!fClientNode->TimeSource()->IsRunning()) {
		fRoster->StartTimeSource(fClientNode->TimeSource()->Node(),
			fClientNode->TimeSource()->RealTime());
	}

	status_t err = fRoster->StartNode(fClientNode->Node(),
		fClientNode->TimeSource()->Now());

	if (err != B_OK) {
		printf("%s\n", strerror(err));
		return err;
	}

	return B_OK;
}


int
JackClient::Activate()
{
	BAutolock _(fLock);

	printf("JackClient::Activate\n");
	if (!fOpen)
		return -1;

	if (fActivated == true)
		return 0;

	status_t err = resume_thread(fProcessThread);

	if (err != B_OK) {
		printf("%s\n", strerror(err));
		return -1;
	}

	fActivated = true;

	return 0;
}


int
JackClient::DeActivate()
{
	BAutolock _(fLock);

	printf("JackClient::DeActivate\n");
	if (fActivated == false)
		return 0;

	status_t err = fRoster->StopNode(fClientNode->Node(), 0, true);

	if (err != B_OK) {
		printf("%s\n", strerror(err));
		return -1;
	}

	fActivated = false;

	return 0;
}


const char*
JackClient::Name() const
{
	return fName;
}

// Ports

jack_port_t*
JackClient::RegisterPort(const char *port_name,
	const char *port_type, unsigned long flags,
	unsigned long buffer_size)
{
	BAutolock _(fLock);

	unsigned long size;

	if (buffer_size == 0) {
		if (strcmp(port_type, JACK_DEFAULT_AUDIO_TYPE) == 0) {
			size = fFormat.u.raw_audio.buffer_size;
		} else if (strcmp(port_type, JACK_DEFAULT_MIDI_TYPE) == 0) {
			// not supported atm
			return NULL;
		}
	} else
		size = buffer_size;

	JackPort* port = new JackPort(port_name, port_type,
		flags, size, this);

	if (flags & JackPortIsInput)
		fInputPorts->AddItem(port);
	else if (flags & JackPortIsOutput)
		fOutputPorts->AddItem(port);

	media_output* output = port->MediaOutput();
	output->node = fClientNode->Node();
	output->source.port = fClientNode->ControlPort();
	output->source.id = 0;
	output->destination = media_destination::null;
	output->format = fFormat;

	strcpy(output->name, jack_port_name((jack_port_t*)port));

	return (jack_port_t*) port;
}


void*
JackClient::ReadBuffer(JackPort* port,
	jack_nframes_t frames)
{
	if (port == NULL)
		return NULL;

	if (port->Owner()->IsEqual(this))
		return port->CurrentBuffer()->Data();


	return NULL;
}


size_t
JackClient::SizeForPortType(const char* port_type)
{
	if (strcmp(port_type, JACK_DEFAULT_AUDIO_TYPE) == 0) {
		return WRAPPER_PREFERRED_BUF_SIZE;
	} else if(strcmp(port_type, JACK_DEFAULT_MIDI_TYPE) == 0) {
		// NOTE completely arbitrary until midi is supported
		return 512;
	}
}


// Callbacks
int
JackClient::SetProcessCallback(JackProcessCallback process_callback,
	void *arg)
{
	fProcessCallback.callback = process_callback;
	fProcessCallback.arg = arg;

	return 0;
}


int
JackClient::SetBufferSizeCallback(JackBufferSizeCallback bufsize_callback,
		void *arg)
{
	fBufferSizeCallback.callback = bufsize_callback;
	fBufferSizeCallback.arg = arg;

	return 0;
}


void
JackClient::SetShutdownCallback(JackShutdownCallback function, void *arg)
{
	fShutdownCallback.callback = function;
	fShutdownCallback.arg = arg;
}

// Other utils and callbacks created for the media_node

JackPortList*
JackClient::GetInputPorts() const
{
	return fInputPorts;
}


JackPortList*
JackClient::GetOutputPorts() const
{
	return fOutputPorts;
}


const char**
JackClient::GetPorts(const char *port_name_pattern, 
	const char *type_name_pattern, unsigned long flags)
{
	BAutolock _(fLock);

	const char** jack_ports;
	jack_ports = (const char**)malloc(100);

	// add the virtual outputs so that
	// jack clients can connect to 
	// the system mixer in a painless way

	int i = 0;
	if (flags & JackPortIsInput
		&& flags & JackPortIsPhysical) {
		jack_ports[i] = "system:playback_1";
		jack_ports[++i] = "system:playback_2";
	}

	if (flags & JackPortIsOutput
		&& flags & JackPortIsPhysical) {
		jack_ports[++i] = "system:capture_1";
		jack_ports[++i] = "system:capture_2";
	}

	/*int32 live_count;
	live_node_info* live_nodes = _LiveNodes(&live_count);

	for (i < live_count; i++) {
		jack_ports[i] = live_nodes[i].name;
		printf("%s %d\n", live_nodes[i].name, i);
	}*/

	return (const char**)jack_ports;
}



status_t
JackClient::Process(jack_nframes_t size)
{
	BAutolock _(fLock);
	if (fOpen == false || fActivated == false)
		return B_ERROR;

	fProcessCallback.callback(size, fProcessCallback.arg);
	return B_OK;
}


int
JackClient::ConnectPorts(const char* source, const char* destination)
{
	BAutolock _(fLock);

	media_node sourceNode = FindNativeNode(source);
	media_node destNode = FindNativeNode(destination);

	JackPort* port = PortByName(source);

	if (port == NULL)
		printf("port is NULL\n");

	printf("%s\n", port->Name());
	media_source src(sourceNode.port, 0);
	media_format format;
	format.type = B_MEDIA_RAW_AUDIO;
	format.u.raw_audio.buffer_size = fFormat.u.raw_audio.buffer_size;
	format.u.raw_audio = media_raw_audio_format::wildcard;
	format.u.raw_audio.channel_count = 1;
	format.u.raw_audio.format = WRAPPER_PREFERRED_FORMAT;

	media_destination dest(destNode.port, 0);

	media_output* output = port->MediaOutput();
	output->node = sourceNode;
	output->source = src;
	output->destination = dest;
	output->format = format;
	strcpy(output->name, source);

	media_input* input = port->MediaInput();
	input->node = destNode;
	input->source = src;
	input->destination = dest;
	input->format = format;
	strcpy(input->name, destination);

	if (status_t ret = fRoster->Connect(src, dest, &format, output, input)
		!= B_OK) {
		printf("error connecting %s\n", strerror(ret));
		return -1;
	}

	port->SetConnected(true);

	return 0;
}


void
JackClient::SetFormat(media_format format)
{
	fFormat.SpecializeTo(&format);
}


bool
JackClient::IsEqual(jack_client_t* cl) const
{
	JackClient* client = (JackClient*) cl;
	return IsEqual(client);
}


bool
JackClient::IsEqual(JackClient* client) const
{
	return fClientNode->ID() == client->fClientNode->ID();
}


bool
JackClient::PortsReady() const
{
	BAutolock _(fLock);

	if(!fOpen && !fActivated)
		return false;

	JackPortList* lst = GetOutputPorts();
	for (int i = 0; i < lst->CountItems(); i++) {
		JackPort* port = lst->ItemAt(i);
		if (!port->IsConnected())
			return false;
	}

	lst = GetInputPorts();
	for (int i = 0; i < lst->CountItems(); i++) {
		JackPort* port = lst->ItemAt(i);
		if (!port->IsConnected())
			return false;
	}

	return true;
}


bool
JackClient::HasData() const
{
	if(!fOpen && !fActivated)
		return false;

	return fHasData;
}


void
JackClient::SetHasData(bool value)
{
	fHasData = value;
}


live_node_info*
JackClient::_LiveNodes(int32* live_count)
{
	BMediaRoster* roster = BMediaRoster::Roster();

	// TODO set autodeleter to live_nodes
	live_node_info* live_nodes = (live_node_info*) malloc(100);
	int32 count;

	media_format outFormat;
	memset(&outFormat, 0, sizeof(outFormat));
	outFormat.type = B_MEDIA_RAW_AUDIO;

	media_format inFormat;
	memset(&inFormat, 0, sizeof(inFormat));
	inFormat.type = B_MEDIA_RAW_AUDIO;

	status_t err = roster->GetLiveNodes(live_nodes, &count,
		&inFormat, &outFormat, NULL, 0);

	if (err != B_OK)
		return NULL;

	*live_count = count;
	return live_nodes;
}


media_node
JackClient::FindNativeNode(const char* jack_client)
{

	media_node ret;
	BString sourceName(jack_client);
	if (sourceName.FindFirst(Name()) == 0) {
		// We are the client
		return fClientNode->Node();
	}

	if (strcmp(jack_client, "system:playback_1") == 0
		|| strcmp(jack_client, "system:playback_2") == 0
		|| strcmp(jack_client, "system:capture_1") == 0
		|| strcmp(jack_client, "system:capture_2") == 0) {

		fRoster->GetAudioMixer(&ret);

	} else {
		// This is not a banal case, find the native node
		int32 live_count;
		live_node_info* nativeNodes = _LiveNodes(&live_count);

		for (int i = 0; i < live_count; i++) {
			if (sourceName.FindFirst(nativeNodes[i].name) == 0) {
				return nativeNodes[i].node;
			}
		}
	}

	return ret;
}


JackPort*
JackClient::PortByName(const char* name)
{
	JackPort* port;
	JackPortList* lst = GetOutputPorts();
	for (int i = 0; i < lst->CountItems(); i++) {
		port = lst->ItemAt(i);
		BString str(name);
		if (str.Compare(jack_port_name((jack_port_t*)port)) == 0)
			return port;
	}

	return NULL;
}


int32
JackClient::CountPorts() const
{
	return fInputPorts->CountItems() + fOutputPorts->CountItems();
}
