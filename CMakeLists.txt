cmake_minimum_required(VERSION 3.10)
project(FreeFirePanel VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorios de inclusión
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Aseguramos que se busque glfw y opengl si es necesario (asumiendo que los provee el sistema o MSYS2/vcpkg)
find_package(OpenGL REQUIRED)

# Archivos fuente
set(SOURCES
    src/main.cpp
    # Agrega aquí implementaciones si separas los .h a .cpp (por simplicidad, usaremos header-only para la lógica pequeña)
)

# ImGui fuentes
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${IMGUI_SOURCES})

# Librerías
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32 glfw3)
