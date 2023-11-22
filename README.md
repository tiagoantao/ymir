# ymir

C codebase library.

This is a bunch of functions that I personally use a lot when coding in C.
You probably don't want to use it wholesale, but maybe take part of the code
yourself. If you use part of the code, please attribute it in whatever way
is more convenient.


Tested on Linux only.



```
meson setup build

cd build

meson compile

meson test
```

# Requirements

Specified as Debian-based dependencies. Similar packages should exist
for other Linuxes (and *nix derivatives).

```
apt-get install meson ninja-build check

apt-get install glib-2 libpng
```

# TODO

- test coverage
- memory checks on build (valgrind or something)
