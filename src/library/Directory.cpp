#include "Directory.hpp"

#include <iostream>
#include <fstream>

Directory::Directory()
	: m_path("/usr/bin")
{}

Directory::Directory(const std::string& path)
	: m_path(path)
{}

bool Directory::load() {
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
