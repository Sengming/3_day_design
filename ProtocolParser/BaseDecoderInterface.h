#pragma once

// include guards probably not needed due to pragma once but adding anyway.
#ifndef BASEDECODERINTERFACE_H_
#define BASEDECODERINTERFACE_H_
#include "DataLine.h"
#include <stdio.h>

class BaseDecoderInterface
{
public:
	~BaseDecoderInterface();
	virtual void decode(DataLinePair* dataToDecode); //leave as void return for now

protected:
	bool m_isValidPair;
	BaseDecoderInterface();

private:
	char* m_timestamp = new char [30];
	char* m_address = new char[30];
};



#endif