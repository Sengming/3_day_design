#include <stdio.h>
#include "Clamp1Decoder.h"
#include "GeneralTypes.h"
#include "Printer.h"

#define BIT_1	(0x01)
#define BYTE	(8)

void Clamp1Decoder::decodeBytes(DataLinePair* dataToDecode)
{
	// BWS Rather than putting the 'burden' on the derived classes to control the flow
	//     of decoding and call the base class method, consider the template method pattern.
	//     https://sourcemaking.com/design_patterns/template_method
	//
	//     The base class could do the control flow for decoding.  Then it could call to
	//     protected virtual methods which are filled in by the derived classes (like Clamp1Decoder).
	//     These derived methods would then just focus on their specific decode and leave the control
	//     flow logic in the base class.

	//printf("Clamp1Decoder!\n");

	// Decode the Command Line:
	snprintf(m_clampClosed, 20, "Clamp Closed");
	snprintf(m_clampOpen, 20, "Clamp Open");

	for (uint32_t i = 0; i < BYTE; i++)
	{
		if (((dataToDecode->lines[0].byte[4]) >> i) & BIT_1)
		{
			printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_1), &m_clampOpen);
		}
		else
		{
			printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_1), &m_clampClosed);
		}
	}

	// Decode the Response:

	for (uint32_t i = 0; i < BYTE; i++)
	{
		if (((dataToDecode->lines[1].byte[3]) >> i) & BIT_1)
		{
			printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_1), &m_clampOpen);
		}
		else
		{
			printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_1), &m_clampClosed);
		}
	}
}

Clamp1Decoder::Clamp1Decoder()
{
}

Clamp1Decoder::~Clamp1Decoder()
{
	delete[] m_clampClosed;
	delete[] m_clampOpen;
 }