
#include "InputFileReader.h"
#include <string.h>
#include <stdlib.h>


InputFileReader::InputFileReader() : m_pfile(NULL), m_eof(false)
{
	// Intentionally left blank
}

InputFileReader::~InputFileReader()
{
	// Intentionally left blank
}

bool InputFileReader::setFile(char* filename)
{
	m_pfile = fopen(filename, "r");
	return true;
}

DataLine InputFileReader::processLine()
{
	DataLine tempData;
	if (fgets(m_copiedstring, MAX_STRING_LENGTH, m_pfile) == NULL)
	{
		m_eof = true;
	}
	else
	{
		if (m_copiedstring[strlen(m_copiedstring) - 1] == '\n')
		{
			m_copiedstring[strlen(m_copiedstring) - 1] = '\0';
		}

		stringChopper(m_copiedstring, &tempData);
	}
	return tempData;
}

inline void InputFileReader::stringChopper(char* rawString, DataLine* line)
{
	char* tempChar;

	tempChar = strtok(rawString, "\t");
	line->timeStamp = strtod(tempChar, NULL);

	tempChar = strtok(NULL, "\t");
	if (!strcmp(tempChar, "TX"))
	{
		line->IoDirection = TX;
	}
	else if (!strcmp(tempChar, "RX"))
	{
		line->IoDirection = RX;
	}

	for (uint32_t i = 0; tempChar != NULL; i++)
	{
		tempChar = strtok(NULL, "\t");
		if (tempChar != NULL)
		{
			line->byte[i] = (char)strtol(tempChar, NULL, 16);
		}
		else
		{
			line->checksum = static_cast<uint32_t>(line->byte[i - 1]);
		}
	}

}
