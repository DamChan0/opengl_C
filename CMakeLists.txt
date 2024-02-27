cmake_minimum_required(VERSION 3.0)
project(GLFW_Button_Example)

# Set OpenGL_GL_PREFERENCE to GLVND
set(OpenGL_GL_PREFERENCE "GLVND")

# Find the GLFW package
find_package(glfw3 REQUIRED)

# Add the executable
add_executable(main main.c)

# Link GLFW library
target_link_libraries(main glfw)

# Add OpenGL library
find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)
