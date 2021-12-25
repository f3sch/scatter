# PAD -- final project group 3 -- scatter

## Setup

```bash
$ git submodule init
$ git submodule update --recursive
$ ./vcpkg/bootstrap-vcpkg.sh
# In-source building is currently forbidden
$ mkdir build && cd build
$ cmake -DUSE_VCPKG=On -DLOCAL=On -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
$ cmake --build .
```

## Compilation not using vcpkg

This describes the installation process using cmake. As pre-requisites, you'll
need git and cmake installed.

For TBB: https://github.com/oneapi-src/oneTBB/blob/master/INSTALL.md

For DPL: https://github.com/oneapi-src/oneDPL

Example:
```bash
# Go to /tmp dir
$ cd /tmp
# Check out the library.
$ git clone https://mp-force.ziti.uni-heidelberg.de/asc/projects/lectures/parallel-algorithm-design/ws21/scatter.git
# Make a build directory to place the build output.
$ mkdir build
$ cd build
# Generate build system files with cmake
$ cmake -DLOCAL=1 --config Release ../scatter/
# Build the library.
$ cmake --build .
```
