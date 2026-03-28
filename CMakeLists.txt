cmake_minimum_required(VERSION 3.14)
project(FreeFirePanel VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directorios de inclusión locales
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Buscamos hilos
find_package(Threads REQUIRED)

# Usamos FetchContent para descargar ImGui (si no existe localmente) y compilarlo
include(FetchContent)

# Descargamos GLFW de forma estática para evitar problemas de DLLs sueltas si no existe
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
# Desactivamos construcción de docs y tests de GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Descargamos ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.90.4-docking
)
FetchContent_MakeAvailable(imgui)

# Enlace estático u obtención de OpenGL
find_package(OpenGL REQUIRED)

# Archivos fuente del Proyecto
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Configuramos sources de ImGui para compilar junto a nuestro EXE
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Definimos el ejecutable WIN32 (Si pasas WIN32 ocultará la ventana de la terminal, puedes quitarlo para debug)
add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${IMGUI_SOURCES})

# Incluimos los headers recien descargados por cloc/Fetch
target_include_directories(${PROJECT_NAME} PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Vincular liberías estáticas (GLFW local compilado) y opengl32 dinámico
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    Threads::Threads
)

# Propiedades estáticas para asegurar compatibilidad en Actions
if(MSVC)
    # Ligar estáticamente en Windows MSVC /MT
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
