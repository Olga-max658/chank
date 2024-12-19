#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <Windows.h>

using namespace std;

#pragma pack(push, 1)

struct PNGChunk
{
    uint32_t length;
    uint32_t type;
    uint32_t CRC;
};

#pragma pack(pop)

DWORD Reverse_DWord(DWORD in)
{
    return ((in >> 24) & 0xFF) | ((in >> 8) & 0xFF00) |
           ((in << 8) & 0xFF0000) | ((in << 24) & 0xFF000000);
}

int main()
{


    return 0;
}
