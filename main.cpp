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
    ifstream imageFile("promo.png", ios::binary);
    if (!imageFile.is_open())
    {
        cout << "Not open file" << endl;
        return 1;
    }

    imageFile.seekg(0, ios::end);
    size_t fileSize = imageFile.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;
    imageFile.seekg(0, ios::beg);

    vector<char> fileData(fileSize);
    imageFile.read(fileData.data(), fileSize);


    return 0;
}
