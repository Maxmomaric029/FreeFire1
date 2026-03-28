#pragma once
#include "imgui.h"

namespace Theme {
    inline void SetupStyle() {
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

        colors[ImGuiCol_Text]                   = ImVec4(0.92f, 0.92f, 0.92f, 1.00f); // #EAEAEA
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.27f, 0.27f, 0.27f, 1.00f); // #444444
        
        // Fondos Delete Hex (#1A1A1A / #0D0D0D)
        colors[ImGuiCol_WindowBg]               = ImVec4(0.10f, 0.10f, 0.10f, 0.97f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.05f, 0.05f, 0.05f, 0.94f);
        
        // Marcos y Bordes
        colors[ImGuiCol_Border]                 = ImVec4(0.18f, 0.20f, 0.25f, 0.00f); // Escondidos (Glow usa bordes propios)
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        
        // Frames (Fondo de Controles)
        colors[ImGuiCol_FrameBg]                = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

        // Acentos (Azul Electrónico)
        ImVec4 accent                           = ImVec4(0.00f, 0.53f, 0.80f, 1.00f); // #0088CC
        ImVec4 accent_hover                     = ImVec4(0.00f, 0.67f, 1.00f, 1.00f); // #00AAFF
        ImVec4 accent_active                    = ImVec4(0.00f, 0.45f, 0.68f, 1.00f);

        colors[ImGuiCol_TitleBg]                = colors[ImGuiCol_WindowBg];
        colors[ImGuiCol_TitleBgActive]          = colors[ImGuiCol_WindowBg];
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        
        // Botones Generales
        colors[ImGuiCol_Button]                 = colors[ImGuiCol_FrameBg];
        colors[ImGuiCol_ButtonHovered]          = accent_hover;
        colors[ImGuiCol_ButtonActive]           = accent_active;
        
        // Headers y Tabs (Resalta Sidebar activo)
        colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.53f, 0.80f, 0.40f); 
        colors[ImGuiCol_HeaderHovered]          = accent_hover;
        colors[ImGuiCol_HeaderActive]           = accent;
        colors[ImGuiCol_Tab]                    = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_TabHovered]             = accent_hover;
        colors[ImGuiCol_TabActive]              = accent;
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        
        // Sliders y Checkmarks
        colors[ImGuiCol_CheckMark]              = accent;
        colors[ImGuiCol_SliderGrab]             = accent;
        colors[ImGuiCol_SliderGrabActive]       = accent_active;

        // Scrollbar y Separadores (Sugerencias Añadidas)
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.03f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.00f, 0.53f, 0.80f, 0.40f); 
        colors[ImGuiCol_ScrollbarGrabHovered]   = accent_hover;
        colors[ImGuiCol_ScrollbarGrabActive]    = accent;
        colors[ImGuiCol_SeparatorHovered]       = accent_hover;
        colors[ImGuiCol_SeparatorActive]        = accent;
    }
}
