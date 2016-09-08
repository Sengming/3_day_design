#include "BaseDecoderInterface.h"
#include "DataLine.h"
#include "Printer.h"
#include <stdio.h>
#include <string.h>

BaseDecoderInterface::BaseDecoderInterface(): m_isValidPair(true)
{
}

BaseDecoderInterface::~BaseDecoderInterface()
{
	printerSingleton.printToFile();
	delete[] m_timestamp;
	delete[] m_address;
}

// Does generic handling of lines here
void BaseDecoderInterface::decode(DataLinePair* dataToDecode)
{ 
	if (dataToDecode->lines[0].checksum != dataToDecode->lines[1].checksum)
	{
		m_isValidPair = false;
	}
	else
	{
		m_isValidPair = true;
		// Checksums match! Time to decode time, address and other shared stuff.
		snprintf(m_timestamp, 30, "%f - %f", dataToDecode->lines[0].timeStamp, dataToDecode->lines[1].timeStamp);
		printerSingleton.printToBuffer(TIME, &m_timestamp);

		snprintf(m_address, 30, "%#x", dataToDecode->lines[0].byte[0]);
		printerSingleton.printToBuffer(ADDRESS, &m_address);
	}
 

}