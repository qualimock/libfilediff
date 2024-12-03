# libfilediff
A shared library for comparing files in specified directories.

The library usage example can be seen in [filediff-gui](https://github.com/qualimock/filediff-gui) utility.

## Prerequisites
To build the library you should use [Meson build system](https://mesonbuild.com)

Library uses [xxHash](https://xxhash.com/) to find differing files.

Meson and xxHash can be installed on your ALT distro via apt-get:
```
apt-get install meson libxxhash-devel
```

## Build and install
Clone the repository:
```
git clone https://github.com/qualimock/libfilediff.git
cd libfilediff
```

Setup Meson:
```
meson setup build
```

Compile the library:
```
meson compile -C build
```

Install the library:
```
cd build
meson install
```

## How to use
If libfilediff is installed using Meson build system, the LD\_LIBRARY_PATH should be set because of Meson's default installation path (/usr/local/).

For example:
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64
```

Meson example
```meson
project('example', 'cpp')

filediff_dep = meson.get_compiler('cpp').find_library('filediff')

executable('example', 'main.cpp', dependencies : [ filediff_dep ])
```

CMake example
```cmake
cmake_minimum_required(VERSION 3.20)
project(example LANGUAGES CXX)

add_executable(example main.cpp)

target_link_libraries(example PRIVATE filediff)
```

Include the library:
```cpp
...
#include <filediff.h>
...
```
## Directory class
```cpp
typedef std::map<fs::path, std::string> FilesMap
```
A map where keys are file paths, and values are files' hashes.

```cpp
Directory::Directory()
```
Creates a default Directory with m_path = "/usr/bin/".

```cpp
Directory::Directory(const std::string& path)
```
Creates a Directory with given path.

```cpp
void Directory::clear()
```
Cleares files in directory and directory path.

```cpp
void Directory::load()
```
Loads files and their hashes from Directory's path.

```cpp
void Directory::load(const std::string& path)
```
Sets Directory's path and call `Directory::load()`

```cpp
FilesMap Directory::compare(const Directory& directory)
```
Compares a Directory with `directory` and returns FilesMap with differing files

```cpp
const fs::path Directory::path() const
```
Returns Directory's path.

```cpp
const FilesMap& Directory::files() const
```
Returns a const reference to Directory's files.

## Public Functions
```cpp
Borders createBorders(long left, long right)
```
Returns Borders struct with given offsets.

```cpp
std::string getFileChunk(const fs::path& file,
                         Borders* aroundChunk,
                         Borders* chunkBorders)
```
Returns file's chunk of bytes with given borders.

```cpp
std::vector<Borders> compareFiles(const fs::path& file1,
                                  const fs::path& file2)
```
Returns an array of Borders of differing parts of given files.
