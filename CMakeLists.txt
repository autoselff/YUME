cmake_minimum_required(VERSION 3.22)
project(YUME VERSION 0.0.3)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
    add_subdirectory(glfw)
    add_subdirectory(glm)

# ===========================================================================
#                             INSTALATION (LINUX)                         
#                      sudo apt-get install libglm-dev
#                  sudo apt-get install libglfw3 libglfw3-dev
# ===========================================================================
elseif(UNIX AND NOT APPLE)
    cmake_policy(SET CMP0072 NEW)
    find_package(OpenGL REQUIRED)
    add_subdirectory(glm)
endif()

# ===========================================================================
#                                   YUME                                    
# ===========================================================================
add_library(YUME_LIB STATIC
    # dependencies
    deps/glad/glad.c
    deps/glad/glad.h
    deps/stb/stb.cpp
    deps/stb/stb_image.h

    # YUME framework
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

    src/engine/renderer/colors.h
    
    src/engine/renderer/square.h
    src/engine/renderer/square.cpp

    src/engine/renderer/triangle.h
    src/engine/renderer/triangle.cpp

    src/engine/renderer/texsquare.h
    src/engine/renderer/texsquare.cpp

    src/engine/renderer/renderer.h
    src/engine/renderer/renderer.cpp

    src/engine/core/assistant.h
    src/engine/core/assistant.cpp

    src/engine/node/node.h
    src/engine/node/node.cpp
)

if(UNIX AND NOT APPLE)
    target_link_libraries(YUME_LIB PUBLIC glfw glm OpenGL::GL)
else()
    target_link_libraries(YUME_LIB PUBLIC glfw glm)
endif()

target_include_directories(YUME_LIB 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/deps>
    PRIVATE 
)

# ===========================================================================
#                              EXAMPLE PROGRAM                                    
# ===========================================================================
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE YUME_LIB)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/out/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/out/release"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/out/minsizerel"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/out/relwithdebinfo"
)

set(RES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RES_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
    COMMENT "[!] 'res' directory copied to output directory."
)
