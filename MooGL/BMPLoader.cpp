#include <iostream>
#include <fstream>
#include "BMPLoader.h"

void loadBitMap(const char* fileName, const char* outFileName) {
    bmpfile_ft magic;
    bmpfile_header header;
    int row, col;
    bmp_colour* image_buffer;

    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName, std::ios::binary);
    outFile.open(outFileName, std::ios::binary);
    if (!inFile.is_open())
    {
        std::cout << "\ncan't open input " << fileName << "\n";
        exit(1);
    }
    std::cout << "\nOpened file\n";
    inFile.read(reinterpret_cast<char*>(&magic), sizeof(bmpfile_ft));
    inFile.read(reinterpret_cast<char*>(&header), sizeof(bmpfile_header));
    inFile.read(reinterpret_cast<char*>(&bitMapInfo), sizeof(BMPINFOHEADER));
    if (bitMapInfo.width != bitMapInfo.height)
    {
        std::cout << "\nBitmap is not square\n";
        exit(1);
    }

    // create a buffer to hold each line as it is read in
    image_buffer = new bmp_colour[bitMapInfo.width];

    for (row = 0; row < bitMapInfo.height; row++) {
        inFile.read(reinterpret_cast<char*>(image_buffer), sizeof(bmp_colour) * bitMapInfo.width);
        // bmp files store colours in the order blue, green, red
        // need to rearrange to the order red, green, blue
        for (col = 0; col < bitMapInfo.width; col++)
        {
            outFile.put(image_buffer[col].r);
            outFile.put(image_buffer[+col].g);
            outFile.put(image_buffer[col].b);
        }
    }

    // close the .bmp file and free up memory
    inFile.close();
    outFile.close();
    delete[] image_buffer;
}