#ifndef _HAIKU_JACKPORT_H_
#define _HAIKU_JACKPORT_H_

#include <Locker.h>
#include <MediaDefs.h>
#include <ObjectList.h>

#include "JackClient.h"
#include "WrapperDefs.h"

class JackClient;


class JackPort
{
public:
					JackPort(const char *port_name,
						const char *port_type, unsigned long flags,
						unsigned long buffer_size, JackClient* owner);

					~JackPort();

	JackClient*		Owner() const;
	const char*		Name() const;
	const char*		Type() const;
	unsigned long	Flags() const;
	unsigned long	BufferSize() const;

	void			SetProcessingBuffer(BBuffer* buffer);
	BBuffer*		CurrentBuffer();

	void			SetMediaInput(media_input dest);
	void			SetMediaOutput(media_output dest);

	media_input*	MediaInput() const;
	media_output*	MediaOutput() const;

	void			SetConnected(bool connected);
	bool			IsConnected() const;

	void			SetEnabled(bool enabled);
	bool			IsEnabled() const;

private:
	const char*		fType;
	unsigned long	fFlags;
	unsigned long	fBufferSize;
	BBuffer*		fCurrentBuf;

	const char*		fName;
	JackClient*		fOwner;

	bool			fConnected;
	bool			fEnabled;

	media_input*	fInput;
	media_output*	fOutput;
};


#endif	// _JACKPORT_H_
