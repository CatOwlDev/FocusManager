cmake_minimum_required(VERSION 3.20)
project(FocusManager CXX)

# Включаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем модуль для автоскачивания библиотек из GitHub
include(FetchContent)

# -----------------------------------------------------------------
# 1. ПОДКЛЮЧАЕМ NLOHMANN JSON
# -----------------------------------------------------------------
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com
    GIT_TAG        v3.11.3 # Стабильная версия
)
FetchContent_MakeAvailable(json)

# -----------------------------------------------------------------
# 2. ПОДКЛЮЧАЕМ FTXUI (Библиотека для консольного интерфейса)
# -----------------------------------------------------------------
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com
    GIT_TAG        v5.0.0 # Стабильная версия
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
