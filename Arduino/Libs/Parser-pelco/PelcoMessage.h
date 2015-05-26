#ifndef							PELCOMESSAGE_H_
# define						PELCOMESSAGE_H_

# include						"Arduino.h" // to uncomment on the arduino-board

// # include						<bitset>

// typedef std::bitset<8>			byte; // To disable on the arduino

class PelcoMessage
{
public:
	PelcoMessage(const byte rawMessage[7]);
	PelcoMessage(const PelcoBuffer &buffer);
	virtual ~PelcoMessage();

	bool						isCorrect() const;
	bool						isADirectionCommand() const;
	bool						isAThrustCommand() const;
	bool						isAStopCommand() const;
	bool						isPanRight() const;
	bool						isPanLeft() const;
	bool						isTiltDown() const;
	bool						isTiltUp() const;
	bool						isThrottleUp() const;
	bool						isThrottleDown() const;
	byte						getByte(unsigned char offset) const;
	// TODO add yaw	

private:
	byte						calculateChecksum() const;
	bool						isTilt(byte direction) const;
	bool						isPan(byte direction) const;
	bool						isThrottle(byte direction) const;

	static const byte 			PANRIGHT;
	static const byte 			PANLEFT;
	static const byte 			TILTDOWN;
	static const byte 			TILTUP;
	static const byte 			THROTTLEUP;
	static const byte 			THROTTLEDOWN;

	byte						_syncByte;
	byte						_cameraAddress;
	byte						_command1;
	byte						_command2;
	byte						_data1;
	byte						_data2;
	byte						_checksum;
};

#endif /* !PELCOMESSAGE_H_ */