
#include <stdint.h>
#include <stdio.h>
#include "InputFileReader.h"
#include "DecoderFactory.h"
#include "GeneralTypes.h"
#include "Printer.h"

int main(uint32_t argc, char* argv[])
{
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
		fileReader.setFile(argv[1]);
		printerSingleton.openFile(argv[2]);

		for (;fileReader.getEof() == false;)
			{
				pairCommands.lines[0] = fileReader.processLine();

				if (fileReader.getEof())
				{
					break;
				}
				pairCommands.lines[1] = fileReader.processLine();

				if (!fileReader.getEof())
				{
					//printf("Line1: %d\n", pairCommands.lines[0].byte[1]);
					//printf("Line2: %d\n", pairCommands.lines[1].byte[1]);
					decoder = DecoderFactory::generateDecoder(static_cast<DeviceType>(pairCommands.lines[0].byte[0]));
					if (decoder != NULL)
					{
						decoder->decode(&pairCommands);
					}
					delete decoder;
				}
			}
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
