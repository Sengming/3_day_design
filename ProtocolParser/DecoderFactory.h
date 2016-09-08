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

	// BWS: So you have a single static method in a class.  This could just be a function.
	//      Everything doesn't need to be a class (like in Java - if I remember Java correctly).
	static BaseDecoderInterface* generateDecoder(DeviceType decoderCode);

private:

};









#endif