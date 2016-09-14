#include "BaseDecoderInterface.h"
#include "DataLine.h"
#include "Printer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

BaseDecoderInterface::BaseDecoderInterface()
{
}

BaseDecoderInterface::~BaseDecoderInterface()
{
	delete[] m_timestamp;
	delete[] m_address;
}

// Check the checksum for match:
bool BaseDecoderInterface::checkChecksum(DataLinePair* dataToDecode)
{
	assert(dataToDecode != nullptr);
	bool retVal = false;

	if (dataToDecode->lines[0].checksum == dataToDecode->lines[1].checksum)
	{
		retVal = true;
	}
	else
	{
		retVal = false;
	}
	return retVal;
}

// Template method which will be used to call the different decode methods.
void BaseDecoderInterface::decodeAll(DataLinePair* dataToDecode)
{
	assert(dataToDecode != nullptr);
	if (checkChecksum(dataToDecode))
	{
		decodeTime(dataToDecode);
		decodeAddress(dataToDecode);
		decodeBytes(dataToDecode);
		printerSingleton.printToFile();
	}
}

// Decode time. 
void BaseDecoderInterface::decodeTime(DataLinePair* dataToDecode)
{
	assert(dataToDecode != nullptr);
	snprintf(m_timestamp, 30, "%f - %f", dataToDecode->lines[0].timeStamp, dataToDecode->lines[1].timeStamp);
	printerSingleton.printToBuffer(TIME, &m_timestamp);
}

// Deocde  address
void BaseDecoderInterface::decodeAddress(DataLinePair* dataToDecode)
{
	assert(dataToDecode != nullptr);
	snprintf(m_address, 30, "%#x", dataToDecode->lines[0].byte[0]);
	printerSingleton.printToBuffer(ADDRESS, &m_address);
}

// Does handling of data bytes here
void BaseDecoderInterface::decodeBytes(DataLinePair* dataToDecode)
{ 
	
	// BWS In general you default your results to the pesimistic failure state.  Then set
	//     to success when the often narrow success path is taken.
    //       
	//     m_isValidPair = false;
	//     if( lines[0].checksum == lines[1].checksum ) {
	//         process...
	//         m_isValidPair = true;
	//     }
	//
	//     Defining the success path in your if, rather than the failure path tends to be more
	//     maintainable.
}