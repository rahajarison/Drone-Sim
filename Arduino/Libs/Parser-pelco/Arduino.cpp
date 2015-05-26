#include		<iostream>
#include		"Arduino.h"

byte		MockSerial::read()
{
	return (0xFF);
}

byte		MockSerial::available()
{
	return (1);
}

void		MockSerial::print(byte toPrint)
{
	std::cout << toPrint;
}

void		MockSerial::print(byte toPrint, byte format)
{
	std::cout << toPrint;
}

void		MockSerial::print(std::string toPrint)
{
	std::cout << toPrint;
}

void		MockSerial::println(byte toPrint)
{
	this->print(toPrint);
	std::cout << std::endl;
}

void		MockSerial::println(byte toPrint, byte format)
{
	this->print(toPrint, format);
	std::cout << std::endl;
}

void		MockSerial::println(std::string toPrint)
{
	this->print(toPrint);
	std::cout << std::endl;
}
