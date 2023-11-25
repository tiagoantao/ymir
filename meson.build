project('ymir', 'c',
  version : '0.0.1',
  default_options : ['warning_level=3'])

# Sanitizers
sanitizer = get_option('use_sanitizer')

c_args = []
link_args = []

if sanitizer == 'address'
  c_args += ['-fsanitize=address']
  link_args += ['-fsanitize=address']
endif

# Valgrind
use_valgrind = get_option('use_valgrind')

# Coverage - part 1
do_coverage = get_option('b_coverage')
if do_coverage
  c_args += ['-fprofile-arcs', '-ftest-coverage']
  link_args += ['-fprofile-arcs']
endif

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
#glib_dep = dependency('glib-2.0', version : '>= 2.40', required : true)
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
  c_args : c_args, link_args : link_args,
  dependencies : [png_dep])


# Tests
test_files = files('tests/test_graphics.c')
test_executable = executable(
  'test_executable', test_files,
  include_directories : inc_dirs,
  link_with: ymir,
  c_args : c_args, link_args : link_args,
  dependencies : [check_dep])


# Coverage
if do_coverage
  gcovr = find_program('gcovr', required : false)
  basic_args = ['--root', meson.current_source_dir(),
              meson.current_build_dir(),
              '--exclude',
              meson.current_source_dir() / 'tests/*',
              ]
  #test('coverage', gcovr, args: basic_args)
  test('coverage_xml', gcovr, args: basic_args + ['--xml-pretty', '--output', 'coverage.xml'])
endif

# Valgrind
if use_valgrind
    valgrind_cmd = find_program('valgrind')
    test_args = ['--leak-check=full', '--error-exitcode=1', test_executable]
    test('vg_test_graphics', valgrind_cmd, args: test_args)
else
    test('test_graphics', test_executable)
endif

# Installation
header_files = files('include/ymir/fs.h', 'include/ymir/graphics.h')
install_headers(header_files, subdir : 'ymir')
#install_man, install_data

# Configuration
#configure_file(output : 'config.h', configuration : conf)


ymir_dep = declare_dependency(
  include_directories : inc_dirs,
  link_with : ymir)
