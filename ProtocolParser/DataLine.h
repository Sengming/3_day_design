#pragma once

#ifndef DATALINE_H_
#define DATALINE_H_
#include <stdint.h>

enum Direction_e
{
	TX = 0,
	RX
};

struct DataLine
{
	double timeStamp;
	Direction_e IoDirection;
	char byte[100];   // BWS If writing in C++ and you have the power of the std library, you don't 
	                  //     need to make these assumptions about number of bytes.
	                  //     Take a look at std::vector
	uint32_t checksum;
};

struct DataLinePair
{
	DataLine lines[2];
};




#endif