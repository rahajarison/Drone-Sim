#ifndef							PELCOMESSAGE_HH_
# define						PELCOMESSAGE_HH_

# include						<bitset>

# define	SYNCVALUE			(0xFF)

typedef std::bitset<8>			byte; // To disable on the arduino

class PelcoMessage
{
public:
	PelcoMessage(const byte rawMessage[7]);
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

#endif /* !PELCOMESSAGE_HH_ */