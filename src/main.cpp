#include <iostream>
#include "library/filediff.hpp"

int main() {
	Directory systemDir;
	Directory userDir("/home/qualimock/dev/filediff/scrambled/");

	systemDir.load();
	userDir.load();

	auto diff = compareDirectories(systemDir, userDir);

	std::cout << std::endl << "Tampered files:" << std::endl;
	for (auto file : diff) {
		auto systemFile = systemDir.files().find(file.first);
		auto userFile = userDir.files().find(file.first);

		std::cout << "System file: " << systemDir.path() << systemFile->first.generic_string() << "    XXH64: " << systemFile->second << std::endl;
		std::cout << "User file: " << userDir.path() << userFile->first.generic_string() << "      XXH64: " << userFile->second << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
