cmake_minimum_required(VERSION 3.20)

project(FocusManager
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---------------------------------------------------------
# C++ settings
# ---------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Statically link the MSVC runtime (/MT).
# This means the user normally won't need to install
# Microsoft Visual C++ Redistributable separately.
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

# ---------------------------------------------------------
# Dependencies
# ---------------------------------------------------------

include(FetchContent)

# FTXUI
set(FTXUI_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(FTXUI_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(FTXUI_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v5.0.0
)

FetchContent_MakeAvailable(ftxui)

# nlohmann/json
set(JSON_BuildTests OFF CACHE BOOL "" FORCE)
set(JSON_Install OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

# ---------------------------------------------------------
# FocusManager sources
# ---------------------------------------------------------

set(FOCUS_MANAGER_SOURCES
    src/main.cpp
    src/Blocker.cpp
    src/Error.cpp
    src/FocusManager.cpp
    src/JsonSerializer.cpp
    src/MyTransformers.cpp
    src/Paths.cpp
    src/Task.cpp
    src/Timer.cpp
    src/ToDoList.cpp
    src/UI.cpp
)

add_executable(FocusManager
    ${FOCUS_MANAGER_SOURCES}
)

# ---------------------------------------------------------
# Include directories
# ---------------------------------------------------------

target_include_directories(FocusManager
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# ---------------------------------------------------------
# Libraries
# ---------------------------------------------------------

target_link_libraries(FocusManager
    PRIVATE
        ftxui::component
        ftxui::dom
        ftxui::screen
        nlohmann_json::nlohmann_json

        # Windows APIs used by Paths.cpp / Blocker.cpp
        shell32
        ole32
        user32
)

# ---------------------------------------------------------
# Compiler options
# ---------------------------------------------------------

if(MSVC)
    target_compile_options(FocusManager
        PRIVATE
            /W4
            /utf-8
        )
endif()

# ---------------------------------------------------------
# Output
# ---------------------------------------------------------

set_target_properties(FocusManager PROPERTIES
    OUTPUT_NAME "FocusManager"
)
