
#include <stdint.h>
#include <stdio.h>
#include "InputFileReader.h"
#include "DecoderFactory.h"
#include "GeneralTypes.h"
#include "Printer.h"

int main(uint32_t argc, char* argv[])
{
	// BWS I see the responsibilities in main() as you have coded it to be:
	//     1. parse the command line
	//     2. open the I/O files
	//     3. Read the input file
	//     4. Pair up TX/RX lines
	//     5. Decode the lines
	//
	//     the responsibility of main() will likely be to coordinate the flow and interfaces between these, but main
	//     can be much shorter and clear in the flow.  Let main focus on the flow and handoff of data between the interfaces.
	//     Let other functions or classes do the work.
	//
	//     Example:
	//         Step 1:  parseTheCommandLine()                        Input:  argc, argv    Output: input/output filename
	//         Step 2:  construct fileReader and printerSingleton    Input:  input/output filename
	//         Step 3:  readNextLine()                               Input:  fileReader    Output: line
	//         Step 4:  pairTxRxLines()                              Input:  line          Output: linePair if successful
	//         Step 5:  decodeLinePair()                             Input:  linePair
	//
	//     Hopefully, this makes sense and you see how this helps with the first step of understanding the program flow, the
	//     individual responsibilities, and the clear interfaces between each step.  main() coordindates the flow and interfaces.
	//
	//     Yet, if desired each step could easily be tested seperately, changed, etc...
	//
	// BWS Since main() is doing work (in this case parsing the command line AND doing detailed coordination of parsing the file) you see
	//     how you end up with variables declared which are a good distance away from their use.  
	//     For example pairCommands is declared up here, but not used until several lines and levels of indentation later.
	InputFileReader fileReader;
	DataLinePair	pairCommands;

	BaseDecoderInterface* decoder;
	switch (argc)
	{
	case 0:
	case 1:
		printf("Invalid params!\n");
		return -1;
		break;
	case 3:
		// Great!

		// BWS I would seperate this file parsing logic out from the command line argument parsing logic.
		//     It is too seperate concepts which can be very loosely coupled.  The output from command line
		//     parsing is an input to the parsing.
		//
		//     Coupling them, by embedding parsing logic within the command line logic, adds complexity and
		//     makes maintenance a bit more difficult, such as if you do something in the default: statement
		//     below to move forward with defaults.

		fileReader.setFile(argv[1]);  // BWS (I know you were going to add 'error handling'  but I suggest that you think about this differently.
		                              //     As you write the code initially, write it to detect and propogate the errors.  Then if you want to leave
		                              //     the decision and implementation for how to "handle" or possibly "recover" from those errors, that is ok.
		                              //     In this case, setFile() returns a result.  You should definitely code on your first pass to check for the result.
		                              //     This is too easily forgotten later.
		                              //
		                              //     Also, instead of returning a boolean result.  I would strongly encourage, throwing an exception from
		                              //     setFile() if it fails.  This keeps these things from being missed and saves you a lot of code.
		printerSingleton.openFile(argv[2]);

		for (;fileReader.getEof() == false;)
			{
				pairCommands.lines[0] = fileReader.processLine();

				if (fileReader.getEof())
				{
					break;
				}
				pairCommands.lines[1] = fileReader.processLine();

				// BWS you do the eof logic differently.  I would have both cases mirror each other.
				//     This would simplify understanding and prevent error.
				//
				//     pairCommands.lines[0] = fileReader.processLine()
				//     if( fileReader.getEof() ) { break; }
				//
				//     pairCommands.lines[1] = fileReader.processLine()
				//     if( fileReader.getEof() ) { break; }
				//
				//     ... continue with the logic ...

				if (!fileReader.getEof())
				{
					//printf("Line1: %d\n", pairCommands.lines[0].byte[1]);
					//printf("Line2: %d\n", pairCommands.lines[1].byte[1]);

					// BWS: I like the idea of a factory that returns a concrete decorder with an abstract interface.
					//
					//      I am not sure you should make the leap from a data byte to an enumeration.  You can end up
					//      with a 'value' that is not a valid value for the DeviceType enumeration.
					decoder = DecoderFactory::generateDecoder(static_cast<DeviceType>(pairCommands.lines[0].byte[0]));   // BWS will you always have a byte[0]?  I know you indicated you will add error handling.
					                                                                                                     //     That is ok.  But, I would try to develop a programming style where you are checking
					                                                                                                     //     basic things like boundaries, NULL pointers, etc... as you write the code the first 
					                                                                                                     //     time.  This level of detail will be easy to overlook when you add error handling later.
					                                                                                                     //     At a minimum, assert or throw an exception and leave that 'unhandled'.
					if (decoder != NULL)
					{
						// BWS Do you see how the complexity to get to this step is very deep?
						//          switch() {
						//              for() {
						//                  if() {
						//                       if() {
                        //
						// This makes it difficult to understand what it takes to get to this code.  It is a lot
						// to understand all at once.  My fear is that as you start adding error handling, this
						// will just get more complex and deeper.
						decoder->decode(&pairCommands);
					}
					delete decoder;
				}
			}
		// BWS I do not like a Singleton for this case.  At a minimum, this breaks the possibility of unit testing the decoders easily.
		//
		//     I think you should define an Interface for streaming out data.  Then pass that interface to the decoders.  In main you
		//     would construct a concrete definition of that interface which in this case would stream the output to a file.  Doing this,
		//     would allow automated unit test of the decoders (if you wanted to do that - not needed for this effort), with a mock
		//     output stream.
		printerSingleton.closeFile();
		break;
	default:
		// fallthrough:
		printf("Haven't handled this case yet, probably generate default filename\n");
		return 0;
	}

	printf("Parsing complete!\n");

	return 0;
}
