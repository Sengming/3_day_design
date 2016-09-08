#pragma once


enum DeviceType
{
	NO_DEVICE		= 0,
	CLAMP_MODULE_1	= 0x20,
	CLAMP_MODULE_2	= 0x21,
	SPINNER_MODULE,
	FLUID_SENSOR,
	ROCKER_ARM,
	MAGNET_DOOR,
	TOTAL_DEVICES
};

union CommandType_u
{
	char wholeByte;
	struct
	{
		unsigned bit_0 : 1;
		unsigned bit_1 : 1;
		unsigned bit_2 : 1;
		unsigned bit_3 : 1;
		unsigned bit_4 : 1;
		unsigned bit_5 : 1;
		unsigned bit_6 : 1;
		unsigned bit_7 : 1;
	};
};

