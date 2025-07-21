cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_CXX_STANDARD 23)


project(Sandbox VERSION 1.0.0)

find_package(SDL2 CONFIG REQUIRED)

find_package(SDL2_image CONFIG REQUIRED)

find_package(SDL2_ttf CONFIG REQUIRED)

find_package(SDL2_mixer CONFIG REQUIRED)

add_executable(Sandbox main.c)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} SDL2_mixer::SDL2_mixer)