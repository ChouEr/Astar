cmake_minimum_required(VERSION 2.6)

aux_source_directory(. DIR_LIB_SRCS)

add_library (pathFinder ${DIR_LIB_SRCS})
