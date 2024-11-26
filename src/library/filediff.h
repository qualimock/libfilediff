#pragma once

#include "filediff_directory.h"

std::string getFileChunk(const std::filesystem::path& file, unsigned left, unsigned right, std::pair<unsigned, unsigned> chunk);
std::vector<std::pair<long, long>> compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2);
