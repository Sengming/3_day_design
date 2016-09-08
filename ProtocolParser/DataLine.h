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
	char byte[100];
	uint32_t checksum;
};

struct DataLinePair
{
	DataLine lines[2];
};




#endif