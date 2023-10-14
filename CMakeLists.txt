cmake_minimum_required(VERSION 3.25)
project(XSUIlib C)

set(CMAKE_C_STANDARD 23)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)

add_subdirectory(external/SDL/SDL-SDL2)
add_subdirectory(test)
add_subdirectory(external/SDL/SDL_ttf-SDL2)
add_subdirectory(external/SDL/SDL_image-SDL2)
add_subdirectory(external/SDL/SDL_mixer-SDL2)

add_library(XSUIlib_static STATIC
        src/xsui.c include/xsui.h src/xsCore.c include/xsCore.h
        src/xsMath.c include/xsMath.h include/xsTypes.h
        include/UI_elements/xsButton.h src/UI_elements/xsButton.c
        src/xsUtils.c include/xsUtils.h include/xsConstants.h
        include/xsFont.h src/xsFont.c
)

# setting for the static library
target_include_directories(XSUIlib_static PUBLIC include)
target_link_directories(XSUIlib_static PUBLIC lib)

target_link_libraries(XSUIlib_static PRIVATE SDL2 SDL2main SDL2_ttf SDL2_image SDL2_mixer)

add_library(XSUIlib_shared SHARED
        src/xsui.c include/xsui.h src/xsCore.c include/xsCore.h
        src/xsMath.c include/xsMath.h include/xsTypes.h
        include/UI_elements/xsButton.h src/UI_elements/xsButton.c
        src/xsUtils.c include/xsUtils.h include/xsConstants.h
        include/xsFont.h src/xsFont.c
)

# setting for the shared library
target_include_directories(XSUIlib_shared PUBLIC include)
target_link_directories(XSUIlib_shared PUBLIC lib)

target_link_libraries(XSUIlib_shared PRIVATE SDL2 SDL2main SDL2_ttf SDL2_image SDL2_mixer)

add_custom_command(TARGET XSUIlib_static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:XSUIlib_static>
)

add_custom_command(TARGET XSUIlib_static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2_ttf>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:XSUIlib_static>
)

add_custom_command(TARGET XSUIlib_static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2_image>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:XSUIlib_static>
)

add_custom_command(TARGET XSUIlib_static POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:SDL2_mixer>  # Location of the SDL2 shared library
        $<TARGET_FILE_DIR:XSUIlib_static>
)

