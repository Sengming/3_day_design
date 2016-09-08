#include "Clamp2Decoder.h"
#include "Printer.h"
#include <stdio.h>

#define BIT_1	(0x01)
#define BYTE	(8)

void Clamp2Decoder::decode(DataLinePair* dataToDecode)
{
	if (m_isValidPair = true)
	{
		// First call base implmentation to handle generic things
		BaseDecoderInterface::decode(dataToDecode);
		//printf("Clamp2Decoder!\n");

		// Decode the Command Line:
		snprintf(m_clampClosed, 20, "Clamp Closed");
		snprintf(m_clampOpen, 20, "Clamp Open");

		// Commands
		for (uint32_t i = 0; i < BYTE; i++)
		{
			if (((dataToDecode->lines[0].byte[4]) >> i) & BIT_1)
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_9), &m_clampOpen);
			}
			else
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_9), &m_clampClosed);
			}
		}

		for (uint32_t i = 0; i < (BYTE / 2); i++)
		{
			if (((dataToDecode->lines[0].byte[4]) >> i) & BIT_1)
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_17), &m_clampOpen);
			}
			else
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + COMMAND_CLAMP_17), &m_clampClosed);
			}
		}

		// Responses

		for (uint32_t i = 0; i < BYTE; i++)
		{
			if (((dataToDecode->lines[1].byte[3]) >> i) & BIT_1)
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_9), &m_clampOpen);
			}
			else
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_9), &m_clampClosed);
			}
		}

		for (uint32_t i = 0; i < (BYTE / 2); i++)
		{
			if (((dataToDecode->lines[1].byte[2]) >> i) & BIT_1)
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_17), &m_clampOpen);
			}
			else
			{
				printerSingleton.printToBuffer(static_cast<PrinterFields_e>(i + RESPONSE_CLAMP_17), &m_clampClosed);
			}
		}
	}
}

Clamp2Decoder::Clamp2Decoder()
{
}

Clamp2Decoder::~Clamp2Decoder()
{
	delete[] m_clampClosed;
	delete[] m_clampOpen;
}