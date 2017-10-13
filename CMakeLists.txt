cmake_minimum_required(VERSION 2.6)

project (callAstar)

aux_source_directory ( . DIR_SRCS )

add_subdirectory(pathFinder)

add_executable(demo main.cpp)

target_link_libraries(demo pathFinder)


