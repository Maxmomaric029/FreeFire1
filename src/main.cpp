#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ui/Theme.h"
#include "ui/Menu.h"
#include "memory/Memory.h"
#include "utils/EmulatorDetector.h"
#include <string>

// FontAwesome identifiers (ejemplos para Iconos)
#define ICON_FA_HOME "\xef\x80\x95"
#define ICON_FA_COG "\xef\x80\x93"

// Global pointers o variables locales en un main real, aquí simple
Memory* memInstance = nullptr;

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    EmulatorDetector detector;
    std::string emuProcess = detector.DetectRunningEmulator();
    if (!emuProcess.empty()) {
        std::wstring widestr = std::wstring(emuProcess.begin(), emuProcess.end());
        memInstance = new Memory(widestr.c_str());
        printf("Conectado a emulador: %s\n", emuProcess.c_str());
    } else {
        printf("Esperando a que se abra un emulador válido...\n");
        memInstance = new Memory();
    }
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(800, 600, "FreeFire Panel - Modern External", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Load Fonts (Requiere las fuentes TrueType descargadas)
    // io.Fonts->AddFontFromFileTTF("resources/Roboto-Medium.ttf", 16.0f);
    // Para FontAwesome:
    // static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
    // ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    // io.Fonts->AddFontFromFileTTF("resources/fa-solid-900.ttf", 16.0f, &icons_config, icons_ranges);

    // Setup Dear ImGui style (Modern Theme)
    Theme::ApplyModernDarkTheme();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Bucle Principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Limpieza de Frame y nueva ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dibujar Menú con Pestañas
        Menu::DrawHUD();

        // Renderizado
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.08f, 0.08f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
