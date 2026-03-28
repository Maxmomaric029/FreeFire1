#pragma once
#include "imgui.h"

namespace Theme {
    inline void ApplyModernDarkTheme() {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // Bordes redondeados y dimensiones
        style.WindowRounding    = 8.0f;
        style.FrameRounding     = 6.0f;
        style.PopupRounding     = 6.0f;
        style.ScrollbarRounding = 6.0f;
        style.GrabRounding      = 6.0f;
        style.TabRounding       = 4.0f;

        style.WindowPadding     = ImVec2(15, 15);
        style.FramePadding      = ImVec2(10, 5);
        style.ItemSpacing       = ImVec2(10, 10);
        style.ItemInnerSpacing  = ImVec2(8, 6);

        // Colores base Oscuros con Acentos Neón
        ImVec4* colors = style.Colors;

        colors[ImGuiCol_Text]                   = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
        
        // Fondo Principal
        colors[ImGuiCol_WindowBg]               = ImVec4(0.09f, 0.10f, 0.13f, 0.98f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.12f, 0.13f, 0.16f, 1.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        
        // Marcos y Bordes
        colors[ImGuiCol_Border]                 = ImVec4(0.18f, 0.20f, 0.25f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        
        // Frames (Fondo de Controles)
        colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.25f, 0.28f, 0.35f, 1.00f);

        // Acentos: Verde Neón a solicitud de moderno
        ImVec4 accent                           = ImVec4(0.20f, 0.85f, 0.42f, 1.00f);
        ImVec4 accent_hover                     = ImVec4(0.28f, 0.95f, 0.52f, 1.00f);
        ImVec4 accent_active                    = ImVec4(0.15f, 0.70f, 0.35f, 1.00f);

        colors[ImGuiCol_TitleBg]                = colors[ImGuiCol_WindowBg];
        colors[ImGuiCol_TitleBgActive]          = colors[ImGuiCol_WindowBg];
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        
        // Botones Generales
        colors[ImGuiCol_Button]                 = colors[ImGuiCol_FrameBg];
        colors[ImGuiCol_ButtonHovered]          = accent_hover;
        colors[ImGuiCol_ButtonActive]           = accent_active;
        
        // Headers y Tabs
        colors[ImGuiCol_Header]                 = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
        colors[ImGuiCol_HeaderHovered]          = accent_hover;
        colors[ImGuiCol_HeaderActive]           = accent;
        colors[ImGuiCol_Tab]                    = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
        colors[ImGuiCol_TabHovered]             = accent_hover;
        colors[ImGuiCol_TabActive]              = accent;
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.17f, 0.20f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.20f, 0.22f, 0.25f, 1.00f);
        
        // Sliders y Checkmarks
        colors[ImGuiCol_CheckMark]              = accent;
        colors[ImGuiCol_SliderGrab]             = accent;
        colors[ImGuiCol_SliderGrabActive]       = accent_active;
    }
}
