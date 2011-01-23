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
// Includes
//=================================================================================
#include <math.h>
#include "libs/lib_unitconverter.h"

//=================================================================================
// Functions
//=================================================================================
// Convert bytes to other size multiplier
long double LIB_UNITCONVERTER_CLASS::ConvertSize(unsigned long bytes, eSizeBytes type)
{
	//determine what conversion they want
	switch (type)
	{
		case BY:
			//convert to bytes (default)
			return bytes;
		case KB:
            //convert to kilobytes
            return (bytes / BYTE_CONVERSION_VALUE);
        case MB:
            //convert to megabytes
            return (bytes / pow((double)BYTE_CONVERSION_VALUE, 2));
        case GB:
            //convert to gigabytes
            return (bytes / pow((long double)BYTE_CONVERSION_VALUE,3));
        /*case eSizeBytes.TB:
            //convert to terabytes
            return (bytes / pow(CONVERSION_VALUE, 4));
        case eSizeBytes.PB:
            //convert to petabyte
            return (bytes / pow(CONVERSION_VALUE, 5));
        case eSizeBytes.EB:
            //convert to exabyte
            return (bytes / pow(CONVERSION_VALUE, 6));*/
        default:
            //default
            return bytes;
    }
}

// Get best fit for bytes size, eg. 1536 Bytes will return 1.5 KiloBytes
long double LIB_UNITCONVERTER_CLASS::FormatByteSize(unsigned long bytes)
{
	/*if (bytes > (long)EB)
		return ConvertSize(bytes, EB);
    if (bytes > (long)PB)
        return ConvertSize(bytes, PB);
    if (bytes > (long)TB)
        return ConvertSize(bytes, TB);*/
	if (bytes > GB)
		return ConvertSize(bytes, GB);
	if (bytes > MB)
		return ConvertSize(bytes, MB);
	return bytes > KB ? ConvertSize(bytes, KB) : bytes;
}

// Convert a size to another, eg. Megabytes to Gigabyte
long double LIB_UNITCONVERTER_CLASS::ConvertSizeToOther(long double value, eSizeBytes from, eSizeBytes to)
{
    if (from == to) return value;
    long double bytes = value;
    switch (from)
    {
        /* case BY:
             bytes = value;
             break;*/
        case KB:
            bytes = value * BYTE_CONVERSION_VALUE;
            break;
        case MB:
            bytes = value * pow((double)BYTE_CONVERSION_VALUE,2);
            break;
        case GB:
            bytes = value * pow((long double)BYTE_CONVERSION_VALUE,3);
            break;
        /*case TB:
            bytes = value * pow((double)BYTE_CONVERSION_VALUE,4);
            break;
        case PB:
            bytes = value * pow((double)BYTE_CONVERSION_VALUE,5);
            break;
        case EB:
            bytes = value * pow((double)BYTE_CONVERSION_VALUE,6);
            break;*/
    }
    return to == BY ? bytes : ConvertSize((unsigned long)bytes, to);
}

// Get the best fit name
const char *LIB_UNITCONVERTER_CLASS::GetSizeNameFromBytes(unsigned long bytes, bool longName /*= true*/)
{
    /*if (bytes > EB)
        return longName ? "Exabyte(s)" : "EB";
    if (bytes > PB)
        return longName ? "Petabyte(s)" : "PB";
    if (bytes > TB)
        return longName ? "Terabyte(s)" : "TB";*/
    if (bytes > GB)
        return longName ? "Gigabyte(s)" : "GB";
    if (bytes > MB)
        return longName ? "Megabyte(s)" : "MB";
    if (bytes > KB)
        return longName ? "Kilobyte(s)" : "KB";
    return longName ? "Byte(s)" : "B";
}