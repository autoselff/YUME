cmake_minimum_required(VERSION 3.8)
project(YUME)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_subdirectory(glfw)
    add_subdirectory(glm)

elseif(UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)

    find_package(OpenGL REQUIRED)

    add_subdirectory(glm)
endif()

# Ling source and header files
add_executable(${PROJECT_NAME}
    # dependencies
    src/deps/glad/glad.c
    src/deps/glad/glad.h
    src/deps/stb/stb.cpp
    src/deps/stb/stb_image.h

    # engine
    src/main.cpp

    src/engine/core/window.h
    src/engine/core/window.cpp

    src/engine/input/keycodes.h
    src/engine/input/input.h
    src/engine/input/input.cpp

    src/engine/config/config.h
    src/engine/config/essentials.h
    src/engine/config/data.h

    src/engine/gl_program/shader.h
    src/engine/gl_program/shader.cpp

    src/engine/gl_program/gl_program.h
    src/engine/gl_program/gl_program.cpp

    src/engine/renderer/square.h
    src/engine/renderer/square.cpp

    src/engine/renderer/triangle.h
    src/engine/renderer/triangle.cpp

    src/engine/renderer/texsquare.h
    src/engine/renderer/texsquare.cpp
)

# Link OpenGL on UNIX
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm OpenGL::GL)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src/deps)
