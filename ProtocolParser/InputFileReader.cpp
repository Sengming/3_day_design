
#include "InputFileReader.h"
#include <string.h>
#include <stdlib.h>


InputFileReader::InputFileReader() : m_pfile(NULL), m_eof(false)
{
	// Intentionally left blank
}

InputFileReader::~InputFileReader()
{
	// Intentionally left blank
}

bool InputFileReader::setFile(char* filename)
{
	m_pfile = fopen(filename, "r");

	// BWS Ok, one more comment on error handling  :)
	//     I would code the check for m_pfile == NULL right away and not leave this for later.
	//     Again, it is way too easily missed and forgotten.
    //
	//     if( m_pfile == NULL ) throw exception with some description.
	return true;
}

DataLine InputFileReader::processLine()
{
	// BWS a precondition to calling this method is that setFile() was called AND m_pfile is != NULL
	//     You must either check for that precondition:
	//         assert( m_pfile != NULL ) 
	//     thus, pushing the burden of performing the setup and checking that it worked to a higher level.
	//     or you could enforce it in your constructor.
	//    
	//     How much work is done in the constructor is debated... but I think in this case your
	//     class is useless without having opened a file.
	DataLine tempData;
	if (fgets(m_copiedstring, MAX_STRING_LENGTH, m_pfile) == NULL)
	{
		m_eof = true;
	}
	else
	{
		if (m_copiedstring[strlen(m_copiedstring) - 1] == '\n')
		{
			m_copiedstring[strlen(m_copiedstring) - 1] = '\0';
		}

		stringChopper(m_copiedstring, &tempData);  
		// BWS stringChopper() is an intersting name.
		//
        // It is good to name functions with a verbNoun.
		// What is stringChopper() really doing?
		//     1. extracting the timestamp
		//     2. determining IoDirection (TX/RX)
		//     3. breaking the remaining line into bytes
		//     4. capturing the checksum
		//
		//  First that is a list of 4 seperate responsibilities and should
		//  probably be four functions with good names.
		//      extractTimestamp(), determineIoDirection(), extractBytes(), extractChecksum()
		//
		//  Now, to do this, especially for a streaming protocol, we want to try to do zero (or very few) copies of data.
		//  You are already on track with this by passing addresses.
		//  However, two things:  
		//     1. there is already a copy of tempData because it is local to this method and returned by copy.
		//        This could be fixed by declaring a DataLine in main() and passing it by reference to this
		//        function to be filled in.
		//        void InputFileReader::processLine( DataLine& data );
		//        You are then "filling in a request" rather than "returning a copy".
		//
		//     2. I would pass be reference rather than pointer in the call to stringChopper (or the new methods)
		//        void InputFileReader::stringChopper( char* rawString, DataLine& line )

	}
	return tempData;
}

inline void InputFileReader::stringChopper(char* rawString, DataLine* line)
{
	char* tempChar;

	// BWS: Yes at some point you need the code that does some messy work  :)
	//      Just one comment:  I would try to learn something new besides strtok.
	//      It relies on global data and is not re-entrant.  Which means this technique
	//      would not be OK for a multi-threaded environment.
	//      I'm going to encourage that you ask around, check out google, look at the std library
	//      for string, etc...

	tempChar = strtok(rawString, "\t");
	line->timeStamp = strtod(tempChar, NULL);

	tempChar = strtok(NULL, "\t");
	if (!strcmp(tempChar, "TX"))
	{
		line->IoDirection = TX;
	}
	else if (!strcmp(tempChar, "RX"))
	{
		line->IoDirection = RX;
	}

	for (uint32_t i = 0; tempChar != NULL; i++)
	{
		tempChar = strtok(NULL, "\t");
		if (tempChar != NULL)
		{
			line->byte[i] = (char)strtol(tempChar, NULL, 16);
		}
		else
		{
			line->checksum = static_cast<uint32_t>(line->byte[i - 1]);
		}
	}

}
