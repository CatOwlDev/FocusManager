cmake_minimum_required(VERSION 3.20)
project(FocusManager CXX)

# Включаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# -----------------------------------------------------------------
# 1. ПОДКЛЮЧАЕМ NLOHMANN JSON (Прямое HTTP-скачивание без Git и кэша)
# -----------------------------------------------------------------
set(JSON_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/nlohmann")
file(MAKE_DIRECTORY "${JSON_DOWNLOAD_DIR}")

# Скачиваем один заголовочный файл напрямую с серверов GitHub
if(NOT EXISTS "${JSON_DOWNLOAD_DIR}/json.hpp")
    message(STATUS "Downloading nlohmann/json.hpp...")
    file(DOWNLOAD 
        "https://githubusercontent.com"
        "${JSON_DOWNLOAD_DIR}/json.hpp"
        SHOW_PROGRESS
        STATUS json_download_status
    )
endif()

# Создаем интерфейсную библиотеку для вашего проекта
add_library(nlohmann_json INTERFACE)
target_include_directories(nlohmann_json INTERFACE "${CMAKE_BINARY_DIR}")

# -----------------------------------------------------------------
# 2. ПОДКЛЮЧАЕМ FTXUI (Через FetchContent)
# -----------------------------------------------------------------
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com
    GIT_TAG        v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# -----------------------------------------------------------------
# 3. СБОРКА ВАШЕГО ПРОЕКТА
# -----------------------------------------------------------------
# ⚠️ ВНИМАНИЕ: Перечислите здесь ВСЕ ваши .cpp файлы через пробел!
# Например: main.cpp manager.cpp utils.cpp
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

# Связываем ваш проект с установленными библиотеками
target_link_libraries(FocusManager PRIVATE 
    nlohmann_json 
    ftxui::screen 
    ftxui::dom 
    ftxui::component
)
