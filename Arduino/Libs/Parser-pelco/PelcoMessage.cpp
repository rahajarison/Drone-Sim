#include			<iostream> // To comment on the arduino-board
// #include			"Arduino.h" // to uncomment on the arduino-board

#include			"PelcoMessage.hh"

const byte PelcoMessage::PANRIGHT     = 2;	// Binary : b00000010
const byte PelcoMessage::PANLEFT      = 4; 	// Binary : b00000100
const byte PelcoMessage::TILTUP       = 8;	// Binary : b00001000
const byte PelcoMessage::TILTDOWN     = 16;	// Binary : b00010000
const byte PelcoMessage::THROTTLEUP   = 32;	// Binary : b00100000
const byte PelcoMessage::THROTTLEDOWN = 64;	// Binary : b01000000


PelcoMessage::PelcoMessage(const byte rawMessage[7])
{
	this->_syncByte = rawMessage[0];
	this->_cameraAddress = rawMessage[1];
	this->_command1 = rawMessage[2];
	this->_command2 = rawMessage[3];
	this->_data1 = rawMessage[4];
	this->_data2 = rawMessage[5];
	this->_checksum = rawMessage[6];
}

PelcoMessage::~PelcoMessage()
{
}

bool				PelcoMessage::isCorrect() const
{
	return (_syncByte == SYNCVALUE &&
			this->_checksum == this->calculateChecksum());
}

byte				PelcoMessage::calculateChecksum() const
{
	// TODO : calculate the checksum
	// See http://www.codeproject.com/Articles/8034/Pelco-P-and-D-protocol-implementation-in-C
	// and http://www.commfront.com/RS232_Examples/CCTV/Pelco_D_Pelco_P_Examples_Tutorial.HTM

	// Const problems due to bitset<8>, need to be done with arduino byte's type built-in
	return (this->_checksum);
}

bool				PelcoMessage::isADirectionCommand() const
{
	return (this->_command1 == 0x00 &&
			(isTiltUp() || isTiltDown() || isPanLeft() || isPanRight()));
}

bool				PelcoMessage::isAThrustCommand() const
{
	return (this->_command1 == 0x00 && 
			(isThrottleUp() || isThrottleDown()));
}

bool				PelcoMessage::isAStopCommand() const
{
	return (this->_command1 == 0x00 && this->_command2 == 0x00 &&
			this->_data1 == 0x00 && this->_data2 == 0x00);
}

bool				PelcoMessage::isPanRight() const
{
	return (this->isPan(PelcoMessage::PANRIGHT));
}

bool				PelcoMessage::isPanLeft() const
{
	return (this->isPan(PelcoMessage::PANLEFT));
}

bool				PelcoMessage::isTiltDown() const
{
	return (this->isTilt(PelcoMessage::TILTDOWN));
}

bool				PelcoMessage::isTiltUp() const
{
	return (this->isTilt(PelcoMessage::TILTUP));
}

bool				PelcoMessage::isThrottleUp() const
{
	return (this->isThrottle(PelcoMessage::THROTTLEUP));
}

bool				PelcoMessage::isThrottleDown() const
{
	return (this->isThrottle(PelcoMessage::THROTTLEDOWN));
}

bool				PelcoMessage::isTilt(byte direction) const
{
	return ((_command2 & direction) != 0x00);
}

bool				PelcoMessage::isPan(byte direction) const
{
	return ((_command2 & direction) != 0x00);
}

bool				PelcoMessage::isThrottle(byte direction) const
{
	return ((_command2 & direction) != 0x00);
}

// Ordered by probability of calls to avoid multiple testing
byte				PelcoMessage::getByte(unsigned char offset) const
{
	switch (offset)
	{
		case 4:		return (_command2); break;
		case 5:		return (_data1); break;
		case 6:		return (_data2); break;
		case 7:		return (_checksum); break;
		case 3:		return (_command1); break;
		case 1:		return (_syncByte); break;
		case 2:		return (_cameraAddress); break;
		default:	return 0;
	}
}