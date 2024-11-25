library_sources = [
  'Directory.cpp',
  'filediff.cpp',
]

xxhash_dep = dependency('libxxhash', required : true)

library = shared_library(
  'filediff',
  library_sources,
  dependencies : [ xxhash_dep ],
  install : true
)

library_dep = declare_dependency(
  include_directories : include_directories('.'),
  link_with : library
)
