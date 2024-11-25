#include "filediff.hpp"

#include <iostream>
#include <algorithm>

FilesMap compareDirectories(const Directory& dirA, const Directory& dirB) {
	FilesMap diff;
	std::set_symmetric_difference(dirA.files().begin(), dirA.files().end(),
								  dirB.files().begin(), dirB.files().end(),
								  std::inserter(diff, diff.begin()));
	return diff;
}
