cmake_minimum_required(VERSION 3.28)
project(YUME VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_subdirectory(glfw)
    add_subdirectory(glm)

elseif(UNIX AND NOT APPLE)
    # sudo apt-get install libglm-dev
    # sudo apt-get install libglfw3 libglfw3-dev

    cmake_policy(SET CMP0072 NEW)

    find_package(OpenGL REQUIRED)

    add_subdirectory(glm)
endif()

add_executable(${PROJECT_NAME}
    # dependencies
    src/deps/glad/glad.c
    src/deps/glad/glad.h
    src/deps/stb/stb.cpp
    src/deps/stb/stb_image.h

    #engine
    src/main.cpp

    src/engine/core/window.h
    src/engine/core/window.cpp

    src/engine/input/keycodes.h
    src/engine/input/input.h
    src/engine/input/input.cpp

    src/engine/config/config.h
    src/engine/config/essentials.h

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

    src/engine/core/assistant.h
    src/engine/core/assistant.cpp
)

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm OpenGL::GL)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src/deps)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/build/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/out/build/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/out/build/release"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/out/build/minsizerel"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/out/build/relwithdebinfo"
)

set(RES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RES_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "Kopiowanie folderu 'res' z zasobami do katalogu binarnych..."
)
