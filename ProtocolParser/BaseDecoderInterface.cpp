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
	// BWS I would have passed dataToDecode in as a referece.
	//     But if you are going to use a pointer, then just get in the habbit of adding:
	//     assert( dataToDecode != nullptr )

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