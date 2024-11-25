#include <iostream>
#include "library/filediff.hpp"

int main() {
	Directory systemDir;
	Directory userDir("/home/qualimock/dev/filediff/scrambled");

	systemDir.load();
	userDir.load();

	auto diff = compareDirectories(systemDir, userDir);

	std::cout << "Tampered files:" << std::endl;
	for (auto file : diff) {
		std::cout << file.first << std::endl;
	}
    return 0;
}
