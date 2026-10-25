cmake_minimum_required(VERSION 3.20)
project(ColorPalettes LANGUAGES CXX)

add_executable(ColorPalettes
    ColorPalettes/Application.cpp
    ColorPalettes/CMY.cpp
    ColorPalettes/ColorPaletteManager.cpp
    ColorPalettes/HSL.cpp
    ColorPalettes/HSV.cpp
    ColorPalettes/RGB.cpp
    ColorPalettes/Slider.cpp

    ColorPalettes/CMY.h
    ColorPalettes/ColorPaletteManager.h
    ColorPalettes/HSL.h
    ColorPalettes/HSV.h
    ColorPalettes/RGB.h
    ColorPalettes/Slider.h
)

target_compile_features(ColorPalettes PRIVATE cxx_std_20)
set_target_properties(ColorPalettes PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(ColorPalettes PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include
)
target_link_directories(ColorPalettes PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib
)

target_compile_definitions(ColorPalettes PRIVATE
    SFML_STATIC
    _CONSOLE
    UNICODE
    _UNICODE
)

target_link_libraries(ColorPalettes PRIVATE
    $<$<CONFIG:Debug>:sfml-graphics-s-d.lib>
    $<$<CONFIG:Debug>:sfml-window-s-d.lib>
    $<$<CONFIG:Debug>:sfml-system-s-d.lib>
    $<$<NOT:$<CONFIG:Debug>>:sfml-graphics-s.lib>
    $<$<NOT:$<CONFIG:Debug>>:sfml-window-s.lib>
    $<$<NOT:$<CONFIG:Debug>>:sfml-system-s.lib>
    opengl32.lib
    winmm.lib
    gdi32.lib
    $<$<CONFIG:Debug>:freetyped.lib>
    $<$<CONFIG:Debug>:harfbuzzd.lib>
    $<$<NOT:$<CONFIG:Debug>>:freetype.lib>
    $<$<NOT:$<CONFIG:Debug>>:harfbuzz.lib>
)

if(MSVC)
    target_compile_options(ColorPalettes PRIVATE /permissive- /sdl /W3)
    set_property(TARGET ColorPalettes PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endif()

add_custom_command(TARGET ColorPalettes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/ColorPalettes/fonts
        $<TARGET_FILE_DIR:ColorPalettes>/fonts
)

set_target_properties(ColorPalettes PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:ColorPalettes>"
)
