#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <windows.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "ui/Theme.h"
#include "ui/Menu.h"
#include "memory/Memory.h"
#include "utils/EmulatorDetector.h"
#include "ui/ImageLoader.h"
#include <string>

// Global pointers
Memory* memInstance = nullptr;
GLuint g_LogoTexture = 0;
int g_LogoWidth = 0;
int g_LogoHeight = 0;

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

    // Hints de Transparencia y decoraciones:
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // Mantener sobre todo

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(650, 480, "FreeFire Panel", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Load Fonts Híbrido
    ImFontConfig font_cfg;
    font_cfg.OversampleH = 2;
    font_cfg.OversampleV = 2;
    ImFont* mainFont = io.Fonts->AddFontFromFileTTF("resources/fonts/Exo2.ttf", 16.0f, &font_cfg);

    // Merge Icons FontAwesome 6 Solid
    static const ImWchar icons_ranges[] = { 0xe005, 0xf8ff, 0 }; 
    ImFontConfig icons_config;
    icons_config.MergeMode = true; 
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = 13.0f; 
    io.Fonts->AddFontFromFileTTF("resources/fonts/fa-solid-900.ttf", 16.0f, &icons_config, icons_ranges);

    // Setup Dear ImGui style (Modern Theme)
    Theme::SetupStyle(); // Adaptado al nuevo Theme transparente

    // Cargar imagen de Banner local
    ImageLoader::LoadTextureFromFile("LOGO.jpg", &g_LogoTexture, &g_LogoWidth, &g_LogoHeight);

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
        // Limpiar completamente el framebuffer con transparencia alfa 0
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
