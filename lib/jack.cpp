/*
    Copyright 2013-2015 Dario Casalinuovo. All rights reserved.

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

#include <ObjectList.h>

#include <String.h>
#include <MediaDefs.h>

#include "WrapperDefs.h"

#include "jack/jack.h"

#include "JackClient.h"
#include "JackPort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


JackClient*
FindClient(jack_client_t* cl) {
	JackClient* client = (JackClient*) cl;
	return client;
}

// General misc methods

LIB_EXPORT jack_nframes_t
jack_get_buffer_size (jack_client_t* cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	return client->BufferSize();
}


LIB_EXPORT jack_nframes_t
jack_get_sample_rate (jack_client_t* cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	printf("jack_get_sample_rate returns: %d\n", client->SampleRate());

	return client->SampleRate();
}

// jack client

LIB_EXPORT int
jack_activate (jack_client_t* cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	return client->Activate();
}


LIB_EXPORT int
jack_deactivate (jack_client_t* cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	return client->DeActivate();
}


LIB_EXPORT jack_client_t*
jack_client_open (const char* client_name,
	jack_options_t options,
	jack_status_t *status, ...)
{
	JackClient* client = new JackClient(client_name, options, status);
	client->Open();
	return client->Client();
}


LIB_EXPORT int
jack_client_close (jack_client_t *cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	client->DeActivate();

	int ret = client->Close();
	delete client;
	return ret;
}


LIB_EXPORT int
jack_client_name_size (void)
{
	return WRAPPER_CLIENT_NAME_SIZE;
}


LIB_EXPORT char*
jack_get_client_name (jack_client_t* cl)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return NULL;

	const char* nm = client->Name();
	char* name = (char*)malloc(strlen(nm));
	strcpy(name, nm);
	return name;
}


int
LIB_EXPORT jack_connect (jack_client_t* cl, const char *source_port,
	const char *destination_port)
{
	printf("connect %s %s\n", source_port, destination_port);

	JackClient* client = FindClient(cl);
	if (client == NULL)
		return NULL;

	return client->ConnectPorts(source_port, destination_port);
}


LIB_EXPORT void*
jack_port_get_buffer (jack_port_t* jackPort, jack_nframes_t frames)
{
	//printf("jack_port_get_buffer\n");
	JackPort* port = (JackPort*) jackPort;
	JackClient* client = port->Owner();

	return client->ReadBuffer(port, frames);
}


LIB_EXPORT jack_port_t*
jack_port_register (jack_client_t *cl,
	const char *port_name,
	const char *port_type,
	unsigned long flags,
	unsigned long buffer_size)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return NULL;

	return client->RegisterPort(port_name, port_type, flags, buffer_size);
}


LIB_EXPORT size_t
jack_port_type_get_buffer_size (jack_client_t *cl, const char *port_type)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return NULL;

	return client->SizeForPortType(port_type);
}


const char*
jack_port_name(const jack_port_t* port)
{
	JackPort* myPort = (JackPort*)port;
	if (myPort == NULL) {
		printf("port is NULL\n");
		return NULL;
	}

	BString str(myPort->Name());
	str.Prepend(":");
	str.Prepend(myPort->Owner()->Name());

	//printf("Port name is %s\n", str.String());

	return str.String();
}


LIB_EXPORT const char **
jack_get_ports (jack_client_t* cl, const char *port_name_pattern, 
	const char *type_name_pattern, unsigned long flags)
{
	printf("jack_get_ports\n");
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return NULL;

	return client->GetPorts(port_name_pattern, type_name_pattern, flags);
}

// Callbacks

LIB_EXPORT int
jack_set_process_callback (jack_client_t *cl,
	JackProcessCallback process_callback,
	void *arg)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	return client->SetProcessCallback(process_callback, arg);
}


LIB_EXPORT int
jack_set_buffer_size_callback (jack_client_t *cl,
	JackBufferSizeCallback bufsize_callback, void *arg)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return -1;

	return client->SetBufferSizeCallback(bufsize_callback, arg);
}


LIB_EXPORT void
jack_on_shutdown (jack_client_t *cl,
	JackShutdownCallback function, void *arg)
{
	JackClient* client = FindClient(cl);
	if (client == NULL)
		return;

	client->SetShutdownCallback(function, arg);
}
