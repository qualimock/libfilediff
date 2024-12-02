#pragma once

#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
  #include <experimental/filesystem>
  namespace fs = std::experimental::filesystem;
#else
  error "Missing the <filesystem> header."
#endif

#include <map>
#include <vector>

//                    file path          file hash
typedef std::map<fs::path, std::string> FilesMap;

class Directory {
    fs::path m_path;

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

    const fs::path path() const { return m_path; };
    const FilesMap& files() const { return m_files; };
};
