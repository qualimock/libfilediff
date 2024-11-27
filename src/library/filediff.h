#pragma once

#include "filediff_directory.h"

extern "C" {
    typedef struct {
        long left;
        long right;
    } Borders;

    Borders createBorders(long left, long right);

    const char *cgetFileChunk(const char *file,
                              Borders *aroundChunk,
                              Borders *chunkBorders);

    // remember to free output_diff after usage
    void ccompareDirectories(char**& output_diff,
                             const char* dir1,
                             const char* dir2);

    // remember to free output_borders after usage
    void ccompareFiles(Borders*& output_borders, const char* file1, const char* file2);
}

std::string getFileChunk(const std::filesystem::path& file, Borders* aroundChunk, Borders* chunkBorders);
std::vector<Borders> compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2);
