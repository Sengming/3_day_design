#pragma once
#include "BaseDecoderInterface.h"

class Clamp1Decoder : public BaseDecoderInterface
{
public:
	Clamp1Decoder();
	~Clamp1Decoder();
	void decodeBytes(DataLinePair* dataToDecode);
private:
	char* m_clampClosed = new char[20];
	char* m_clampOpen = new char[20];

};
