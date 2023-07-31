cmake_minimum_required(VERSION 3.20.5)

project(Catch2-SYCL)

# Use Intel DPC++ SYCL implementation by default
find_package(IntelSYCL REQUIRED)
# comment above line and uncomment below line to try Open SYCL/hipSYCL instead
#find_package(hipSYCL REQUIRED)

# Get Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(catch2sycl TestCase1.cpp TestCase2.cpp)

# Link with Catch2
target_link_libraries(catch2sycl PRIVATE Catch2::Catch2WithMain)

# Specify the SYCL sources
add_sycl_to_target(TARGET catch2sycl SOURCES TestCase1.cpp TestCase2.cpp)

target_include_directories(catch2sycl PRIVATE "${PROJECT_SOURCE_DIR}")