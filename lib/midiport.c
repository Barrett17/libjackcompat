#include "jack/midiport.h"

void
jack_midi_clear_buffer(void *port_buffer)
{
}


int
jack_midi_event_get(jack_midi_event_t *event,
                    void        *port_buffer,
                    uint32_t    event_index)
{
}


int
jack_midi_event_write(void *port_buffer,
                      jack_nframes_t time,
                      const jack_midi_data_t *data,
                      size_t data_size)
{
}


uint32_t
jack_midi_get_event_count(void* port_buffer)
{
}
