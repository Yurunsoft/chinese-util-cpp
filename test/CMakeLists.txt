cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(ChineseUtilTests
  LANGUAGES CXX
)

set(VENDOR_DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/_deps)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  GIT_TAG 2.4.0
)

if (TEST_INSTALLED_VERSION)
  find_package(ChineseUtil REQUIRED)
else()
  CPMAddPackage(
    NAME ChineseUtil
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.3
)

find_package(nlohmann_json QUIET)

include_directories(
  ${VENDOR_DEPENDENCIES_DIR}/nlohmann_json-src/include
)

# ---- Create binary ----

file(GLOB headers CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(ChineseUtilTests ${headers} ${sources})
target_link_libraries(ChineseUtilTests doctest ChineseUtil)

target_include_directories(ChineseUtilTests
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

set_target_properties(ChineseUtilTests PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if (NOT TEST_INSTALLED_VERSION)
  if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(ChineseUtil PUBLIC -Wall -pedantic -Wextra)
  elseif(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_HAS_STD_BYTE=0)
    target_compile_options(ChineseUtil PUBLIC /W4 /wd4505 /wd4018 /utf-8)
    target_compile_definitions(ChineseUtilTests PUBLIC DOCTEST_CONFIG_USE_STD_HEADERS)
  endif()
endif()

# ---- Add ChineseUtilTests ----

ENABLE_TESTING() 

# Note: doctest and similar testing frameworks can automatically configure CMake tests
# For other testing frameworks add the tests target instead:
# ADD_TEST(ChineseUtilTests ChineseUtilTests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(ChineseUtilTests)

# ---- code coverage ----

if (ENABLE_TEST_COVERAGE)
  target_compile_options(ChineseUtil PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(ChineseUtil PUBLIC -fprofile-arcs -ftest-coverage)
endif()
