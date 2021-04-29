cmake_minimum_required(VERSION 3.12)
project(ABY LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
    message(FATAL_ERROR "ABY requires at least g++-8")
endif()

option(ABY_BUILD_EXE "Build executables" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Set build type to `Release` if non was specified:
# (cf. https://gitlab.kitware.com/cmake/community/wikis/FAQ#how-can-i-change-the-default-build-mode-and-see-it-reflected-in-the-gui)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# Write built executables and libraries to bin/ and lib/, respectively.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

find_package(ENCRYPTO_utils QUIET)
if(ENCRYPTO_utils_FOUND)
    message(STATUS "Found ENCRYPTO_utils")
elseif(NOT ENCRYPTO_utils_FOUND AND NOT TARGET ENCRYPTO_utils::encrypto_utils)
    message("ENCRYPTO_utils was not found: add ENCRYPTO_utils subdirectory")
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/ENCRYPTO_utils/CMakeLists.txt")
        find_package(Git REQUIRED)
        message("initialize Git submodule: extern/ENCRYPTO_utils")
        execute_process(COMMAND git submodule update --init extern/ENCRYPTO_utils
                        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
    endif()
    add_subdirectory(extern/ENCRYPTO_utils)
endif()

find_package(OTExtension QUIET)
if(OTExtension_FOUND)
    message(STATUS "Found OTExtension")
elseif (NOT OTExtension_FOUND AND NOT TARGET OTExtension::otextension)
    message("OTExtension was not found: add OTExtension subdirectory")
    if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/OTExtension/CMakeLists.txt")
        find_package(Git REQUIRED)
        message("initialize Git submodule: extern/OTExtension")
        execute_process(COMMAND git submodule update --init extern/OTExtension
                        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
    endif()
    add_subdirectory(extern/OTExtension)
endif()

find_package(GMP REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost 1.66.0 REQUIRED COMPONENTS thread system)
#find_package(RELIC REQUIRED)

set(ecclvl 251) #set this for the ecc security level

#relic library configuration
set(DEBUG off CACHE BOOL "Build relic with debugging support")
set(PROFL off CACHE BOOL "Build relic with profiling support")
set(CHECK off CACHE BOOL "Build relic with error-checking support")
set(ALIGN "16" CACHE STRING "Relic align")
set(ARCH "X64" CACHE STRING "Architecture to be used in relic")
set(ARITH "curve2251-sse" CACHE STRING "arithmetic utils used in relic")
set(FB_POLYN ${ecclvl} CACHE INTEGER "security level of the ecc binary curve in relic")
set(FB_METHD "INTEG;INTEG;QUICK;QUICK;QUICK;QUICK;LOWER;SLIDE;QUICK" CACHE STRING "Methods for fb in relic")
set(FB_PRECO on CACHE BOOl "fb preco for relic")
set(FB_SQRTF off CACHE BOOL "sqrtf for relic")
set(EB_METHD "PROJC;LODAH;COMBS;INTER" CACHE STRING "Methods for eb in relic")
set(EC_METHD "CHAR2" CACHE STRING "Methods for ec in relic")
set(COMP "-O3 -funroll-loops -fomit-frame-pointer -march=core2 -msse4.2 -mpclmul" CACHE STRING "Relic compiler options")
set(TIMER "CYCLE" CACHE STRING "Relic timer")
set(WITH "MD;DV;BN;FB;EB;EC" CACHE STRING "Relic algorithms")
set(WSIZE "64" CACHE STRING "Relic word size in bits")
set(TESTS "0" CACHE STRING "Relic amount of random tests, 0 for disable")
set(BENCH "0" CACHE STRING "Relic amount of benchmarks on random values, 0 for disable")
set(SHLIB off CACHE BOOL "Relic shared library")
set(STLIB on CACHE BOOL "Relic static library")
add_subdirectory(extern/ENCRYPTO_utils/extern/relic)

#looks dirty, but since the relic library is poorly exported let's treat it as an external library
if(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(RELIC_LIB_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/librelic_s.a")
else()
	set(RELIC_LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/extern/ENCRYPTO_utils/extern/relic/lib/librelic_s.a")
endif()

add_library(RELIC::relic STATIC IMPORTED)

set(RELIC_LIB_DIR "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/librelic_s.a")

add_subdirectory(src/abycore)


if(ABY_BUILD_EXE)
    add_subdirectory(src/test)
    add_subdirectory(src/examples)
endif(ABY_BUILD_EXE)
