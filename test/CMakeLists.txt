cmake_minimum_required(VERSION 3.25)
project(test C)

set(CMAKE_C_STANDARD 23)

add_executable(buttons_test buttons/buttons.c)

target_include_directories(buttons_test PRIVATE ../include)
target_link_libraries(buttons_test "${PROJECT_SOURCE_DIR}/../build/Debug/libXSUIlib.a")