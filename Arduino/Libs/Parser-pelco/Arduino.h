#ifndef					ARDUINO_H_
# define				ARDUINO_H_

# include				<string>

# define	HEX			(16)

typedef		unsigned char byte;

class 			MockSerial
{
public:
	byte			available();
	byte 			read();
	void			print(byte toPrint);
	void			print(byte toPrint, byte format);
	void			print(std::string toPrint);
	void			println(byte toPrint);	
	void			println(byte toPrint, byte format);
	void			println(std::string toPrint);	
};

extern MockSerial	Serial;
extern MockSerial	Serial3;

#endif