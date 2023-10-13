cmake_minimum_required(VERSION 3.25)
project(test C)

set(CMAKE_C_STANDARD 23)

add_executable(buttons_test buttons/buttons.c)

target_include_directories(buttons_test PRIVATE ../include)
target_link_directories(buttons_test PRIVATE ${PROJECT_SOURCE_DIR}/../build/Release/)
target_link_libraries(buttons_test PRIVATE XSUIlib_static SDL2)

if (MINGW)
    add_custom_command(TARGET buttons_test POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:XSUIlib_shared>  # Location of the XSUIlib_shared shared library
            $<TARGET_FILE_DIR:buttons_test>)
endif()

add_custom_command(TARGET buttons_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:buttons_test>)

add_custom_command(TARGET buttons_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2_ttf>  # Location of the SDL2_ttf shared library
        $<TARGET_FILE_DIR:buttons_test>)

add_custom_command(TARGET buttons_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/assets"
        $<TARGET_FILE_DIR:buttons_test>/assets)


