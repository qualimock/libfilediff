#include "filediff.h"

#include <iostream>
#include <fstream>
#include <cstring>

extern "C" {
    Borders createBorders(long left, long right) {
        Borders b{left, right};
        return b;
    }

    const char* cgetFileChunk(const char* file, Borders* aroundChunk, Borders* chunkBorders) {
        const char* chunk = strdup(getFileChunk(std::filesystem::path(file), aroundChunk, chunkBorders).c_str());
        return chunk;
    }

    void ccompareDirectories(char**& output_diff, const char* dir1, const char* dir2) {
        Directory d1(dir1);
        Directory d2(dir2);

        std::cout << "Loading directory " << dir1 << std::endl;
        if (!d1.load()) {
            std::cerr << "Cannot load " << dir1 << std::endl;
            return;
        }

        std::cout << "Loading directory " << dir2 << std::endl;
        if (!d2.load()) {
            std::cerr << "Cannot load " << dir2 << std::endl;
            return;
        }

        auto diff = d1.compare(d2);

        output_diff = (char**)malloc((diff.size()+1) * sizeof(char*));

        int count = 0;
        for (auto file : diff) {
            output_diff[count] = strdup(file.first.c_str());
            count++;
        }

        output_diff[count] = NULL;
    }

    void ccompareFiles(Borders*& output_borders, const char* file1, const char* file2) {
        std::vector<Borders> borders = compareFiles(file1, file2);
        output_borders = (Borders*)malloc(sizeof(borders) * sizeof(Borders));

        for (size_t i = 0; i < borders.size(); ++i) {
            output_borders[i] = borders[i];
        }
    }
}

std::string getFileChunk(const std::filesystem::path& file, Borders* aroundChunk, Borders* chunk) {
    long from = chunk->left - aroundChunk->right;
    long to = chunk->left + aroundChunk->right;

    std::ifstream f(file, std::ios::binary | std::ios::ate);

    if (!f.is_open()) {
        std::cerr << "showFileChunk: Unable to open file" << std::endl;
        return std::string();
    }

    f.seekg(from);

    char byte;
    std::string buf;

    while (f.get(byte) && f.tellg() != to+1) {
        buf += byte;
    }

    return buf;
}

std::vector<Borders> compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2) {
    std::ifstream f1(file1, std::ios::binary | std::ios::ate);
    std::ifstream f2(file2, std::ios::binary | std::ios::ate);

    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "compareFiles: Unable to open one or both files!" << std::endl;
        return std::vector<Borders>();
    }

    f1.seekg(0);
    f2.seekg(0);

    std::vector<Borders> chunks;

    char byte1, byte2;
    std::streamoff begin, end;
    bool foundCorruption = false;

    while (f1.get(byte1) && f2.get(byte2)) {
        if (byte1 != byte2 && !foundCorruption) {
            begin = f1.tellg();
            foundCorruption = true;
        }

        if (byte1 == byte2 && foundCorruption) {
            end = f1.tellg();
            chunks.push_back(createBorders(begin, end));
            foundCorruption = false;
        }
    }

    return chunks;
}
