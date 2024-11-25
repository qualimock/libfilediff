#pragma once

#include "Directory.hpp"

#include <vector>

typedef std::vector<std::pair<std::streamoff, std::streamoff>> Chunks;

FilesMap compareDirectories(const Directory& dirA, const Directory& dirB);
Chunks compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2);
