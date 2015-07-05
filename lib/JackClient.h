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

#ifndef _HAIKU_JACK_CLIENT
#define _HAIKU_JACK_CLIENT

#include <Buffer.h>
#include <MediaRoster.h>
#include <String.h>

#include "ClientNode.h"
#include "JackPort.h"

#include "jack/jack.h"

class JackPort;
class ClientNode;

typedef BObjectList<JackPort> JackPortList;


template <class T>
struct CallbackContainer {
	T callback = 0;
	void* arg = NULL;
};

class JackClient
{
public:
						JackClient(const char* client_name,
							jack_options_t options,
							jack_status_t *status);

	virtual 				~JackClient();

	// Various hooks for the jack c api

	jack_nframes_t		BufferSize() const;
	jack_nframes_t		SampleRate() const;
	int					Activate();
	int 				DeActivate();
	const char*			Name() const;
	const char**		GetPorts(const char *port_name_pattern, 
							const char *type_name_pattern,
							unsigned long flags);

	int 				Open();
	int					Close();

	int					ConnectPorts(const char* source,
							const char* destination);

	// Ports
	jack_port_t*		RegisterPort(const char *port_name,
							const char *port_type,
							unsigned long flags,
							unsigned long buffer_size);

	void*				ReadBuffer(JackPort* port,
							jack_nframes_t frames);

	size_t				SizeForPortType(const char* port_type);

	// Callbacks
	int 				SetProcessCallback(
							JackProcessCallback process_callback,
							void *arg);

	int 				SetBufferSizeCallback(
							JackBufferSizeCallback bufsize_callback,
							void *arg);

	void				SetShutdownCallback(JackShutdownCallback function,
							void *arg);

	// BMediaNode callbacks

	JackPortList*		GetInputPorts() const;
	JackPortList*		GetOutputPorts() const;

	void				SetFormat(media_format format);
	status_t			Process(jack_nframes_t size);

	// Other utils
	status_t			ActivateNode();

	media_node			FindNativeNode(const char* jack_client);
	jack_client_t*		Client() const;

	bool				IsEqual(jack_client_t* cl) const;
	bool				IsEqual(JackClient* cl) const;

	bool				HasData() const;
	void				SetHasData(bool value);

	JackPort*			PortByName(const char* name);
	int32				CountPorts() const;

	bool				PortsReady() const;

private:
	live_node_info*		_LiveNodes(int32* live_count);
	static int32		ProcessThread(void* cookie);

	// Jack native client things
	jack_options_t		fOptions;
	jack_status_t*		fStatus;

	// wrap implementation internals
	BLocker*			fLock;
	const char*			fName;
	bool				fOpen;
	bool 				fActivated;
	BMediaRoster*		fRoster;
	ClientNode*			fClientNode;
	media_format		fFormat;
	thread_id			fProcessThread;
	bool				fHasData;

	// Ports
	JackPortList*		fInputPorts;
	JackPortList*		fOutputPorts;


	// Callbacks
	CallbackContainer<JackProcessCallback> 		fProcessCallback;
	CallbackContainer<JackBufferSizeCallback>	fBufferSizeCallback;
	CallbackContainer<JackShutdownCallback>		fShutdownCallback;
};

#endif
