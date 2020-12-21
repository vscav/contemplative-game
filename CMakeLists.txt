cmake_minimum_required(VERSION 3.1)

project(gl-app-template)

# use GLVND libraries
set(OpenGL_GL_PREFERENCE GLVND)

set(CXXFLAGS ${CXXFLAGS} std=c++17)
set(LIBRARIES ${LIBRARIES} stdc++fs)

# glfw library subdirectory
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)

# glew library subdirectory
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)

# glm library subdirectory
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

# engine library subdirectory
add_subdirectory(engine)

# set all libraries
set(ALL_LIBRARIES engine libglew_static glfw)

# change executable files directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# global compilation
file(GLOB APPLICATION "application")
add_subdirectory(${APPLICATION})
















# # Projects Settings
# cmake_minimum_required (VERSION 3.1)
# project (opengl-app-template)

# # Get application files
# get_filename_component(FILE app.cpp NAME_WE)
# file(GLOB_RECURSE HEADER_FILES header/*.hpp)
# file(GLOB_RECURSE SRC_FILES src/*.cpp)

# # App executable
# add_executable(${FILE} ${SRC_FILES} ${HEADER_FILES})
# set_property(TARGET ${FILE} PROPERTY CXX_STANDARD 11)
# target_compile_options(${FILE} PRIVATE -Wall)

# # glfw library
# add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
# target_link_libraries(${FILE} PRIVATE glfw)

# # glew library
# add_definitions(-DGLEW_STATIC)
# add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
# target_link_libraries(${FILE} PRIVATE libglew_static)

# # glm library
# add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
# target_link_libraries(${FILE} PRIVATE glm)

# # doxygen (documentation)
# add_subdirectory(doc)
