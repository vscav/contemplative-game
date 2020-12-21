add_definitions(-std=c++17)

# get all application files
file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SRC_FILES *.cpp)
file(GLOB_RECURSE VERT_SHADER_FILES *.vert)
file(GLOB_RECURSE FRAG_SHADER_FILES *.frag)
file(GLOB_RECURSE GEOM_SHADER_FILES *.geom)

# include external libraries
include_directories(../lib/glm)
include_directories(../lib/glew/include)
include_directories(../lib/glfw/include)

# include engine
include_directories(../engine/include)

# executable filename
set(OUTPUT app)

# define executable
add_executable(${OUTPUT} ${SRC_FILES} ${HEADER_FILES} ${VERT_SHADER_FILES} ${FRAG_SHADER_FILES} ${GEOM_SHADER_FILES})

# link libraries to the executable
target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})

# copy shaders to the bin directory
file(COPY res/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
# copy texture images to the build directory
file(COPY res/textures/skybox/space DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/textures/skybox)
# copy gltf file and its texture images to the build directory
file(COPY res/models DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)