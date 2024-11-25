#include "Directory.hpp"

#include <iostream>
#include <fstream>
#include <xxh3.h>

Directory::Directory()
	: m_path("/usr/bin")
{}

Directory::Directory(const std::string& path)
	: m_path(path)
{}

bool Directory::load() {
	try {
        if (std::filesystem::exists(m_path) && std::filesystem::is_directory(m_path)) {
            for (const auto& entry : std::filesystem::directory_iterator(m_path)) {
                if (std::filesystem::is_regular_file(entry.path())) {
					if (std::filesystem::is_symlink(entry.path())) {
						continue;
					}

					std::cout << "Insert: " << entry.path() << " into " << m_path << std::endl;
                    m_files.insert(std::make_pair(entry.path().filename(), computeHash(entry.path())));
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
