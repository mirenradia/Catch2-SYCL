cmake_minimum_required(VERSION 3.20.5)

project(doctest-SYCL)

# Use Intel DPC++ SYCL implementation by default
find_package(IntelSYCL REQUIRED)
# comment above line and uncomment below line to try Open SYCL/hipSYCL instead
#find_package(hipSYCL REQUIRED)

# Get doctest
Include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.11
)

FetchContent_MakeAvailable(doctest)

add_executable(doctestsycl TestCase1.cpp TestCase2.cpp)

# Link with doctest
target_link_libraries(doctestsycl PRIVATE doctest::doctest)

# Specify the SYCL sources
add_sycl_to_target(TARGET doctestsycl SOURCES TestCase1.cpp TestCase2.cpp)

target_include_directories(doctestsycl PRIVATE "${PROJECT_SOURCE_DIR}" doctest::doctest)