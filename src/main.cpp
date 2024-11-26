#include <iostream>
#include "library/filediff.h"

int main() {
    Directory systemDir;
    Directory userDir("/home/qualimock/dev/libfilediff/scrambled/");

    if (!systemDir.load()) {
        std::cerr << "Cannot load system dir" << std::endl;
        return -1;
    }

    if (!userDir.load()) {
        std::cerr << "Cannot load user dir" << std::endl;
        return -1;
    }

    auto diff = systemDir.compare(userDir);

    std::cout << std::endl << "Tampered files:" << std::endl;

    for (auto file : diff) {
        auto systemFile = systemDir.files().find(file.first);
        auto userFile = userDir.files().find(file.first);

        auto chunks = compareFiles(systemDir.path() + systemFile->first.generic_string(),
                                   userDir.path() + userFile->first.generic_string());

        std::cout << "System file: " << systemDir.path() << systemFile->first.generic_string()
                  << std::endl << "XXH64: " << systemFile->second << std::endl;
        std::cout << std::endl;

        std::cout << "User file: " << userDir.path() << userFile->first.generic_string()
                  << std::endl << "XXH64: " << userFile->second << std::endl;
        std::cout << std::endl;

        for (auto chunk : chunks) {
            std::cout << systemDir.path() + systemFile->first.generic_string() << ": " << std::endl;
            Borders aroundChunk = createBorders(50, 50);
            const char* chunkStr = cgetFileChunk((systemDir.path() + systemFile->first.generic_string()).c_str(), &aroundChunk, &chunk);
            std::cout << chunkStr << std::endl;
            std::cout << std::endl;

            std::cout << userDir.path() + userFile->first.generic_string() << ": " << std::endl;
            chunkStr = cgetFileChunk((userDir.path() + userFile->first.generic_string()).c_str(), &aroundChunk, &chunk);
            std::cout << chunkStr << std::endl;
            std::cout << std::endl;
        }

        std::cout << "----------------------------" << std::endl;
    }

    return 0;
}
