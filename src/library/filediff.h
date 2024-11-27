#pragma once

#include "filediff_directory.h"

typedef struct {
    long left;
    long right;
} Borders;

Borders createBorders(long left, long right);

std::string getFileChunk(const std::filesystem::path& file,
                         Borders* aroundChunk,
                         Borders* chunkBorders);


std::vector<Borders> compareFiles(const std::filesystem::path& file1,
                                  const std::filesystem::path& file2);
