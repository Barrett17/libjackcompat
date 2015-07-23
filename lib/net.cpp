/*
    Copyright 2015 Dario Casalinuovo. All rights reserved.

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

#include "jack/net.h"

#include "WrapperDefs.h"


LIB_EXPORT jack_net_master_t* jack_net_master_open(const char* ip,
	int port, const char* name, jack_master_t* req,
	jack_slave_t* result)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT int
jack_net_master_close(jack_net_master_t* net)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_net_master_recv(jack_net_master_t* net, int audio_input,
	float** audio_input_buffer, int midi_input,
	void** midi_input_buffer)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_net_master_send(jack_net_master_t* net, int audio_output,	
	float** audio_output_buffer, int midi_output,
	void** midi_output_buffer)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT jack_net_slave_t* jack_net_slave_open(const char* ip,
	int port, const char* name, jack_slave_t* request,
	jack_master_t* result)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT int
jack_net_slave_close(jack_net_slave_t* net)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_net_slave_activate(jack_net_slave_t* net)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_net_slave_deactivate(jack_net_slave_t* net)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_set_net_slave_process_callback(jack_net_slave_t* net,
	JackNetSlaveProcessCallback callback, void* cookie)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_set_net_slave_buffer_size_callback(jack_net_slave_t* net,
	JackNetSlaveBufferSizeCallback callback, void* cookie)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_set_net_slave_sample_rate_callback(jack_net_slave_t* net,
	JackNetSlaveSampleRateCallback callback, void* cookie)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_set_net_slave_shutdown_callback(jack_net_slave_t* net,
	JackNetSlaveShutdownCallback callback, void* cookie)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT jack_adapter_t*
jack_create_adapter(int input, int output,
	jack_nframes_t host_buffer_size,
	jack_nframes_t host_sample_rate,
	jack_nframes_t adapted_buffer_size,
	jack_nframes_t adapted_sample_rate)
{
	UNIMPLEMENTED();

	return NULL;
}


LIB_EXPORT int
jack_destroy_adapter(jack_adapter_t* adapter)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT void
 jack_flush_adapter(jack_adapter_t* adapter)
{
	UNIMPLEMENTED();
}


LIB_EXPORT int
jack_adapter_push_and_pull(jack_adapter_t* adapter,
	float** input, float** output, unsigned int frames)
{
	UNIMPLEMENTED();

	return -1;
}


LIB_EXPORT int
jack_adapter_pull_and_push(jack_adapter_t* adapter,
	float** input, float** output, unsigned int frames)
{
	UNIMPLEMENTED();

	return -1;
}
