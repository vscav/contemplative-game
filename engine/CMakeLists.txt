cmake_minimum_required(VERSION 3.10)

project(engine LANGUAGES C CXX)

# get source and header files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)

# engine documentation (Doxygen)
add_subdirectory(doc)

# include external libraries
include_directories(../lib/glm)
include_directories(../lib/glew/include)
include_directories(../lib/glfw/include)

# compile engine as library
add_library(engine ${SRC_FILES} ${HEADER_FILES} src/FilePath.cpp)

# set compilation flags
target_compile_features(engine PRIVATE cxx_std_17)
target_compile_options(engine PRIVATE -Wall -O2)

# engine include directory
target_include_directories(engine PRIVATE "include")

