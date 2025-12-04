cmake_minimum_required(VERSION 3.22)
project(MyGame)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(YUME yume_build)

add_executable(MyGame main.cpp)

target_link_libraries(MyGame PRIVATE YUME_LIB)

set(RES_SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")

add_custom_command(
    TARGET MyGame
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RES_SOURCE_DIR}"
        "$<TARGET_FILE_DIR:MyGame>/res"
    COMMENT "[!] 'res' directory copied to output directory."
)

# cmake -B build
# cmake --build build
# ./build/MyGame