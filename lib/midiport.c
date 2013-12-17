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

void
jack_midi_clear_buffer(void* port_buffer)
{
}


int
jack_midi_event_get(jack_midi_event_t* event,
                    void*        port_buffer,
                    uint32_t    event_index)
{
}


int
jack_midi_event_write(void* port_buffer,
                      jack_nframes_t time,
                      const jack_midi_data_t* data,
                      size_t data_size)
{
}


uint32_t
jack_midi_get_event_count(void* port_buffer)
{
}
