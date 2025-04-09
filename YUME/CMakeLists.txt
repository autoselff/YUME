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
    src/deps/stb/stb.cpp

    # engine
    src/main.cpp

    src/engine/core/window.h
    src/engine/core/window.cpp

    src/engine/input/keycodes.h
    src/engine/input/input.h
    src/engine/input/input.cpp

    src/engine/config/config.h
)

# Link OpenGL on UNIX
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm OpenGL::GL)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src/deps)
