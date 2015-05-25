#include			<iostream>
#include			<stdlib.h>
#include			"PelcoMessage.hh"

int					main(int argc, char *argv[])
{
	// Sync, Camera, Command1, Command2, Data1, Data2, Checksum

	// // Pan left at high speed
	// byte			rawBytes[7] = {
	// 	0xFF, 0x01, 0x00, 0x04, 0x3F, 0x00, 0x44
	// };

	// // Pan right at high speed
	// byte			rawBytes[7] = {
	// 	0xFF, 0x01, 0x00, 0x02, 0x3F, 0x00, 0x44
	// };

	// // Tilt down at medium speed
	// byte			rawBytes[7] = {
	// 	0xFF, 0x01, 0x00, 0X10, 0x1E, 0x00, 0x44
	// };

	// // Tilt up at low speed
	// byte			rawBytes[7] = {
	// 	0xFF, 0x01, 0x00, 0x08, 0x05, 0x00, 0x44
	// };

	// Throttle up at low speed
	byte			rawBytes[7] = {
		0xFF, 0x01, 0x00, 0x20, 0x05, 0x00, 0x44
	};

	PelcoMessage	message(rawBytes);

	if (!message.isCorrect())
		std::cerr << "Incorrect format" << std::endl;
	else
	{
		std::cout << "Command 2 byte : [" << message.getByte(4) << "]" << std::endl;
		if (message.isADirectionCommand())
			std::cout << "It's a direction" << std::endl;
		else if (message.isAThrustCommand())
			std::cout << "It's a thrust command" << std::endl;
		else
			std::cout << "It's not a direction" << std::endl;		
	}
	return (EXIT_SUCCESS);
}