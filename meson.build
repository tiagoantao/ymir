project('ymir', 'c',
  version : '0.0.1',
  default_options : ['warning_level=3'])

# Versioning
project_version = meson.project_version()
version_array = project_version.split('.')
version_major = version_array[0]
version_minor = version_array[1]
version_patch = version_array[2]
conf = configuration_data()
conf.set('VERSION_MAJOR', version_major)
conf.set('VERSION_MINOR', version_minor)
conf.set('VERSION_PATCH', version_patch)

# Dependencies
glib_dep = dependency('glib-2.0', version : '>= 2.40', required : true)
png_dep = dependency('libpng', required : true)

# Dev dependencies
check_dep = dependency('check')

# Include directories
inc_dirs = include_directories('include')

# Source files
src_files = files('src/fs.c', 'src/graphics.c')

# Library
ymir = library('ymir',
  src_files, include_directories : inc_dirs, install : true,
  dependencies : [glib_dep, png_dep])


# Tests
test_files = files('tests/test_graphics.c')
test_executable = executable(
  'test_executable', test_files,
  include_directories : inc_dirs,
  link_with: ymir,
  dependencies : [check_dep])
test('test_graphics', test_executable)

# Installation
header_files = files('include/fs.h', 'include/graphics.h')
install_headers(header_files, subdir : 'ymir')
#install_man, install_data

# Configuration
#configure_file(output : 'config.h', configuration : conf)

