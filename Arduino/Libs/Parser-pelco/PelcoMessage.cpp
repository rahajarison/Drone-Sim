#include			<iostream> // To comment on the arduino-board
// #include			"Arduino.h" // to uncomment on the arduino-board

#include			"PelcoMessage.hh"

const byte PelcoMessage::PANRIGHT = 2;	// Binary : b00000010
const byte PelcoMessage::PANLEFT  = 4; 	// Binary : b00000100
const byte PelcoMessage::TILTUP   = 8;	// Binary : b00001000
const byte PelcoMessage::TILTDOWN = 16;	// Binary : b00010000


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
	return (this->_checksum);
}

bool				PelcoMessage::isADirection() const
{
	// TODO : think about the "stop" (set / stabilize) function
	return (_command1 == 0x00 &&
			(isTiltUp() || isTiltDown() || isPanLeft() || isPanRight()));
}

bool				PelcoMessage::isTiltUp() const
{
	return (this->isTilt(PelcoMessage::TILTUP));
}

bool				PelcoMessage::isTiltDown() const
{
	return (this->isTilt(PelcoMessage::TILTDOWN));
}

bool				PelcoMessage::isPanLeft() const
{
	return (this->isPan(PelcoMessage::PANLEFT));
}

bool				PelcoMessage::isPanRight() const
{
	return (this->isPan(PelcoMessage::PANRIGHT));
}

bool				PelcoMessage::isTilt(byte direction) const
{
	return ((_command2 & direction) != 0x00);
}

bool				PelcoMessage::isPan(byte direction) const
{
	std::cout << _command2 << std::endl;
	return ((_command2 & direction) != 0x00);
}