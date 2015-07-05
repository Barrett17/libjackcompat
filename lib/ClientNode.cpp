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

#include "ClientNode.h"

#include <Buffer.h>
#include <BufferGroup.h>
#include <MediaEventLooper.h>
#include <SupportDefs.h>
#include <TimeSource.h>

#include "WrapperDefs.h"

#include <stdio.h>
#include <string.h>


ClientNode::ClientNode(const char* name, JackClient* owner)
	:
	BMediaNode(name),
	//BBufferConsumer(B_MEDIA_RAW_AUDIO),
	BBufferProducer(B_MEDIA_RAW_AUDIO),
	BMediaEventLooper(),
	fOwner(owner),
	fTime(0),
	fFramesSent(0)
{
}


ClientNode::~ClientNode()
{
	BMediaEventLooper::Quit();
}


//BMediaNode
BMediaAddOn*
ClientNode::AddOn(int32 *id) const
{
	return NULL;
}


status_t
ClientNode::HandleMessage(int32 code, const void *data,	size_t size)
{

	return B_OK;
}


void
ClientNode::NodeRegistered()
{
	printf("ClientNode::NodeRegistered\n");
	SetPriority(B_REAL_TIME_PRIORITY);

	fFormat.type = B_MEDIA_RAW_AUDIO;
	fFormat.u.raw_audio = media_raw_audio_format::wildcard;

	fFormat.u.raw_audio.channel_count = 1;
	fFormat.u.raw_audio.frame_rate = WRAPPER_PREFERRED_FRAMERATE;
	fFormat.u.raw_audio.byte_order
		= (B_HOST_IS_BENDIAN) ? B_MEDIA_BIG_ENDIAN : B_MEDIA_LITTLE_ENDIAN;

	fFormat.u.raw_audio.buffer_size = WRAPPER_PREFERRED_BUF_SIZE;

	fFormat.u.raw_audio.channel_count = 1;
	fFormat.u.raw_audio.format = WRAPPER_PREFERRED_FORMAT;

	fOwner->SetFormat(fFormat);

	Run();
}


//BBufferConsumer
/*
void
ClientNode::BufferReceived(BBuffer *buffer)
{
	printf("ClientNode::BufferReceived\n");

	media_timed_event event(buffer->Header()->start_time,
		BTimedEventQueue::B_HANDLE_BUFFER, buffer,
		BTimedEventQueue::B_RECYCLE_BUFFER);
	EventQueue()->AddEvent(event);
}

			
status_t
ClientNode::AcceptFormat(const media_destination& dst,
	media_format* format)
{
	printf("ClientNode::AcceptFormat\n");
	if (dst.port != ControlPort())
		return B_MEDIA_BAD_DESTINATION;

	if (format->type == B_MEDIA_UNKNOWN_TYPE)
		format->type = B_MEDIA_RAW_AUDIO;

	if (format->type != B_MEDIA_RAW_AUDIO)
		return B_MEDIA_BAD_FORMAT;

	if (format->u.raw_audio.format != media_raw_audio_format::WRAPPER_PREFERRED_FORMAT)
		return B_MEDIA_BAD_FORMAT;

	// TODO finish it
	format->u.raw_audio.format = media_raw_audio_format::WRAPPER_PREFERRED_FORMAT;
	return B_OK;
}


status_t
ClientNode::GetNextInput(int32 *cookie,	media_input *input)
{
	//printf("next input\n");

	JackPortList* ports = fOwner->GetInputPorts();

	if (*cookie == ports->CountItems())
		return B_BAD_INDEX;

	JackPort* port = ports->ItemAt(*cookie);
	if (port == NULL)
		return B_BAD_INDEX;

	// printf("%s %d\n", port->Name(), *cookie);
	// *input = port->Input();
	*cookie++;

	return B_OK;
}


void
ClientNode::DisposeInputCookie(int32 cookie)
{

}


status_t
ClientNode::FormatChanged(const media_source &src,
	const media_destination &dst,
	int32 change_tag, const media_format &format)
{
	return B_MEDIA_BAD_FORMAT;
}


void
ClientNode::ProducerDataStatus(const media_destination &dst,
		int32 status, bigtime_t when)
{
	printf("ClientNode::ProducerDataStatus\n");
	if (dst != media_destination::null)
		SendDataStatus(status, dst, when);
}


status_t
ClientNode::GetLatencyFor(const media_destination &dst,
	bigtime_t *latency, media_node_id *time_src)
{
	printf("ClientNode::GetLatencyFor\n");
	*latency = fDownstreamLatency + fProcessLatency;
	// we have multiple inputs with different IDs, but
	// the port number must match our ControlPort()
	if (dst.port != ControlPort())
		return B_MEDIA_BAD_DESTINATION;

	// return our event latency - this includes our internal + downstream
	// latency, but _not_ the scheduling latency
	*latency += EventLatency();
	*time_src += TimeSource()->ID();

	printf("ClientNode::GetLatencyFor %Ld, timesource is %ld\n",
		*latency, *time_src);

	return B_OK;
}

	
status_t
ClientNode::Connected(const media_source &src, 
	const media_destination &dst, const media_format &format,
	media_input *input)
{
	printf("ClientNode::Connected\n");
	if (src.id != 0 || src.port != ControlPort())
		return B_MEDIA_BAD_DESTINATION;
	
	fFormat = format;

	return B_OK;
}


void
ClientNode::Disconnected(const media_source &src,
		const media_destination &dst)
{
	printf("ClientNode::Disconnected\n");
	if (dst.port != ControlPort())
		return;
}
*/

//BBufferProducer

status_t
ClientNode::FormatSuggestionRequested(media_type type,
	int32 quality, media_format *format)
{
	printf("ClientNode::FormatSuggestionRequested\n");
	if (type != B_MEDIA_RAW_AUDIO)
		return B_MEDIA_BAD_FORMAT;

	*format = fFormat;
	
	return B_OK;
}


status_t
ClientNode::FormatProposal(const media_source &src,
	media_format *format)
{
	printf("ClientNode::FormatProposal\n");

	if (src.id != 0 || src.port != ControlPort())
		return B_MEDIA_BAD_SOURCE;

	media_raw_audio_format* raw = &format->u.raw_audio;

	if (format->type == B_MEDIA_UNKNOWN_TYPE) {
		format->type = B_MEDIA_RAW_AUDIO;
	} else if (format->type != B_MEDIA_RAW_AUDIO ||
		format->u.raw_audio.format != WRAPPER_PREFERRED_FORMAT)
		return B_MEDIA_BAD_FORMAT;

	if (raw->format == 0)
		raw->format = fFormat.u.raw_audio.format;

 	if (raw->frame_rate == 0)
		raw->frame_rate = fFormat.u.raw_audio.frame_rate;

	if (raw->buffer_size == 0)
		raw->buffer_size = fFormat.u.raw_audio.buffer_size;

	if (raw->channel_count == 0)
		raw->channel_count = fFormat.u.raw_audio.channel_count;

	if (format->u.raw_audio.channel_count > 1
		|| raw->frame_rate != fFormat.u.raw_audio.frame_rate
		|| raw->buffer_size != fFormat.u.raw_audio.buffer_size)
		return B_MEDIA_BAD_FORMAT;

	return B_OK;
}


status_t
ClientNode::FormatChangeRequested(const media_source &src,
	const media_destination &dst,
	media_format *format,
	int32* _deprecated_)
{
	// Unconsidered atm for simplicity.
	return B_MEDIA_BAD_FORMAT;
}


void
ClientNode::LateNoticeReceived(const media_source &src,
	bigtime_t late,	bigtime_t when)
{
	printf("ClientNode::LateNoticeReceived %d\n", (int)src.id);

	// NOTE enable when this become also a consumer
	//NotifyLateProducer(src, late, when);
}


status_t
ClientNode::GetNextOutput(int32 *cookie, media_output *output)
{
	JackPortList* ports = fOwner->GetOutputPorts();

	if (*cookie >= ports->CountItems())
		return B_BAD_INDEX;

	JackPort* port = ports->ItemAt(*cookie);
	if (port == NULL)
		return B_BAD_INDEX;

	*output = *port->MediaOutput();

	printf("ClientNode::GetNextOutput %d %s\n", *cookie, port->Name());

	*cookie += 1;

	return B_OK;
}


status_t
ClientNode::DisposeOutputCookie(int32 cookie)
{
	// TODO investigate
	return B_OK;
}


status_t
ClientNode::SetBufferGroup(const media_source &src,
	BBufferGroup *group)
{
	printf("ClientNode::SetBufferGroup\n");

	if (src.port != ControlPort() || src.id != 0)
		return B_MEDIA_BAD_SOURCE;

	fBufferGroup = group;

	return B_OK;
}


status_t
ClientNode::PrepareToConnect(const media_source &src,
	const media_destination &dst,
	media_format *format, media_source *out_source,
	char *name)
{
	printf("ClientNode::PrepareToConnect\n");
	
	if (dst.port == ControlPort())
		return B_MEDIA_BAD_SOURCE;

	if (src.port != ControlPort() || src.id != 0)
		return B_MEDIA_BAD_SOURCE;

	if (format->type != B_MEDIA_RAW_AUDIO
		&& format->type != B_MEDIA_UNKNOWN_TYPE) {
		return B_MEDIA_BAD_FORMAT;
	}

	JackPort* port;
	JackPortList* outputs = fOwner->GetOutputPorts();

	for (int i = 0; i < outputs->CountItems(); i++) {
		port = outputs->ItemAt(i);

		media_output* output = port->MediaOutput();
		if (output->source.id == src.id
		&& output->destination.id == dst.id) {

			if (port->IsConnected())
				return B_MEDIA_ALREADY_CONNECTED;

			*out_source = output->source;

			BString portName(jack_port_name((jack_port_t*) port));
			portName.CopyInto(name, 0, portName.Length());

			printf("Connecting to %s\n", name);
			format->SpecializeTo(&fFormat);
			return B_OK;
		}
	}

	return B_MEDIA_BAD_SOURCE;
}


void
ClientNode::Connect(status_t status,
	const media_source &src, const media_destination &dst,
	const media_format &format, char* name)
{
	if (status != B_OK)
		return;

	media_node_id id;
	FindLatencyFor(dst, &fDownstreamLatency, &id);

	fOwner->SetFormat(format);

	JackPort* port;
	JackPortList* outputs = fOwner->GetOutputPorts();

	for (int i = 0; i < outputs->CountItems(); i++) {
		port = outputs->ItemAt(i);
		BString str(jack_port_name((jack_port_t*) port));

		if (str.Compare(name) == 0 && !port->IsConnected()) {
			printf("ClientNode::Connect %s\n", port->Name());

			port->MediaOutput()->source = src;
			port->MediaOutput()->destination = dst;
			port->MediaOutput()->format = format;
			break;
		}
	}
}


void
ClientNode::Disconnect(const media_source &src,
	const media_destination &dst)
{
	printf("ClientNode::Disconnect\n");
	JackPort* port;
	JackPortList* outputs = fOwner->GetOutputPorts();
	for (int i = 0; i < outputs->CountItems(); i++) {
		port = outputs->ItemAt(i);
		if (port->MediaOutput()->source == src
			&& port->MediaOutput()->destination == dst) {
			port->SetConnected(false);
		}
	}
}	

	
void
ClientNode::EnableOutput(const media_source &src,
	bool enabled, int32* _deprecated_)
{
	printf("ClientNode::EnableOutput\n");
	if (src.id != 0 || src.port != ControlPort())
		return;

/*	JackPort* port;
	JackPortList* outputs = fOwner->GetOutputPorts();
	for (int i = 0; i < outputs->CountItems(); i++) {
		port = outputs->ItemAt(i);
		if (port->MediaOutput()->source == src
			&& port->MediaOutput()->destination == dst) {

			port->SetEnabled(false);

		}
	}*/
}


status_t
ClientNode::GetLatency(bigtime_t *outLatency)
{
	printf("ClientNode::GetLatency\n");
	*outLatency = EventLatency() + SchedulingLatency();
	return B_OK;
}


void
ClientNode::LatencyChanged(const media_source &src,
	const media_destination &dst,
	bigtime_t latency, uint32 flags)
{
	printf("ClientNode::LatencyChanged\n");
	if (src.port != ControlPort() || src.id != 0) {
		printf("Error: wrong source");
		return;
	}

	fDownstreamLatency = latency;
	SetEventLatency(fDownstreamLatency + fProcessLatency);

	/*media_input* input;
	JackPortList* inputs = fOwner->GetInputPorts();
	for (int i = 0; i < inputs->CountItems(); i++) {
		input = inputs->ItemAt(i)->MediaInput();

		// consumer disabled
		//SendLatencyChange(input->source,
		//	input->destination, EventLatency());
	}*/
}


void 
ClientNode::ProducerDataStatus(const media_destination &dst, int32 status,
	bigtime_t when)
{
	printf("ClientNode::ProducerDataStatus(\n");
	JackPortList* ports = fOwner->GetOutputPorts();
	for (int i = 0; i < ports->CountItems(); i++) {
		JackPort* port = ports->ItemAt(i);
		if (port->MediaOutput()->destination != media_destination::null)
			SendDataStatus(status, port->MediaOutput()->destination, when);
	}
}


void
ClientNode::HandleEvent(const media_timed_event *event,
	bigtime_t late, bool realTimeEvent)
{
	//printf("ClientNode::HandleEvent %d\n", event->type);
	switch (event->type) {
		case BTimedEventQueue::B_HANDLE_BUFFER:
		{
			printf("BTimedEventQueue::B_HANDLE_BUFFER\n");

			break;
		}
		case BTimedEventQueue::B_START:
		{
			printf("BTimedEventQueue::B_START\n");
			if (RunState() != B_STARTED) {
				fFramesSent = 0;
				int period = (fOwner->GetOutputPorts()->CountItems()*2);
				fBufferGroup = new BBufferGroup(fFormat.u.raw_audio.buffer_size,
					period);

				if (fBufferGroup->InitCheck() != B_OK)
					printf("error\n");

				fTime = event->event_time;

				bigtime_t start = ::system_time();
				ComputeCycle();
				bigtime_t produceLatency = ::system_time();
				fProcessLatency = produceLatency - start;

				printf("Estimated latency is %Ld\n", fProcessLatency);

				bigtime_t duration = bigtime_t(1000000LL * fOwner->BufferSize()) /
					int32(fFormat.u.raw_audio.frame_rate);
				SetBufferDuration(duration);
				SetEventLatency(fDownstreamLatency + fProcessLatency);
				_ScheduleOutputEvent(fTime);
				printf("The start event has been scheduled\n");
			}
			break;
		}

		case BTimedEventQueue::B_STOP:
		{
			// stopped - don't process any more buffers, flush all buffers
			// from event queue
			EventQueue()->FlushEvents(0, BTimedEventQueue::B_ALWAYS, true,
				BTimedEventQueue::B_HANDLE_BUFFER);

			Stop(TimeSource()->Now(), true);
			NodeStopped(TimeSource()->Now());

			break;
		}

		case BTimedEventQueue::B_DATA_STATUS:
		{
			break;
		}

		case NEW_BUFFER_EVENT:
		{
			if (RunState() != B_STARTED)
				return;

			if (late > (BufferDuration() / 3) ) {
				printf("ClientNode::HandleEvent::NEW_BUFFER_EVENT, event"
					" scheduled much too late, lateness is %"
					B_PRId64 "\n", late);
			}

			// The first cycle is always computed
			// in the B_START event, so we skip it
			// at the first time.
			if (fFramesSent > 0)
				ComputeCycle();

			_DataAvailable(event->event_time);
			int64 samples = fFormat.u.raw_audio.buffer_size
				/ ((fFormat.u.raw_audio.format
				& media_raw_audio_format::B_AUDIO_SIZE_MASK));
			fFramesSent += samples;

			// Now we schedule the next event
			bigtime_t nextEvent = fTime + bigtime_t((1000000LL * double(fFramesSent))
				/ int32(fFormat.u.raw_audio.frame_rate));
			_ScheduleOutputEvent(nextEvent);
			break;
		}

		default:
			break;
	}
}


status_t
ClientNode::ComputeCycle()
{
	//printf("ClientNode::ComputeCycle()\n");

	// Set the buffers and set up the ports
	// for processing.
	//_WaitForInputPorts();
	status_t ret = _InitOutputPorts();
	if (ret != B_OK)
		return ret;

	// Let the process init
	fOwner->Process(fOwner->BufferSize());

	return B_OK;
}


status_t
ClientNode::_InitOutputPorts()
{
	//printf("JackClient::_InitOutputPorts()\n");
	JackPortList* outputPorts = fOwner->GetOutputPorts();

	for (int i = 0; i < outputPorts->CountItems(); i++) {
		JackPort* port = outputPorts->ItemAt(i);
		if (!port->IsConnected())
			return B_ERROR;

		BBuffer* buffer = fBufferGroup->RequestBuffer(
			fFormat.u.raw_audio.buffer_size);

		if (buffer == NULL || buffer->Data() == NULL) {
			printf("RequestBuffer failed\n");
			return B_ERROR;
		}

		port->SetProcessingBuffer(buffer);
	}
	return B_OK;
}


void
ClientNode::_DataAvailable(bigtime_t time)
{
	JackPortList* ports = fOwner->GetOutputPorts();
	for (int i = 0; i < ports->CountItems(); i++) {
		JackPort* port = ports->ItemAt(i);
		if (port != NULL && port->IsConnected()) {

			BBuffer* buffer = FillNextBuffer(time, port);
			if (buffer != NULL) {
				if (SendBuffer(buffer,
					port->MediaOutput()->source, port->MediaOutput()->destination)
					!= B_OK) {

					printf("ClientNode::_DataAvailable: Buffer sending "
						"failed\n");
					buffer->Recycle();
				}
			} else
				printf("Buffer is null!\n");
		}
	}
}


BBuffer*
ClientNode::FillNextBuffer(bigtime_t eventTime, JackPort* port)
{
	//printf("FillNextBuffer\n");
	BBuffer* buffer = port->CurrentBuffer();
	media_header* header = buffer->Header();
	header->type = B_MEDIA_RAW_AUDIO;
	header->size_used = fFormat.u.raw_audio.buffer_size;
	header->time_source = TimeSource()->ID();
	header->start_time = eventTime;
	return buffer;
}


status_t
ClientNode::_ScheduleOutputEvent(bigtime_t event)
{
	media_timed_event nextBufferEvent(event, NEW_BUFFER_EVENT);
	EventQueue()->AddEvent(nextBufferEvent);
	return B_OK;
}


JackPort*
ClientNode::_FindOutputPort(media_source source, media_destination dest) const
{
	JackPort* port;
	JackPortList* outputs = fOwner->GetOutputPorts();
	for (int i = 0; i < outputs->CountItems(); i++) {
		port = outputs->ItemAt(i);
		if (source == port->MediaOutput()->source && dest == 
			port->MediaOutput()->destination)
				return port;
	}
	return NULL;
}
