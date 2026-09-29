cmake_minimum_required(VERSION 3.20)
project(FocusManager CXX)

# Включаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -----------------------------------------------------------------
# 1. ПОДКЛЮЧАЕМ NLOHMANN JSON (Прямое HTTP-скачивание файла)
# -----------------------------------------------------------------
set(JSON_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/nlohmann")
file(MAKE_DIRECTORY "${JSON_DOWNLOAD_DIR}")

if(NOT EXISTS "${JSON_DOWNLOAD_DIR}/json.hpp")
    message(STATUS "Downloading nlohmann/json.hpp...")
    file(DOWNLOAD 
        "https://githubusercontent.com"
        "${JSON_DOWNLOAD_DIR}/json.hpp"
        SHOW_PROGRESS
    )
endif()

add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE "${CMAKE_BINARY_DIR}")

# -----------------------------------------------------------------
# 2. ПОДКЛЮЧАЕМ FTXUI (HTTP-скачивание ZIP-архива вместо Git Clone)
# -----------------------------------------------------------------
FetchContent_Declare(
    ftxui
    URL      https://github.com
)
FetchContent_MakeAvailable(ftxui)

# -----------------------------------------------------------------
# 3. СБОРКА ВАШЕГО ПРОЕКТА
# -----------------------------------------------------------------
# Все ваши исходные .cpp файлы собраны столбиком
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

# Связываем проект с установленными библиотеками
target_link_libraries(FocusManager PRIVATE 
    nlohmann_json 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)
