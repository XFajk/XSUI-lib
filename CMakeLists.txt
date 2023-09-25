cmake_minimum_required(VERSION 3.25)
project(XSUIlib C)

set(CMAKE_C_STANDARD 23)

add_library(${PROJECT_NAME} src/xsui.c include/xsui.h src/xsCore.c include/xsCore.h src/xsMath.c include/xsMath.h)

add_subdirectory(external/SDL2)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PUBLIC lib)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)
