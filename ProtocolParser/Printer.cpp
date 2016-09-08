
#include "Printer.h"
#include <stdio.h>

Printer printerSingleton;

Printer::Printer()
{
	m_currentIndex = 0;
	m_file = NULL;
}

void Printer::openFile(char* fileToOpen)
{
	m_file = fopen(fileToOpen, "w");
	m_currentIndex = 0;
	initialize();
}

void Printer::closeFile()
{
	fclose(m_file);
}

Printer::~Printer()
{
	//nothing to do here, no heap allocations
}

void Printer::printToBuffer(PrinterFields_e field, char** string)
{
	buffer[m_currentIndex].dataStringPointer = string;
	buffer[m_currentIndex].field = field;
	++m_currentIndex;
}

void Printer::reset()
{
	for (uint32_t i = 0; i < 100; ++i)
	{
		buffer[i].dataStringPointer = NULL;
		buffer[i].field = FIELD_NONE;
	}
	m_currentIndex = 0;
}

void Printer::printToFile()
{
	for (uint32_t i = 0; i < TOTAL_FIELDS; ++i)
	{
		for (uint32_t j = 0; j < TOTAL_FIELDS; ++j)
		{
			if (buffer[j].field == static_cast<PrinterFields_e>(i))
			{
				fputs(*(buffer[j].dataStringPointer), m_file);
				break;
			}
		}
		fputs(",", m_file);
	}
	fputs("\n", m_file);
	reset();
}

// Print out all the file names first.
void Printer::initialize()
{
	for (uint32_t i = 0; i < TOTAL_FIELDS; ++i)
	{
		fputs(m_headerStrings[i],m_file);
		fputs(",", m_file);
	}
	fputs("\n", m_file);

	for (uint32_t i = 0; i < 100; ++i)
	{
		buffer[i].dataStringPointer = NULL;
		buffer[i].field = FIELD_NONE;
	}
}
