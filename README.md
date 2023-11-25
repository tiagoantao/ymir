# ymir

C codebase library.

This is a bunch of functions that I personally use a lot when coding in C.
You probably don't want to use it wholesale, but maybe take part of the code
yourself. If you use part of the code, please attribute it in whatever way
is more convenient.


Tested on Linux only.



```sh
rm -rf build
meson setup build -Db_coverage=true

meson compile -C build

meson test -C build
```

Coverage results are produced in `build/coverage.xml`


## Sanitizer and Valgrind use

Build with:

```sh
meson setup build -Db_sanitizer=address
```

or:

```sh
meson setup build -Duse_valgrind=true
```


# Requirements

Specified as Debian-based dependencies. Similar packages should exist
for other Linuxes (and *nix derivatives).

```sh
apt-get install meson ninja-build check doxygen gcovr

apt-get install libpng
```

# TODO

- test coverage
- add doxygen
