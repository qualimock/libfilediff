#pragma once

#include <filesystem>
#include <map>

typedef std::map<std::string, std::string> FilesMap;

class Directory {
	std::filesystem::path m_path;

	FilesMap m_files;

	std::string computeHash(const std::string& file_path);

public:
	Directory();
	Directory(const std::string& path);

	void clear();
	bool load();
	bool load(const std::string& path);

	Directory(const Directory&) = delete;
	Directory& operator=(const Directory&) = delete;

	const std::string name() const { return m_path; };
	const FilesMap& files() const { return m_files; };
};
