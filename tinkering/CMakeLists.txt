cmake_minimum_required(VERSION 3.16)
project(TinkeringZone)

find_package(Threads REQUIRED)
find_package(Boost 1.66.0 REQUIRED COMPONENTS thread system)
find_package(RELIC)
find_package(ABY)

if (ABY_FOUND)
    message(STATUS "Found ABY")
elseif(NOT ABY_FOUND AND NOT TARGET ABY::aby)
    message("ABY was not found: add ABY subdirectory")
    add_subdirectory(extern/ABY)
endif()

#add_executable(tinkering_server tinkering_server.cpp)
#add_executable(tinkering_client tinkering_client.cpp)

add_library(psiclient STATIC circ_lib/circs_client.cpp)
add_library(psiserver STATIC circ_lib/circs_server.cpp)

target_link_libraries(psiclient ABY::aby ENCRYPTO_utils::encrypto_utils)
target_link_libraries(psiserver ABY::aby ENCRYPTO_utils::encrypto_utils)
#target_link_libraries(tinkering_server ABY::aby ENCRYPTO_utils::encrypto_utils)
#target_link_libraries(tinkering_client ABY::aby ENCRYPTO_utils::encrypto_utils)