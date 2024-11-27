#pragma once

#include "filediff_directory.h"

typedef struct {
    long left;
    long right;
} Borders;

Borders createBorders(long left, long right);

std::string getFileChunk(const fs::path& file,
                         Borders* aroundChunk,
                         Borders* chunkBorders);


std::vector<Borders> compareFiles(const fs::path& file1,
                                  const fs::path& file2);
