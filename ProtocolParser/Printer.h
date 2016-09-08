#pragma once
#include <stdio.h>
#include <stdint.h>

enum PrinterFields_e
{
	TIME,					//0
	ADDRESS,				//1
	STATE,					//2
	SUBSTATE,				//3
	STATE_INDEX,			//4
	COMMAND_CLAMP_1,        //5
	COMMAND_CLAMP_2,        //6
	COMMAND_CLAMP_3,        //7
	COMMAND_CLAMP_4,        //8
	COMMAND_CLAMP_5,        //9
	COMMAND_CLAMP_6,        //10
	COMMAND_CLAMP_7,        //11
	COMMAND_CLAMP_8,        //12
	COMMAND_CLAMP_9,        //13
	COMMAND_CLAMP_10,        //14
	COMMAND_CLAMP_11,        //15
	COMMAND_CLAMP_12,        //16
	COMMAND_CLAMP_13,        //17
	COMMAND_CLAMP_14,        //18
	COMMAND_CLAMP_15,        //19
	COMMAND_CLAMP_16,        //20
	COMMAND_CLAMP_17,        //21
	COMMAND_CLAMP_18,        //22
	COMMAND_CLAMP_19,        //23
	COMMAND_CLAMP_20,        //24
	RESPONSE_CLAMP_1,        //25
	RESPONSE_CLAMP_2,        //26
	RESPONSE_CLAMP_3,        //27
	RESPONSE_CLAMP_4,        //28
	RESPONSE_CLAMP_5,        //29
	RESPONSE_CLAMP_6,        //30
	RESPONSE_CLAMP_7,        //31
	RESPONSE_CLAMP_8,        //32
	RESPONSE_CLAMP_9,        //33
	RESPONSE_CLAMP_10,        //34
	RESPONSE_CLAMP_11,        //35
	RESPONSE_CLAMP_12,        //36
	RESPONSE_CLAMP_13,        //37
	RESPONSE_CLAMP_14,        //38
	RESPONSE_CLAMP_15,        //39
	RESPONSE_CLAMP_16,        //40
	RESPONSE_CLAMP_17,        //41
	RESPONSE_CLAMP_18,        //42
	RESPONSE_CLAMP_19,        //43
	RESPONSE_CLAMP_20,		  //44
	TOTAL_FIELDS,
	FIELD_NONE
};

struct BufferElement
{
	char** dataStringPointer;
	PrinterFields_e field;
};

class Printer
{
public:
	Printer();
	~Printer();

	void printToBuffer(PrinterFields_e field, char** string);
	void printToFile();
	void reset();
	void openFile(char* fileToOpen);
	void closeFile();
private:
	// Our happy print buffer
	BufferElement buffer[100];
	uint32_t m_currentIndex;
	void initialize();
	FILE* m_file;
	const char m_headerStrings[TOTAL_FIELDS][100] =
	{
		{"TIME"},					//0
		{"ADDRESS"},				//1
		{"STATE"},					//2
		{"SUBSTATE"},				//3
		{"STATE_INDEX"},			//4
		{"COMMAND_CLAMP_1"},        //5
		{"COMMAND_CLAMP_2"},        //6
		{"COMMAND_CLAMP_3"},        //7
		{"COMMAND_CLAMP_4"},        //8
		{"COMMAND_CLAMP_5"},        //9
		{"COMMAND_CLAMP_6"},        //10
		{"COMMAND_CLAMP_7"},        //11
		{"COMMAND_CLAMP_8"},        //12
		{"COMMAND_CLAMP_9"},        //13
		{"COMMAND_CLAMP_10"},        //14
		{"COMMAND_CLAMP_11"},        //15
		{"COMMAND_CLAMP_12"},        //16
		{"COMMAND_CLAMP_13"},        //17
		{"COMMAND_CLAMP_14"},        //18
		{"COMMAND_CLAMP_15"},        //19
		{"COMMAND_CLAMP_16"},        //20
		{"COMMAND_CLAMP_17"},        //21
		{"COMMAND_CLAMP_18"},        //22
		{"COMMAND_CLAMP_19"},        //23
		{"COMMAND_CLAMP_20"},        //24
		{"RESPONSE_CLAMP_1"},        //25
		{"RESPONSE_CLAMP_2"},        //26
		{"RESPONSE_CLAMP_3"},        //27
		{"RESPONSE_CLAMP_4"},        //28
		{"RESPONSE_CLAMP_5"},        //29
		{"RESPONSE_CLAMP_6"},        //30
		{"RESPONSE_CLAMP_7"},        //31
		{"RESPONSE_CLAMP_8"},        //32
		{"RESPONSE_CLAMP_9"},        //33
		{"RESPONSE_CLAMP_10"},        //34
		{"RESPONSE_CLAMP_11"},        //35
		{"RESPONSE_CLAMP_12"},        //36
		{"RESPONSE_CLAMP_13"},        //37
		{"RESPONSE_CLAMP_14"},        //38
		{"RESPONSE_CLAMP_15"},        //39
		{"RESPONSE_CLAMP_16"},        //40
		{"RESPONSE_CLAMP_17"},        //41
		{"RESPONSE_CLAMP_18"},        //42
		{"RESPONSE_CLAMP_19"},        //43
		{"RESPONSE_CLAMP_20"}		  //44
	};
};

extern Printer printerSingleton;
