## Project continuous here https://github.com/OpenCAEPlus/OpenCAEPoro
# OpenCAEPoro

[![Build and publish doc](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/doc.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/doc.yml)
[![Github pages](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/gh-page.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/gh-page.yml)

| Build | Test |
|:------|:-----|
|[![Linux GNU Build](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_gnu_build.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_gnu_build.yml)| [![Linux GNU Test](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_gnu_test.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_gnu_test.yml) |
|[![Linux Intel Build](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_intel_build.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_intel_build.yml)|[![Linux Intel Test](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_intel_test.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/linux_intel_test.yml)|
|[![Win64 Intel Build](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/windows_intel_build.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/windows_intel_build.yml)| [![Win64 Intel Test](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/windows_intel_test.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/windows_intel_test.yml) |
|[![Mac64 Intel Build](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/mac_x64_intel_build.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/mac_x64_intel_build.yml)| [![Mac64 Intel Test](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/mac_x64_intel_test.yml/badge.svg)](https://github.com/FaspDevTeam/OpenCAEPoro/actions/workflows/mac_x64_intel_test.yml) |


OpenCAEPoro or OCP is part of the [OpenCAEPlus](https://opencaeplus.org/) project. OCP, 
written in C++, focuses on simulating multicomponent multiphase flows in porous media. 
For more information, please refer to [OCP repository](https://faspdevteam.github.io/OpenCAEPoro/).

## Get Started

For user manual and API's (class references from Doxygen), see [website](https://porous.opencaeplus.org).

For full documentation generated by Doxygen, see [here](https://faspdevteam.github.io/OpenCAEPoro/).

## Install

There is a top level cmake configuration file to build the OpenCAEPoro lib 
and the associate test program suite. You can use a cmake-style approach to 
compile the package; see [the official webpage](https://cmake.org) on how to
use cmake for your own operating system and tool chain. 

Before building OpenCAEPoro, you need to make sure that BLAS, LAPACK, and FASP
are available. BLAS and LAPACK are ready on most systems. The FASP package (only 
the open-source part [faspsolver](https://github.com/FaspDevTeam/faspsolver) is 
required) can be downloaded from its GitHub repository. More solver options are
provided in [fasp4blkoil](https://github.com/FaspDevTeam/fasp4blkoil).

The typical command for compiling OpenCAEPoro is:

**Step 1.** Config the environment for building with cmake:
```bash
  >>> mkdir Build; cd Build; cmake ..
```

**Step 2a.** To build the library as well as examples without installing it, run:
```bash
  >>> make
```

**Step 2b.** To make the library and then install it, run:
```bash
  >>> make install
```

Standard `uninstall` and `clean` targets are also provided in the generated Makefile. You may safely remove the `Build` directory as well. 

Note: You can also use the provided scripts to build the whole project:
```bash
  >>> chmod 755 cli
  >>> ./cli build -c intel -t all -b Debug # Change the argument to Release for release build
```

## Structure

The directory structure of OpenCAEPoro is designed as follows:
  - data/: Output files for comparison purposes
  - doc/: Documentation website
  - examples/: Input files for test examples 
  - external/: external dependencies
  - include/: Header files
  - src/: Source files
  - stash/: Files that are no longer needed, keep for future references
  - main/: Main source code for executables 
  - CMakeLists.txt: Main cmake script
  - CMakePresets.json: Preset setting for cmake 
  - CONTRIBUTE.md: Guidance for open source contributors
  - LICENSE: License agreement
  - README.md: This document
  - .clang-format: For automatic source code formatting
  - cli, cli.bat: Command line interface for build, test, and doc

## Test

There are three levels of tests:
  - Unit test: for testing individual code components
  - Integrate test: for testing interfaces between components
  - System test: for testing and benchmark of the whole program  

Currently, only system tests are provided in the `examples/` folder.

## License
This software is free software distributed under the Lesser General Public
License or LGPL, version 3.0 or any later versions. This software distributed
in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OpenCAEPoro. If not, see <http://www.gnu.org/licenses/>.
