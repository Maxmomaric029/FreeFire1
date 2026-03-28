#pragma once
#include "imgui.h"

namespace Theme {

    // ── Paleta de colores BloodWorld ──────────────────────────────────────────
    // Rojo eléctrico
    static constexpr ImVec4 COL_RED        = { 0.85f, 0.08f, 0.08f, 1.00f }; // #D91414
    static constexpr ImVec4 COL_RED_HOVER  = { 1.00f, 0.18f, 0.18f, 1.00f }; // #FF2E2E
    static constexpr ImVec4 COL_RED_DIM    = { 0.55f, 0.05f, 0.05f, 1.00f }; // #8C0D0D
    // Azul eléctrico
    static constexpr ImVec4 COL_BLUE       = { 0.05f, 0.45f, 0.95f, 1.00f }; // #0D73F2
    static constexpr ImVec4 COL_BLUE_HOVER = { 0.20f, 0.60f, 1.00f, 1.00f }; // #3399FF
    // Morado eléctrico
    static constexpr ImVec4 COL_PURPLE     = { 0.50f, 0.10f, 0.90f, 1.00f }; // #8019E6
    static constexpr ImVec4 COL_PURPLE_DIM = { 0.30f, 0.05f, 0.55f, 1.00f }; // #4D0D8C

    // U32 helpers para ImDrawList
    static constexpr ImU32 U32_RED        = IM_COL32(217,  20,  20, 255);
    static constexpr ImU32 U32_RED_GLOW   = IM_COL32(255,  46,  46, 180);
    static constexpr ImU32 U32_BLUE       = IM_COL32( 13, 115, 242, 255);
    static constexpr ImU32 U32_PURPLE     = IM_COL32(128,  25, 230, 255);
    static constexpr ImU32 U32_WHITE      = IM_COL32(235, 235, 240, 255);

    inline void SetupStyle() {
        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowRounding    = 6.0f;
        style.FrameRounding     = 4.0f;
        style.PopupRounding     = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding      = 4.0f;
        style.TabRounding       = 3.0f;
        style.WindowBorderSize  = 0.0f; // Glow manual, sin borde nativo
        style.ChildBorderSize   = 0.0f;
        style.FrameBorderSize   = 0.0f;

        style.WindowPadding     = ImVec2(12, 12);
        style.FramePadding      = ImVec2(10,  5);
        style.ItemSpacing       = ImVec2(10,  8);
        style.ItemInnerSpacing  = ImVec2( 8,  6);
        style.ScrollbarSize     = 8.0f;

        ImVec4* c = style.Colors;

        c[ImGuiCol_Text]              = ImVec4(0.92f, 0.92f, 0.95f, 1.00f);
        c[ImGuiCol_TextDisabled]      = ImVec4(0.35f, 0.35f, 0.40f, 1.00f);

        // Fondos
        c[ImGuiCol_WindowBg]          = ImVec4(0.07f, 0.07f, 0.09f, 0.97f); // #111117
        c[ImGuiCol_ChildBg]           = ImVec4(0.05f, 0.05f, 0.07f, 1.00f); // #0D0D12
        c[ImGuiCol_PopupBg]           = ImVec4(0.07f, 0.07f, 0.09f, 0.96f);

        // Bordes (desactivados — el glow manual los reemplaza)
        c[ImGuiCol_Border]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        c[ImGuiCol_BorderShadow]      = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

        // Frames
        c[ImGuiCol_FrameBg]           = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
        c[ImGuiCol_FrameBgHovered]    = ImVec4(0.14f, 0.14f, 0.18f, 1.00f);
        c[ImGuiCol_FrameBgActive]     = ImVec4(0.18f, 0.10f, 0.22f, 1.00f);

        // TitleBar (oculta — usamos NoTitleBar)
        c[ImGuiCol_TitleBg]           = c[ImGuiCol_WindowBg];
        c[ImGuiCol_TitleBgActive]     = c[ImGuiCol_WindowBg];
        c[ImGuiCol_TitleBgCollapsed]  = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);

        // Botones — acento rojo base, hover azul
        c[ImGuiCol_Button]            = ImVec4(0.20f, 0.05f, 0.05f, 1.00f);
        c[ImGuiCol_ButtonHovered]     = COL_RED_HOVER;
        c[ImGuiCol_ButtonActive]      = COL_RED_DIM;

        // Headers (Sidebar selectable)
        c[ImGuiCol_Header]            = ImVec4(0.50f, 0.10f, 0.10f, 0.45f);
        c[ImGuiCol_HeaderHovered]     = ImVec4(0.85f, 0.08f, 0.08f, 0.55f);
        c[ImGuiCol_HeaderActive]      = COL_RED;

        // Tabs
        c[ImGuiCol_Tab]               = c[ImGuiCol_FrameBg];
        c[ImGuiCol_TabHovered]        = COL_BLUE_HOVER;
        c[ImGuiCol_TabActive]         = COL_BLUE;
        c[ImGuiCol_TabUnfocused]      = c[ImGuiCol_FrameBg];
        c[ImGuiCol_TabUnfocusedActive]= ImVec4(0.10f, 0.10f, 0.14f, 1.00f);

        // Sliders y checks — morado
        c[ImGuiCol_CheckMark]         = COL_PURPLE;
        c[ImGuiCol_SliderGrab]        = COL_PURPLE;
        c[ImGuiCol_SliderGrabActive]  = COL_PURPLE_DIM;

        // Scrollbar
        c[ImGuiCol_ScrollbarBg]       = ImVec4(0.02f, 0.02f, 0.03f, 0.60f);
        c[ImGuiCol_ScrollbarGrab]     = ImVec4(0.50f, 0.10f, 0.90f, 0.40f);
        c[ImGuiCol_ScrollbarGrabHovered] = COL_PURPLE;
        c[ImGuiCol_ScrollbarGrabActive]  = COL_PURPLE_DIM;

        // Separadores
        c[ImGuiCol_Separator]         = ImVec4(0.20f, 0.05f, 0.30f, 0.80f);
        c[ImGuiCol_SeparatorHovered]  = COL_PURPLE;
        c[ImGuiCol_SeparatorActive]   = COL_RED;

        // ResizeGrip
        c[ImGuiCol_ResizeGrip]        = ImVec4(0.85f, 0.08f, 0.08f, 0.20f);
        c[ImGuiCol_ResizeGripHovered] = COL_RED_HOVER;
        c[ImGuiCol_ResizeGripActive]  = COL_RED;
    }
}
