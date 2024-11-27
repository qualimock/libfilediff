#include <iostream>
#include "library/filediff.h"

#include <cstring>

int main() {
    Directory dir1;
    Directory dir2("/home/qualimock/dev/libfilediff/scrambled/");

    dir1.load();
    dir2.load();

    auto diff = dir1.compare(dir2);

    Borders aroundChunk = createBorders(20, 20);

    for (auto file : diff) {
        fs::path file1 = dir1.path().generic_string() + file.first.generic_string();
        fs::path file2 = dir2.path().generic_string() + file.first.generic_string();

        std::vector<Borders> v_borders = compareFiles(file1, file2);

        std::cout << "File " <<  file.first.generic_string() << std::endl;
        for (Borders chunkBorders: v_borders) {
            std::cout << file1.generic_string() << ":" << std::endl;
            std::cout << getFileChunk(file1, &aroundChunk, &chunkBorders) << std::endl;

            std::cout << std::endl;

            std::cout << file2.generic_string() << ":" << std::endl;
            std::cout << getFileChunk(file2, &aroundChunk, &chunkBorders) << std::endl;
        }

        std::cout << "--------------------------------" << std::endl;
    }

    return 0;
}
