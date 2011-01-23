#ifndef LIB_UNITCONVERTER_H
#define LIB_UNITCONVERTER_H
//========= Copyright © 2010-2011, Tiago Conceição, All rights reserved. ============
//									Plugin Template							 
//
//						Please Read (LICENSE.txt) and (README.txt)
//								   Dont Forget Visit:
//								(http://www.sourceplugins.com) -> VPS Plugins
//		(http://www.sourcemm.net)  (http://forums.alliedmods.net/forumdisplay.php?f=52) - MMS Plugins
//
//===================================================================================

//=================================================================================
// Defines
//=================================================================================
#define LIB_UNITCONVERTER_VERSION "1.0"
#define LIB_UNITCONVERTER_CLASS CUnitConverterLib
//#define BYTE_CONVERSION_VALUE 1024;

//=================================================================================
// Class
//=================================================================================
class LIB_UNITCONVERTER_CLASS
{
public:
	static const unsigned int BYTE_CONVERSION_VALUE = 1024; 
	enum eSizeBytes
        {
            // Byte
            BY = 1, // Byte
            // Kilobyte
            KB = BYTE_CONVERSION_VALUE * BY, // Kilobyte  
            // Megabyte
            MB = BYTE_CONVERSION_VALUE * KB, // Megabyte
            // Gigabyte
            GB = BYTE_CONVERSION_VALUE * MB, // Gigabyte
            /*// Terabyte
            TB = BYTE_CONVERSION_VALUE * GB, // Terabyte
            // Petabyte
            PB = BYTE_CONVERSION_VALUE * TB, // Petabyte
            // Exabyte
            EB = BYTE_CONVERSION_VALUE * PB  // Exabyte*/
        };

	// Convert bytes to other size multiplier
	static long double ConvertSize(unsigned long bytes, eSizeBytes type);

	// Get best fit for bytes size, eg. 1536 Bytes will return 1.5 KiloBytes
	static long double FormatByteSize(unsigned long bytes);

	// Convert a size to another, eg. Megabytes to Gigabyte
	static long double ConvertSizeToOther(long double value, eSizeBytes from, eSizeBytes to);

	// Get the best fit name
	static const char *GetSizeNameFromBytes(unsigned long bytes, bool longName = true);
	
};

#endif