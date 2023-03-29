#pragma once

#include <iostream>

typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;

typedef struct {
    unsigned char magic[2];
} bmpfile_ft;

typedef struct {
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;
} bmpfile_header;

typedef struct {
    uint32_t header_sz;
    int32_t width;
    int32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    int32_t hres;
    int32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;
} BMPINFOHEADER;

typedef struct {
    unsigned char b, g, r;
} bmp_colour;

BMPINFOHEADER bitMapInfo;

void loadBitMap(const char* fileName, const char* outFileName);