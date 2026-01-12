cmake_minimum_required(VERSION 3.22.1)
project(anticheat-injector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Agregar el archivo fuente principal
add_library(anticheat-injector SHARED
    native-lib.cpp
    memory-hook.cpp
    imgui-overlay.cpp
)

# Incluir directorios
target_include_directories(anticheat-injector PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

# Enlazar librerías del sistema
target_link_libraries(anticheat-injector
    log
    android
)
