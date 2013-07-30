#include <string.h>

#include "JackPort.h"


JackPort::JackPort(const char *port_name,
	const char *port_type, unsigned long flags,
	unsigned long buffer_size, JackClient* owner)
	:
	fOwner(owner),
	fType(port_type),
	fFlags(flags),
	fBufferSize(buffer_size)
{
	fOwner = owner;
	fName = port_name;
	fConnected = false;
	fEnabled = false;
	fInput = new media_input();
	fOutput = new media_output();
	fCurrentBuf = NULL;
}


JackPort::~JackPort()
{
	delete fInput;
	delete fOutput;
}


JackClient*
JackPort::Owner() const
{
	return fOwner;
}


const char*
JackPort::Name() const
{
	return fName;
}


const char*
JackPort::Type() const
{
	return fType;
}


unsigned long
JackPort::Flags() const
{
	return fFlags;
}


unsigned long
JackPort::BufferSize() const
{
	return fBufferSize;
}


BBuffer*
JackPort::CurrentBuffer()
{
	return fCurrentBuf;
}


void
JackPort::SetProcessingBuffer(BBuffer* buf)
{
	fCurrentBuf = buf;
}


void
JackPort::SetMediaInput(media_input dest)
{
	*fInput = dest;
}


void
JackPort::SetMediaOutput(media_output dest)
{
	*fOutput = dest;
}


media_input*
JackPort::MediaInput() const
{
	return fInput;
}


media_output*
JackPort::MediaOutput() const
{
	return fOutput;
}

void
JackPort::SetConnected(bool connected)
{
	fConnected = connected;
}


bool
JackPort::IsConnected() const
{
	return fConnected;
}


void
JackPort::SetEnabled(bool enabled)
{
	fEnabled = enabled;
}


bool
JackPort::IsEnabled() const
{
	return fEnabled;
}
