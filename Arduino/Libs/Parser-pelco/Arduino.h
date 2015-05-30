#ifndef						ARDUINO_H_
# define					ARDUINO_H_

# include					<string>

# define	HEX				(16)

typedef		unsigned char 	byte;

class						HardwareSerial
{
public:
	virtual byte			available();
	virtual byte 			read();
	virtual void			print(byte toPrint);
	virtual void			print(byte toPrint, byte format);
	virtual void			print(std::string toPrint);
	virtual void			println(byte toPrint);	
	virtual void			println(byte toPrint, byte format);
	virtual void			println(std::string toPrint);	
private:
};

class 						MockSerial
{
public:
	virtual byte			available();
	virtual byte 			read();
	virtual void			print(byte toPrint);
	virtual void			print(byte toPrint, byte format);
	virtual void			print(std::string toPrint);
	virtual void			println(byte toPrint);	
	virtual void			println(byte toPrint, byte format);
	virtual void			println(std::string toPrint);	
};

extern MockSerial			Serial;
extern MockSerial			Serial1;
extern MockSerial			Serial2;
extern MockSerial			Serial3;

#endif