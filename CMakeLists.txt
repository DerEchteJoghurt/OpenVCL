cmake_minimum_required(VERSION 3.2)
project(OpenVCLTest C CXX)

add_executable(
    ${PROJECT_NAME}

    main.cpp

    source/Application.cpp
    source/TButton.cpp
    source/TWindow.cpp
    source/SDL_FontCache.c
)

target_link_libraries(
    ${PROJECT_NAME}

    -lSDL2
    -lSDL2_ttf
    -lSDL2_gfx
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC

    include
)