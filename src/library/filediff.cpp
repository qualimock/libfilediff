#include "filediff.h"

#include <iostream>
#include <fstream>

extern "C" Borders createBorders(long left, long right) {
    Borders b{left, right};
    return b;
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
