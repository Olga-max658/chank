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
    size_t position = 8;
    uint32_t totalBytesRead = 8;

    while (position < fileData.size())
    {
        PNGChunk* currentChunk = reinterpret_cast<PNGChunk*>(&fileData[position]);
        uint32_t chunkLength = Reverse_DWord(currentChunk->length);

        string chunkType(reinterpret_cast<char*>(&currentChunk->type), 4);
        uint32_t chunkChecksum = Reverse_DWord(currentChunk->CRC);

        cout << "Chunk size: " << chunkLength << endl;
        cout << "Chunk type: " << chunkType << endl;

        position = position + sizeof(PNGChunk) + chunkLength;
        totalBytesRead += chunkLength + sizeof(PNGChunk);

        if (chunkType == "IEND")
        {
            cout << "Actual file size: " << totalBytesRead << " bytes" << endl;
            break;
        }
    }

    return 0;
}
