#include <iostream>
#include "library/filediff.hpp"

int main() {
    Directory systemDir;
    Directory userDir("/home/qualimock/dev/filediff/scrambled/");

    systemDir.load();
    userDir.load();

    auto diff = compareDirectories(systemDir, userDir);

    std::cout << std::endl << "Tampered files:" << std::endl;
    for (auto file : diff) {
        auto systemFile = systemDir.files().find(file.first);
        auto userFile = userDir.files().find(file.first);

        std::cout << "System file: " << systemDir.path() << systemFile->first.generic_string()
                  << std::endl << "XXH64: " << systemFile->second << std::endl;
        std::cout << std::endl;

        std::cout << "User file: " << userDir.path() << userFile->first.generic_string()
                  << std::endl << "XXH64: " << userFile->second << std::endl;
        std::cout << std::endl;

        auto file1 = std::filesystem::path(systemDir.path() + systemFile->first.generic_string());
        auto file2 = std::filesystem::path(userDir.path() + userFile->first.generic_string());
        auto chunks = compareFiles(file1, file2);

        for (auto chunk : chunks) {
            std::cout << systemDir.path() + systemFile->first.generic_string() << ": " << std::endl;
            std::cout << showFileChunk(systemDir.path() + systemFile->first.generic_string(), 50, 50, chunk) << std::endl;
            std::cout << std::endl;

            std::cout << userDir.path() + userFile->first.generic_string() << ": " << std::endl;
            std::cout << showFileChunk(userDir.path() + userFile->first.generic_string(), 50, 50, chunk) << std::endl;
            std::cout << std::endl;
        }

        std::cout << "----------------------------" << std::endl;
    }

    return 0;
}
