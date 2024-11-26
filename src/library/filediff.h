#pragma once

#include "filediff_directory.h"

FilesMap compareDirectories(const Directory& dirA, const Directory& dirB);

std::string showFileChunk(const std::filesystem::path& file, unsigned left, unsigned right, std::pair<unsigned, unsigned> chunk);
