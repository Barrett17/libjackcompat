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

#include "jack/thread.h"

#include "WrapperDefs.h"


LIB_EXPORT int
jack_client_real_time_priority(jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_client_max_real_time_priority(jack_client_t* client)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_acquire_real_time_scheduling(jack_native_thread_t thread, int priority)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_client_create_thread(jack_client_t* client,
	jack_native_thread_t* thread, int priority, int realtime,
	void* (*start_routine)(void*), void* arg)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_drop_real_time_scheduling(jack_native_thread_t thread)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_client_stop_thread(jack_client_t* client, jack_native_thread_t thread)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT int
jack_client_kill_thread(jack_client_t* client, jack_native_thread_t thread)
{
	UNIMPLEMENTED();
	return -1;
}


LIB_EXPORT void
jack_set_thread_creator(jack_thread_creator_t creator)
{
	UNIMPLEMENTED();
}
