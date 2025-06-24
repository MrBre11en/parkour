cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(Parkour)                      # Имя проекта

# Настройка стандарта C++ (GLM требует C++11 или новее)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление GLM (header-only)
find_package(glm REQUIRED)

# Создание исполняемого файла
add_executable(${PROJECT_NAME}
    parkour/main.cpp
)

# Связывание GLM с проектом
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)