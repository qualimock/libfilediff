#include <iostream>
#include "library/filediff.hpp"

int main() {
	Directory systemDir("/home/qualimock/dev/filediff/original");
	Directory userDir("/home/qualimock/dev/filediff/scrambled");

	systemDir.load();
	userDir.load();
    return 0;
}
