#ifndef								PELCOBUFFER_H_
# define							PELCOBUFFER_H_

# include							"Arduino.h"

# define	SYNCVALUE				(0xFF)
# define	PELCOBUFFERSIZE			(7)

class PelcoBuffer
{
public:
	PelcoBuffer(HardwareSerial& serial);
	virtual ~PelcoBuffer();

	unsigned int					getSize() const;
	bool							isComplete() const;
	const byte*						getBytes() const;
	void							acquire();
	void							flush();
	void							printBuffer() const;

private:
	byte							_buffer[PELCOBUFFERSIZE];
	unsigned int					_size;
	HardwareSerial&					_serial;
};

#endif /* !PELCOBUFFER_H_ */