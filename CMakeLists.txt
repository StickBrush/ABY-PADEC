cmake_minimum_required(VERSION 3.10)
project(ABY LANGUAGES CXX)

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
    find_package(Git REQUIRED)
    execute_process(COMMAND git submodule update --init extern/ENCRYPTO_utils
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_subdirectory(extern/ENCRYPTO_utils)
endif()

find_package(OTExtension QUIET)
if(OTExtension_FOUND)
    message(STATUS "Found OTExtension")
elseif (NOT OTExtension_FOUND AND NOT TARGET OTExtension::otextension)
    message("OTExtension was not found: add OTExtension subdirectory")
    find_package(Git REQUIRED)
    execute_process(COMMAND git submodule update --init extern/OTExtension
                    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_subdirectory(extern/OTExtension)
endif()

find_package(GMP REQUIRED)
find_package(Threads REQUIRED)

add_subdirectory(src/abycore)


if(ABY_BUILD_EXE)
    add_subdirectory(src/test)
    add_subdirectory(src/examples)
endif(ABY_BUILD_EXE)