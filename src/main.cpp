#include <iostream>
#include "library/filediff.h"

#include <cstring>

int main() {
    const char* dir1 = "/usr/bin/";
    const char* dir2 = "/home/qualimock/dev/libfilediff/scrambled/";

    char** diff;
    ccompareDirectories(diff, dir1, dir2);

    for (int i = 0; diff[i] != NULL; ++i) {
        char* file1 = (char*)malloc(strlen(dir1) + strlen(diff[i]) + 1);
        strcpy(file1, dir1);
        strcat(file1, diff[i]);

        char* file2 = (char*)malloc(strlen(dir2) + strlen(diff[i]) + 1);
        strcpy(file2, dir2);
        strcat(file2, diff[i]);

        Borders* borders;
        ccompareFiles(borders, file1, file2);

        Borders around = createBorders(20, 20);

        std::cout << diff[i] << ":" << std::endl;

        for (int j = 0; j != (sizeof(*borders)/sizeof(borders[0])); ++j) {
            std::cout << file1 << std::endl;
            std::cout << borders[j].left << ":" << borders[j].right << std::endl;
            std::cout << cgetFileChunk(file1, &around, &borders[j]) << std::endl;

            std::cout << std::endl;

            std::cout << file2 << std::endl;
            std::cout << borders[j].left << ":" << borders[j].right << std::endl;
            std::cout << cgetFileChunk(file2, &around, &borders[j]) << std::endl;
        }

        std::cout << "-----------------" << std::endl;

        free(borders);
    }

    free(diff);
    return 0;
}
