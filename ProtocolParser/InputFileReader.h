#pragma once
#ifndef INPUTFILEREADER_H_
#define INPUTFILEREADER_H_

#include <stdio.h>
#include <stdint.h>
#include "DataLine.h"
#define MAX_STRING_LENGTH 1000

class InputFileReader
{
public:
	InputFileReader();
	~InputFileReader();

	bool setFile(char* filename);
	DataLine processLine();
	bool getEof() { return m_eof; }

private:
	FILE* m_pfile;
	DataLine m_data;
	char m_copiedstring[MAX_STRING_LENGTH];
	inline void stringChopper(char* rawString, DataLine* line);
	bool m_eof;
};




#endif