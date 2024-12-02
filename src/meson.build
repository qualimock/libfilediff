library_sources = [
  'filediff_directory.cpp',
  'filediff.cpp',
]

xxhash_dep = dependency('libxxhash', required : true)

library = shared_library(
  'filediff',
  library_sources,
  dependencies : [ xxhash_dep ],
  version: '0.2.1',
  soversion : 0,
  install : true
)

install_headers(['filediff_directory.h', 'filediff.h'])

library_dep = declare_dependency(
  include_directories : include_directories('.'),
  link_with : library
)
