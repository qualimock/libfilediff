library_sources = [
  'filediff.cpp',
]

library = shared_library(
  'filediff',
  library_sources,
  install : true
)

library_dep = declare_dependency(
  include_directories : include_directories('.'),
  link_with : library
)
