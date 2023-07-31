# Catch2-SYCL

A simple repository to demonstrate an issue I have found with unnamed SYCL
kernels in [Catch2](https://github.com/catchorg/Catch2) test cases.

## Prerequisites

You will need the following software available
* Intel oneAPI DPC++ compiler (and runtime) 2023.1.0 or newer (tested with
  2023.2.0)
* CMake 3.20.5 or newer (tested with 3.27.1)

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
3. Configure the build making sure to use `icpx` as the C++ compiler:
   ```bash
   cmake -DCMAKE_CXX_COMPILER=icpx ..
   ```
4. Finally, build the application using `make`:
   ```bash
   make -j `nproc`
   ```

## Running

This is a [Catch2](https://github.com/catchorg/Catch2) application with two test
cases (imaginatively named "Test1" and "Test2"). Catch2 provides the `main()`
function and also allows the user to pass a plethora of flags on the
command-line. For more information, do
```bash
./catch2sycl --help
```
By default, if no flags are passed, both test cases are run:
```bash
./catch2sycl
```
You should find one of the test cases fails and observe output something like:
```
Randomness seeded to: xxxxxxx

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
catch2sycl is a Catch2 v3.4.0 host application.
Run with -? for options

-------------------------------------------------------------------------------
Test2
-------------------------------------------------------------------------------
/home/miren/RSE/Catch2-SYCL/TestCase2.cpp:7
...............................................................................

/home/miren/RSE/Catch2-SYCL/TestCase2.cpp:37: FAILED:
  REQUIRE( shared_ptr_c[i] == 3 * i )
with expansion:
  2 == 3

===============================================================================
test cases:    2 |    1 passed | 1 failed
assertions: 1026 | 1025 passed | 1 failed
```

## Problem
The problem seems to come from the mangled names the compiler generates for both
of the SYCL kernels being the same. In my case, this is something like
```
_ZTSZL22CATCH2_INTERNAL_TEST_0vEUlN4sycl3_V12idILi1EEEE_
```
Catch2's macros use the `__COUNTER__` predefined macro to generate a "unique"
name for the test case function by default (it can be configured to also use the
line number instead, but this would have the same problem). Unfortunately, this
counter seems to only increase within each separate invocation to the
preprocessor thus test cases defined in different source files (i.e.
non-headers) can have the same name.  This confuses the SYCL
compiler/linker/runtime which links the kernel invocation on the host to the
same device kernel code in both cases leading to test failure.