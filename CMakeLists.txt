cmake_minimum_required(VERSION 3.25)
project(XSUIlib C)

set(CMAKE_C_STANDARD 23)

add_library(${PROJECT_NAME} 
        src/xsui.c include/xsui.h src/xsCore.c include/xsCore.h
        src/xsMath.c include/xsMath.h include/xsTypes.h
        include/UI_elements/xsButton.h src/UI_elements/xsButton.c
        src/xsUtils.c include/xsUtils.h include/xsConstants.h
)

add_subdirectory(external/SDL2)
add_subdirectory(test)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_directories(${PROJECT_NAME} PUBLIC lib)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
