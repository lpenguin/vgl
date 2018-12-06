cmake_minimum_required(VERSION 3.12)
project(uploadbench)

set(CMAKE_CXX_STANDARD 17)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLU REQUIRED)
find_package(GLFW REQUIRED)

add_executable(uploadbench main.cpp gl/util.cpp gl/shader.cpp gl/texture.h gl/base.cpp gl/base.h gl/util.h gl/buffer.h gl/vertex_array.cpp gl/buffer.cpp gl/vec.h gl/itexture.h)

target_link_libraries(
        uploadbench
        ${OpenGL_LIBRARY}
        ${GLFW_LIBRARY}
        ${GLEW_LIBRARY}
        ${GLM_LIBRARY}
        ${GLU_LIBRARY}

)