#pragma once
#ifndef DECODERFACTORY_H_
#define DECODERFACTORY_H_
#include <stdint.h>
#include "GeneralTypes.h"
#include "BaseDecoderInterface.h"


class DecoderFactory
{
public:
	DecoderFactory();
	virtual ~DecoderFactory() = 0;
	static BaseDecoderInterface* generateDecoder(DeviceType decoderCode);

private:

};









#endif