cmake_minimum_required(VERSION 3.20)
project(dggame)

set(CMAKE_CXX_STANDARD 20)

find_package(ZLIB REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(unofficial-skia CONFIG REQUIRED)

file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp")

add_executable(${PROJECT_NAME} ${SRC_DIR_LIST})

target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)

target_link_libraries(${PROJECT_NAME} glfw)

target_link_libraries(${PROJECT_NAME} unofficial::skia::skia)