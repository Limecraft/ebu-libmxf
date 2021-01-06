# libMXF

libMXF is a low-level C library for reading and writing the
[SMPTE ST 377-1 MXF file format](https://ieeexplore.ieee.org/document/7292073).

libMXF and the associated libMXF++ C++ wrapper library are used in the bmx project.

libMXF was originally developed as part of the
[Ingex Project](http://ingex.sourceforge.net/) where it supported MXF transfer,
playback and storage applications. libMXF was also used in the
[BBC Archive Preservation
Project](https://www.bbc.co.uk/rd/publications/whitepaper275) to
migrate BBC archive content from video tapes to files.

The [MXFDump](./tools/MXFDump) MXF text dumper utility from the [AAF
SDK](https://sourceforge.net/projects/aaf/) is provided in this project for
convenience.


## Examples

A number of applications and library code can be found in the
[examples](./examples) directory. These are not part of the core library and
are not required to build libMXF++ or bmx.
* [archive](./examples/archive): library code and utilities used in the [BBC
Archive Preservation
Project](https://www.bbc.co.uk/rd/publications/whitepaper275).
* [avidmxfinfo](./examples/avidmxfinfo): library and utility for extracting
metadata about Avid MXF OP-Atom files. This utility has been superseded by
`mxf2raw` in the bmx project.
* [reader](./examples/reader): library code used by the [Ingex
Player](http://ingex.sourceforge.net/) for reading MXF files.
* [transfertop2](./examples/transfertop2): utilities used in the
[TransferToP2](http://ingex.sourceforge.net/TransferToP2.html) application to
allow edited sequences to be transferred from an editing system to a P2 card.
* [vlc](./examples/vlc): legacy code that was written to test how easy it would
be to support MXF in [VLC](https://www.videolan.org/vlc/).
* [writeaviddv50](./examples/writeaviddv50): example utility for writing DV 50
MBit/s video in Avid MXF OP-Atom files.
* [writeavidmxf](./examples/writeavidmxf): library code and utility for writing
Avid MXF OP-Atom files. This utility has been superseded by `raw2bmx` in the
bmx project.


## Build and Installation

libMXF is developed on Ubuntu Linux but is supported on other Unix-like systems
using the autotools build system. A set of Microsoft Visual C++ project files
are provided for Windows.


### Dependencies

The following libraries must be installed to build libMXF. The (Ubuntu) debian
package names and versions are shown in brackets.
* uuid, Unix-like systems only (uuid-dev)


### Unix-like Systems Build

Install the development versions of the dependency libraries. The libMXF library
and example applications can then be built from source using autotools as
follows,
```bash
./autogen.sh
./configure
make
```

Run
```bash
./configure -h
```
to see a list of build configuration options.

A number of `--disable-*` options are provided for disabling all examples
(`--disable-examples`) or specific ones (e.g.
`--disable-writeavidmxf`). The `--disable-examples` option can be combined with
`--enable-*` options to enable specific examples. The bmx project
does not require the examples and therefore libMXF can be configured using
`--disable-examples`.

There are a number of core library and example regression tests that can be run
using
```bash
make check
```

Finally, the core library and examples can be installed using
```bash
sudo make install
```

To avoid library link errors similar to "error while loading shared
libraries" when building libMXF++ or bmx run
```bash
sudo /sbin/ldconfig
```
to update the runtime linker cache after installation.


### Microsoft Visual Studio C++ Build

The Visual Studio 2010 build solution and project files can be found in the
[msvc_build/vs10](./msvc_build/vs10) directory. These files can be upgraded to
any more recent version when importing into the IDE.

The main build solution file is [libMXF-All.sln](./msvc_build/vs10/libMXF-All.sln).
It is used to build the library and example applications.

The build depends on the `mxf_scm_version.h` header file in the root directory
to provide the most recent git commit identifier. This file is generated
automatically using the [gen_scm_version.sh](./gen_scm_version.sh) script when
building using autotools and is included in the source distribution package.
You are likely missing this file if you are using the source code directly from
the git repository then and will need to create it manually.

The [MXFDump.sln](./msvc_build/vs10/MXFDump.sln) build solution file is used to
build the MXFDump text dumper tool.


## Source and Binary Distributions

Source distributions and Windows binaries are made [available on
SourceForge](https://sourceforge.net/projects/bmxlib/files/).


## License

The libMXF library is provided under the BSD 3-clause license. See the
[COPYING](./COPYING) file provided with this library for more details.
