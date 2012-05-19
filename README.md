Libcondset is a library for the manipulation of Condition Sets, which are sets of predicates and data. The class also has a compact binary format, making this class best suited to sending conditions over the network or saving them in files.
It is a small library providing one C++ class. It can be used as a dynamic library, a static library, or just a header and an object file.
This library has been tested for the formats portability and has been tested on Ubuntu 11.04, Ubuntu 10.04, and Mac OSX 10.7. It should work on most, if not all UNIX/POSIX based operating systems that can run GCC.

Installation is simple. If you want to use it as a header and object file, issue this in the place where you unzipped or cloned it:

`$ make conditionset.o`

If you want it to be installed as a static library:

`$ make install_static INSTALL_PREFIX=/usr/local`

Note: `INSTALL_PREFIX` is any dir with a `lib/` and an `include/`. 
To install as a shared library, the same as above but as `install_shared`:

`$ make install_shared INSTALL_PREFIX=/usr/local`

The documentation is in the `libcondset-doc.x.x.x.tar.gz` archive in HTML form.
