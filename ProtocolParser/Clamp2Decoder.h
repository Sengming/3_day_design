#pragma once

#include "BaseDecoderInterface.h"

class Clamp2Decoder : public BaseDecoderInterface
{
public:
	Clamp2Decoder();
	~Clamp2Decoder();
	void decodeBytes(DataLinePair* dataToDecode);
private:
	char* m_clampClosed = new char[20];
	char* m_clampOpen = new char[20];

};



