#ifndef _CLIENT_NODE_H
#define _CLIENT_NODE_H

#include <BufferProducer.h>
#include <BufferConsumer.h>
#include <MediaEventLooper.h>

#include "JackClient.h"
#include "JackPort.h"


class JackPort;
class JackClient;
class BBufferGroup;

#define NEW_BUFFER_EVENT (BTimedEventQueue::B_USER_EVENT + 1)

class ClientNode
	: /*public BBufferConsumer,*/ public BBufferProducer,
		public BMediaEventLooper
{	
public:
							ClientNode(const char* name,
								JackClient* owner);

	virtual 				~ClientNode();

//BMediaNode
public:
	virtual		BMediaAddOn *AddOn(int32 *id) const;
	virtual		status_t 	HandleMessage(int32 code, const void *data,
								size_t size);
protected:
	virtual 	void 		NodeRegistered();

//BBufferConsumer
/*public:
	virtual 	void 		BufferReceived(BBuffer *buffer);									
	virtual 	status_t 	AcceptFormat(const media_destination &dst,
							media_format *format);
	virtual 	status_t 	GetNextInput(int32 *cookie,	media_input *input);
	virtual 	void 		DisposeInputCookie(int32 cookie);
	virtual 	status_t 	FormatChanged(const media_source &src,
									const media_destination &dst,
							int32 change_tag, const media_format &format);
	virtual 	void 		ProducerDataStatus(const media_destination &dst,
									int32 status,
									bigtime_t when);	
	virtual 	status_t 	GetLatencyFor(const media_destination &dst,
							bigtime_t *latency,
							media_node_id *time_src);		
	virtual 	status_t 	Connected(const media_source &src, 
									const media_destination &dst,
									const media_format &format,
									media_input *input);
	virtual 	void 		Disconnected(const media_source &src,
									const media_destination &dst);*/
//BBufferProducer
public:
	virtual 	status_t 	FormatSuggestionRequested(media_type type,
									int32 quality, media_format *format);
	virtual 	status_t 	FormatProposal(const media_source &src,
									media_format *format);
	virtual 	status_t 	FormatChangeRequested(const media_source &src,
									const media_destination &dst,
									media_format *format,
									int32* _deprecated_);
	virtual 	void 		LateNoticeReceived(const media_source &src,
									bigtime_t late,	bigtime_t when);
	virtual 	status_t	GetNextOutput(int32 *cookie, media_output *output);
	virtual 	status_t 	DisposeOutputCookie(int32 cookie);
	virtual 	status_t	SetBufferGroup(const media_source &src,
									BBufferGroup *group);
	virtual 	status_t 	PrepareToConnect(const media_source &src,
									const media_destination &dst,
									media_format *format,
									media_source *out_source,
									char *name);
	virtual 	void 		Connect(status_t status,
									const media_source &src,
									const media_destination &dst,
									const media_format &format,
									char* name);
	virtual		void 		Disconnect(const media_source &src,
									const media_destination &dst);		
	virtual 	void 		EnableOutput(const media_source &src,
									bool enabled, int32* _deprecated_);
	virtual 	status_t 	GetLatency(bigtime_t *outLatency);
	virtual 	void 		LatencyChanged(	const media_source &src,
									const media_destination &dst,
									bigtime_t latency, uint32 flags);

				void 		ProducerDataStatus(const media_destination &dst,
								int32 status, bigtime_t when);
protected:
	virtual 	void 		HandleEvent(const media_timed_event *event,
									bigtime_t late,
									bool realTimeEvent=false);

private:
				status_t	_ScheduleOutputEvent(bigtime_t event);
				status_t	ComputeCycle();
				status_t	_InitOutputPorts();

				void		_DataAvailable(bigtime_t time);

				BBuffer*	FillNextBuffer(bigtime_t eventTime,
							 	JackPort* port);

				JackPort*	_FindOutputPort(media_source source,
								media_destination dest) const;

				JackClient*	 fOwner;

				media_format fFormat;

				bigtime_t	 fDownstreamLatency;
				bigtime_t	 fProcessLatency;
				bigtime_t	 fLastLateness;

				bigtime_t	 fTime;
				size_t		 fFramesSent;

				BBufferGroup*	fBufferGroup;
};

#endif
