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

	// BWS Why call new for a char array of [30].
	//     I realize this puts the data in the heap rather than the stack.  If there was a LOT of data
	//     that might be important.  You may consider using stl::string instead.
	//
	//     Of greater concern is that you now created a class which:
	//          a) you are not preventing copies of, because you are not declaring the copy constructor
	//             and assignment operator private.
	//
	//          b) this will create a default copy constructor
	//
	//          c) if copied will do a 'shallow' copy of m_timestamp and m_address. This means that
	//             two objects (the original and the copy) will actually point to the same memory
	//             for m_timestamp and m_address
	//
	//             They will share/overwrite the same value.
	//             If one is deleted, the other will now point to invalid memory, and will
	//             try to incorrectly delete the same memory twice.
	//
	//     At a minimum, if did want copies of objects to share the same memory, you would want to
	//     look at using std::shared_ptr

	//  I know I may be over-conservative, but C++ copying objects without you realizing it is a common
	//  mistake that is hard to debug.  I generally author all of my classes to not allow copying.
	//  When the compiler tells me it is trying to copy, I then decide if I want to allow it and 
	//  subsequently implement my class to make sure it copies correctly.
	//       #define DoNotCopy( c )  c(c const& other); c& operator=(c const& other)
	//           
	//       class MyClass {
	//           private:
	//               DoNotCopy( myClass );
	//       }
};



#endif