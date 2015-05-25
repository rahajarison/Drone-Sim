#include			<iostream>
#include			<stdlib.h>
#include			"PelcoMessage.hh"

int					main(int argc, char *argv[])
{
	// Sync, Camera, Command1, Command2, Data1, Data2, Checksum
	// Pan left at high speed
	byte			rawBytes[7] = {
		0xFF, 0x01, 0x00, 0x04, 0x3F, 0x00, 0x44
	};
	PelcoMessage	message(rawBytes);

	if (!message.isCorrect())
		std::cerr << "Incorrect format" << std::endl;
	else
	{
		if (message.isADirection())
			std::cout << "IT'S A TRAP" << std::endl;
		else
			std::cout << "Loul. Nope." << std::endl;		
	}
	return (EXIT_SUCCESS);
}