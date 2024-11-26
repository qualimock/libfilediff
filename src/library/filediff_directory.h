#pragma once

#include <filesystem>
#include <map>
#include <vector>

//                    file path          file hash
typedef std::map<std::filesystem::path, std::string> FilesMap;

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

    FilesMap compare(const Directory& directory);

    Directory(const Directory&) = delete;
    Directory& operator=(const Directory&) = delete;

    const std::string path() const { return m_path; };
    const FilesMap& files() const { return m_files; };
};
