#include "filediff_directory.h"

#include <iostream>
#include <fstream>
#include <xxh3.h>

Directory::Directory()
    : m_path("/usr/bin/")
{}

Directory::Directory(const std::string& path)
    : m_path(path)
{
    if (m_path.generic_string().back() != '/') {
        m_path = std::filesystem::path(m_path.generic_string() + '/');
    }
}

bool Directory::load() {
    try {
        if (std::filesystem::exists(m_path) && std::filesystem::is_directory(m_path)) {
            for (const auto& entry : std::filesystem::directory_iterator(m_path)) {
                if (std::filesystem::is_regular_file(entry.path())) {
                    if (std::filesystem::is_symlink(entry.path())) {
                        std::cout << "Skipping symlink " << entry.path().generic_string() << std::endl;
                        continue;
                    }

                    try{
                        m_files.insert(std::make_pair(entry.path().filename(), computeHash(entry.path())));
                    } catch (const std::runtime_error& e) {
                        std::cout << "Skipping " << entry.path().generic_string() << " due to lack of permissions" << std::endl;
                        continue;
                    }
                }
            }

            return true;
        } else {
            std::cerr << "Directory does not exist or is not a directory." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }

    return false;
}

bool Directory::load(const std::string &path) {
    if (!(std::filesystem::exists(path) || std::filesystem::is_directory(path))) {
        return false;
    }

    clear();
    m_path = path;
    return load();
}

void Directory::clear() {
    m_path.clear();
    m_files.clear();
}


std::string Directory::computeHash(const std::string& file_path) {
    const size_t buffer_size = 8192;
    char buffer[buffer_size];

    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + file_path);
    }

    XXH64_state_t* state = XXH64_createState();
    if (!state) {
        throw std::runtime_error("Failed to create xxHash state.");
    }
    XXH64_reset(state, 0);

    while (file.read(buffer, buffer_size)) {
        XXH64_update(state, buffer, file.gcount());
    }
    XXH64_update(state, buffer, file.gcount());

    uint64_t hash = XXH64_digest(state);
    XXH64_freeState(state);

    std::ostringstream result;
    result << std::hex << hash;
    return result.str();
}

Chunks Directory::compareFiles(const std::filesystem::path& file) {
    std::ifstream f1(m_path, std::ios::binary | std::ios::ate);
    std::ifstream f2(file, std::ios::binary | std::ios::ate);

    if (!f1.is_open() || !f2.is_open()) {
        std::cerr << "compareFiles: Unable to open one or both files!" << std::endl;
        return Chunks();
    }

    f1.seekg(0);
    f2.seekg(0);

    Chunks chunks;

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
            chunks.push_back(std::make_pair(begin, end));
            foundCorruption = false;
        }
    }

    return chunks;
}
