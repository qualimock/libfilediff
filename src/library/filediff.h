#pragma once

#include "filediff_directory.h"


std::string showFileChunk(const std::filesystem::path& file, unsigned left, unsigned right, std::pair<unsigned, unsigned> chunk);
