cmake_minimum_required(VERSION 3.30)
project(imagin3D)

set(CMAKE_CXX_STANDARD 20)

# GLFW
add_subdirectory(libs/glfw)
include_directories(libs/glfw/include)

# GLAD
include_directories(libs/glad/include)
set(GLAD_SRC libs/glad/src/glad.c)

# Project Files
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
add_executable(imagin3D ${PROJECT_SOURCES} ${GLAD_SRC})


# Link Libraries
target_link_libraries(imagin3D glfw)
if (APPLE)
    target_link_libraries(imagin3D "-framework OpenGL")
elseif (WIN32)
    target_link_libraries(imagin3D opengl32)
else()
    target_link_libraries(imagin3D GL)
endif()
