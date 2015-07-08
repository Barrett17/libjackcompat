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

#include "jack/midiport.h"


uint32_t
jack_midi_get_event_count(void* buffer)
{
	return 0;
}


int
jack_midi_event_get(jack_midi_event_t* event, void* buffer,
	uint32_t event_index)
{
	return -1;
}


size_t
jack_midi_max_event_size(void* buffer)
{
	return -1;
}


jack_midi_data_t*
jack_midi_event_reserve(void* buffer,
	jack_nframes_t time, size_t data_size)
{
	return NULL;
}


int
jack_midi_event_write(void* buffer,
	jack_nframes_t time, const jack_midi_data_t* data,
	size_t data_size)
{
	return -1;
}


void
jack_midi_clear_buffer(void* buffer)
{
}


uint32_t
jack_midi_get_lost_event_count(void* buffer)
{
	return 0;
}
