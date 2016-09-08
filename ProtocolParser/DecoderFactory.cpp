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
		// BWS I would avoid multiple returns, there really is no need here.
		//     revTal = new Clamp1Decoder();
		//     break;
		//   
		//     with return at end.
		return dynamic_cast<BaseDecoderInterface*>(new Clamp1Decoder());  // BWS You do not need to cast to a base class.
		break;
	case CLAMP_MODULE_2:
		return dynamic_cast<BaseDecoderInterface*>(new Clamp2Decoder());
		break;
	default:
		return NULL;
	}

	// BWS You are potentially returning a NULL value.  It is better to avoid NULL as much as possible.
	//     In main() you now have to check for this.
	//     decoder = generateDecoder();
	//     if( decoder != NULL ) {
	//          decoder->decode()
	//     }
	//
	//     A better option in this case would be to return an object of a class type that handles
	//     an unknown address.
	//
	//     class UnknownDecoder {
	//         decode() { /* do nothing */ }
	//     }
    //
	//     default:
	//         retVal = new UnknownDecoder()
	//
	//     In main() you no longer need to check for NULL.

}