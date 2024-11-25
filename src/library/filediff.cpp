#include "filediff.hpp"

#include <iostream>
#include <algorithm>
#include <fstream>

FilesMap compareDirectories(const Directory& dirA, const Directory& dirB) {
	FilesMap diff;
	std::set_symmetric_difference(dirA.files().begin(), dirA.files().end(),
								  dirB.files().begin(), dirB.files().end(),
								  std::inserter(diff, diff.begin()));
	return diff;
}

Chunks compareFiles(const std::filesystem::path& file1, const std::filesystem::path& file2) {
    std::ifstream f1(file1, std::ios::binary | std::ios::ate);
    std::ifstream f2(file2, std::ios::binary | std::ios::ate);

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
