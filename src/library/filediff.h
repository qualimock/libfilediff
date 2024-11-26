#pragma once

#include "filediff_directory.h"

extern "C"
typedef struct {
    long left;
    long right;
} Borders;

extern "C" Borders createBorders(long left, long right);

extern "C" const char* cgetFileChunk(const char* file, Borders* aroundChunk, Borders* chunkBorders);

std::string getFileChunk(const std::filesystem::path& file, Borders* aroundChunk, Borders* chunkBorders);
std::vector<Borders> compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2);
