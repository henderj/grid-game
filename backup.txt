cmake_minimum_required(VERSION 3.16)
project(grid_game)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.h"
        )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)

add_executable(grid_game main.cpp ${all_SRCS})
target_link_libraries(grid_game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})