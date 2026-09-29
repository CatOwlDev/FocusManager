cmake_minimum_required(VERSION 3.20)
project(FocusManager CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Создаем единую папку для внешних зависимостей
set(DEPS_DIR "${CMAKE_BINARY_DIR}/external")
file(MAKE_DIRECTORY "${DEPS_DIR}")

# -----------------------------------------------------------------
# 1. ПОДКЛЮЧАЕМ NLOHMANN JSON
# -----------------------------------------------------------------
if(NOT EXISTS "${DEPS_DIR}/nlohmann/json.hpp")
    message(STATUS "Downloading nlohmann/json.hpp...")
    file(DOWNLOAD 
        "https://githubusercontent.com"
        "${DEPS_DIR}/nlohmann/json.hpp"
    )
endif()

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE "${DEPS_DIR}")

# -----------------------------------------------------------------
# 2. ПОДКЛЮЧАЕМ FTXUI (Исправленное скачивание с редиректами)
# -----------------------------------------------------------------
if(NOT EXISTS "${DEPS_DIR}/ftxui-5.0.0.zip")
    message(STATUS "Downloading FTXUI source archive...")
    file(DOWNLOAD 
        "https://github.com"
        "${DEPS_DIR}/ftxui-5.0.0.zip"
        STATUS download_status
        LOG download_log
        FOLLOW_REDIRECTS # <--- ТОТ САМЫЙ ФЛАГ, КОТОРЫЙ ВСЁ ИСПРАВИТ
    )
    
    message(STATUS "Extracting FTXUI...")
    file(ARCHIVE_EXTRACT 
        INPUT "${DEPS_DIR}/ftxui-5.0.0.zip"
        DESTINATION "${DEPS_DIR}"
    )
endif()

# Регистрируем распакованную библиотеку внутри проекта
add_subdirectory("${DEPS_DIR}/FTXUI-5.0.0")


# -----------------------------------------------------------------
# 3. СБОРКА ВАШЕГО ПРОЕКТА
# -----------------------------------------------------------------
add_executable(FocusManager 
    main.cpp
    Blocker.cpp
    Error.cpp
    FocusManager.cpp
    JsonSerializer.cpp
    MyTransformers.cpp
    Paths.cpp
    Task.cpp
    Timer.cpp
    ToDoList.cpp
    UI.cpp
)

target_link_libraries(FocusManager PRIVATE 
    nlohmann_json 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)
