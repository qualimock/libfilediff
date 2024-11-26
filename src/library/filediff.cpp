#include "filediff.h"

#include <iostream>
#include <fstream>

std::string showFileChunk(const std::filesystem::path& file, unsigned left, unsigned right, std::pair<unsigned, unsigned> chunk) {
    unsigned from = chunk.first - left;
    unsigned to = chunk.second + right;

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
