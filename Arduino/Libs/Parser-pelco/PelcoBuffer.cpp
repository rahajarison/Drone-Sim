#include	"Arduino.h"
#include	"PelcoBuffer.h"

PelcoBuffer::PelcoBuffer(HardwareSerial& serial) : _serial(serial)
{
	this->flush();
}

PelcoBuffer::~PelcoBuffer()
{
	this->flush();
}

void			PelcoBuffer::flush()
{
	for (byte i = 0; i < PELCOBUFFERSIZE; i++)
		this->_buffer[i] = 0x00;
	this->_size = 0;
}

const byte*		PelcoBuffer::getBytes() const
{
	return (this->_buffer);
}

unsigned int	PelcoBuffer::getSize() const
{
	return (this->_size);
}

bool			PelcoBuffer::isComplete() const
{
	return (this->_size == PELCOBUFFERSIZE);
}

void			PelcoBuffer::acquire()
{
	byte 		toParse;

	toParse = 0x00;
	if (!this->isComplete())
	{
		if (this->_size == 0)
		{
			while (_serial.available() > 0 && toParse != SYNCVALUE)
			{
				toParse = _serial.read();
			}
			if (toParse == SYNCVALUE)
			{
				_buffer[0] = toParse;
				++(this->_size);
			}
		}
		else
		{
			while (_serial.available() > 0 && !this->isComplete())
			{
				_buffer[_size] = _serial.read();
				++(this->_size);
			}
		}
	}
}

void			PelcoBuffer::printBuffer() const
{
	Serial.print("[");
    for (int i = 0; i < PELCOBUFFERSIZE; i++)
    {
      Serial.print(_buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println("]");
}