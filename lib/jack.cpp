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

#include "jack/jack.h"

#include <ObjectList.h>

#include <String.h>
#include <MediaDefs.h>

#include "JackClient.h"
#include "JackPort.h"
#include "WrapperDefs.h"

#include <stdlib.h>
#include <string.h>


JackClient*
FindClient(jack_client_t* client)
{
	return (JackClient*)client;
}


LIB_EXPORT int
jack_set_buffer_size(jack_client_t* client, jack_nframes_t frames)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT float
jack_cpu_load(jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_is_realtime(jack_client_t* client)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT jack_nframes_t
jack_thread_wait(jack_client_t* client, int status)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT jack_nframes_t
jack_cycle_wait(jack_client_t* client)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT void
jack_cycle_signal(jack_client_t* client, int status)
{
	UNIMPLEMENTED();
}

// General misc methods

LIB_EXPORT jack_nframes_t
jack_get_buffer_size(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	return cp->BufferSize();
}


LIB_EXPORT jack_nframes_t
jack_get_sample_rate(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	TRACE("jack_get_sample_rate returns: %d\n", cp->SampleRate());

	return cp->SampleRate();
}

// jack client

LIB_EXPORT int
jack_activate(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	return cp->Activate();
}


LIB_EXPORT int
jack_deactivate(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	return cp->DeActivate();
}


LIB_EXPORT jack_client_t*
jack_client_open(const char* name,
	jack_options_t options, jack_status_t* status, ...)
{
	CALLED();

	JackClient* client = new JackClient(name, options, status);
	client->Open();
	return client->Client();
}


LIB_EXPORT int
jack_client_close(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	cp->DeActivate();

	int ret = cp->Close();
	delete cp;
	return ret;
}


LIB_EXPORT jack_native_thread_t
jack_client_thread_id(jack_client_t* client)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_client_name_size(void)
{
	CALLED();

	return WRAPPER_CLIENT_NAME_SIZE;
}


LIB_EXPORT char*
jack_get_client_name(jack_client_t* client)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return NULL;

	const char* nm = cp->Name();
	char* name = (char*)malloc(strlen(nm));
	strcpy(name, nm);
	return name;
}


LIB_EXPORT int
jack_get_client_pid(const char* name)
{
	UNIMPLEMENTED();

	return -1;
}


int
LIB_EXPORT jack_connect(jack_client_t* client, const char* source,
	const char* destination)
{
	CALLED();
	TRACE("Connect %s %s\n", source, destination);

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return NULL;

	return cp->ConnectPorts(source, destination);
}


LIB_EXPORT void*
jack_port_get_buffer(jack_port_t* port, jack_nframes_t frames)
{
	CALLED();

	JackPort* jack_port = (JackPort*) port;
	JackClient* client = jack_port->Owner();
	return client->ReadBuffer(jack_port, frames);
}


LIB_EXPORT jack_port_t*
jack_port_register(jack_client_t* client,
	const char* name, const char* type,
	unsigned long flags, unsigned long size)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return NULL;

	return cp->RegisterPort(name, type, flags, size);
}


LIB_EXPORT size_t
jack_port_type_get_buffer_size(jack_client_t* client,
	const char* type)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return NULL;

	return cp->SizeForPortType(type);
}


const char*
jack_port_name(const jack_port_t* port)
{
	CALLED();

	JackPort* myPort = (JackPort*)port;
	if (myPort == NULL) {
		ERROR("port is NULL\n");
		return NULL;
	}

	BString str(myPort->Name());
	str.Prepend(":");
	str.Prepend(myPort->Owner()->Name());

	TRACE("Port name is %s\n", str.String());

	return str.String();
}


LIB_EXPORT const char**
jack_get_ports(jack_client_t* client, const char* port_pattern, 
	const char* type_pattern, unsigned long flags)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return NULL;

	return cp->GetPorts(port_pattern, type_pattern, flags);
}


LIB_EXPORT int
jack_port_unregister(jack_client_t* client, jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT const char*
jack_port_short_name(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT int
jack_port_flags(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT const char*
jack_port_type(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT jack_port_type_id_t
jack_port_type_id(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_is_mine(const jack_client_t* client, const jack_port_t* port)
{
	UNIMPLEMENTED();
	return 0;
}


LIB_EXPORT int
jack_port_connected(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_connected_to(const jack_port_t* port, const char* port_name)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT const char**
jack_port_get_connections(const jack_port_t* port)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT const char**
jack_port_get_all_connections(const jack_client_t* client,
	const jack_port_t* port)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT int
jack_port_set_name(jack_port_t* port, const char* name)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_set_alias(jack_port_t* port, const char* alias)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_unset_alias(jack_port_t* port, const char* alias)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_get_aliases(const jack_port_t* port, char* const aliases[2])
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_request_monitor(jack_port_t* port, int value)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_request_monitor_by_name(jack_client_t* client,
	const char* name, int value)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_ensure_monitor(jack_port_t* port, int value)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_monitoring_input(jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_disconnect(jack_client_t* client, const char* source,
	const char* destination)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_disconnect(jack_client_t* client, jack_port_t* port)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_name_size(void)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_port_type_size(void)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT size_t
jack_port_type_get_buffer_size(jack_client_t* client,
	const char* type)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_port_get_latency_range(jack_port_t* port,
	jack_latency_callback_mode_t mode,
	jack_latency_range_t* range)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_port_set_latency_range(jack_port_t* port,
	jack_latency_callback_mode_t mode, jack_latency_range_t* range)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_recompute_total_latencies(jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_port_t*
jack_port_by_name(jack_client_t* client, const char* name)
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT jack_port_t*
jack_port_by_id(jack_client_t* client, jack_port_id_t id)
{
	UNIMPLEMENTED();
	return NULL;
}

// Callbacks

LIB_EXPORT int
jack_set_process_thread(jack_client_t* client,
	JackThreadCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}



LIB_EXPORT int
jack_set_thread_init_callback(jack_client_t* client,
	JackThreadInitCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_on_info_shutdown(jack_client_t* client,
	JackInfoShutdownCallback callback, void* cookie)
{
	UNIMPLEMENTED();
}


LIB_EXPORT int
jack_set_freewheel_callback(jack_client_t* client,
	JackFreewheelCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_sample_rate_callback(jack_client_t* client,
	JackSampleRateCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_client_registration_callback(jack_client_t* client,
	JackClientRegistrationCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_port_registration_callback(jack_client_t* client,
	JackPortRegistrationCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_port_connect_callback(jack_client_t* client,
	JackPortConnectCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_port_rename_callback(jack_client_t* client,
	JackPortRenameCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}

s
LIB_EXPORT int
jack_set_graph_order_callback(jack_client_t* client,
	JackGraphOrderCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_xrun_callback(jack_client_t* client,
	JackXRunCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_latency_callback(jack_client_t* client,
	JackLatencyCallback callback, void* cookie)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_set_process_callback(jack_client_t* client,
	JackProcessCallback callback, void* argument)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	return cp->SetProcessCallback(callback, argument);
}


LIB_EXPORT int
jack_set_buffer_size_callback(jack_client_t* client,
	JackBufferSizeCallback callback, void* argument)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return -1;

	return cp->SetBufferSizeCallback(callback, argument);
}


LIB_EXPORT void
jack_on_shutdown(jack_client_t* client,
	JackShutdownCallback callback, void* arg)
{
	CALLED();

	JackClient* cp = FindClient(client);
	if (cp == NULL)
		return;

	cp->SetShutdownCallback(callback, argument);
}


LIB_EXPORT jack_nframes_t
jack_frames_since_cycle_start(const jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_nframes_t
jack_frame_time(const jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_nframes_t
jack_last_frame_time(const jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_get_cycle_times(const jack_client_t* client,
	jack_nframes_t* frames, jack_time_t* usecs_current,
	jack_time_t* usecs_next, float* period)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_time_t
jack_frames_to_time(const jack_client_t* client,
	jack_nframes_t frames)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT jack_nframes_t
jack_time_to_frames(const jack_client_t* client,
	jack_time_t frames)
{
	UNIMPLEMENTED();
}


LIB_EXPORT jack_time_t
jack_get_time()
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_set_error_function(void(*function)(const char* error))
{
	UNIMPLEMENTED();
}


LIB_EXPORT void
jack_set_info_function(void(*function)(const char* info))
{
	UNIMPLEMENTED();
}


LIB_EXPORT void
jack_free(void* pointer)
{
	UNIMPLEMENTED();
}


LIB_EXPORT void
jack_get_version(int* major, int* minor, int* micro, int* proto)
{
	UNIMPLEMENTED();
}


LIB_EXPORT const char*
jack_get_version_string()
{
	UNIMPLEMENTED();
	return NULL;
}


LIB_EXPORT int
jack_set_freewheel(jack_client_t* client, int value)
{
	UNIMPLEMENTED();
	return -1;
}
