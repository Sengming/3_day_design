#include "DecoderFactory.h"
#include "GeneralTypes.h"
#include "Clamp1Decoder.h"
#include "Clamp2Decoder.h"

// Abstract factory is probably better to stay true to the whole open for extension, closed for modification concept, but is it really needed here? I'll leave this as a factory method for now.
// Perhaps we can discuss and optimize/change later.


DecoderFactory::DecoderFactory()
{
}

DecoderFactory::~DecoderFactory()
{
}

BaseDecoderInterface* DecoderFactory::generateDecoder(DeviceType decoderCode) 
{
	BaseDecoderInterface* retVal = NULL;
	switch (decoderCode)
	{
	case CLAMP_MODULE_1:
		return dynamic_cast<BaseDecoderInterface*>(new Clamp1Decoder());
		break;
	case CLAMP_MODULE_2:
		return dynamic_cast<BaseDecoderInterface*>(new Clamp2Decoder());
		break;
	default:
		return NULL;
	}

}