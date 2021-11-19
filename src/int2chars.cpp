#include "int2chars.h"
#include <iostream>

char *int16_2_chars(uint16_t in)
{
    char *little_endian = new char[2];
    little_endian[0] = in;
    little_endian[1] = in >> 8;
    return little_endian;
}

char *int32_2_chars(uint32_t in)
{
    char *little_endian = new char[4];

    little_endian[0] = in;
    little_endian[1] = in >> 8;
    little_endian[2] = in >> 16;
    little_endian[3] = in >> 24;

    return little_endian;
}