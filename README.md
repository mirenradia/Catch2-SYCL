# doctest-SYCL

This branch replaces [Catch2](https://github.com/catchorg/Catch2) with 
[doctest](https://github.com/doctest/doctest) in order to see if it is affected
by the same problem.

## Prerequisites

You will need the following software available
* [Intel oneAPI
    DPC++](https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html)
    2023.1.0 or newer (tested with 2024.0.0)
* [CMake](https://cmake.org/) 3.20.5 or newer (tested with 3.27.9)

## Build instructions

0. First make sure you have set up your environment correctly with the
   prerequisites listed above available (e.g. modules loaded/`setvars.sh` script
   sourced).
1. Clone the repository:
   ```bash
   git clone https://github.com/mirenradia/Catch2-SYCL.git
   ```
2. Next create a build directory and change into it:
   ```bash
   mkdir Catch2-SYCL/build && cd Catch2-SYCL/build
   ```
4. Configure the build. For Intel DPC++, make sure you set `icpx` as the C++ 
   compiler:
   ```bash
   cmake -DCMAKE_CXX_COMPILER=icpx ..
   ```
5. Finally, build the application using `make`:
   ```bash
   make -j `nproc`
   ```

## Running

This is a [doctest](https://github.com/doctest/doctest) application with two test
cases (imaginatively named "Test1" and "Test2"). doctest provides the `main()`
function and also allows the user to pass a plethora of flags on the
command-line. For more information, do
```bash
./catch2sycl --help
```
By default, if no flags are passed, both test cases are run:
```bash
./catch2sycl
```