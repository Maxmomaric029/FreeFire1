#pragma once
#include "imgui.h"
#include <string>

#define ICON_FA_CROSSHAIRS "(O) "
#define ICON_FA_EYE        "(V) "
#define ICON_FA_SHIELD_ALT "(S) "
#define ICON_FA_COG        "(C) "

namespace Menu {
    // Custom Toggle Switch (sustituto del Checkbox estándar)
    inline void ToggleButton(const char* str_id, bool* v) {
        ImVec2 p = ImGui::GetCursorScreenPos();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        float height = ImGui::GetFrameHeight();
        float width = height * 1.55f;
        float radius = height * 0.50f;

        ImGui::InvisibleButton(str_id, ImVec2(width, height));
        if (ImGui::IsItemClicked())
            *v = !*v;

        float t = *v ? 1.0f : 0.0f;
        ImGuiContext& g = *GImGui;
        float ANIM_SPEED = 0.08f;
        if (g.LastActiveId == g.CurrentWindow->GetID(str_id)) // Animación muy básica
            t = *v ? 1.0f : 0.0f;

        ImU32 col_bg;
        if (ImGui::IsItemHovered())
            col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.3f, 0.3f, 0.35f, 1.0f), ImVec4(0.15f, 0.80f, 0.38f, 1.0f), t));
        else
            col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.2f, 0.2f, 0.25f, 1.0f), ImVec4(0.11f, 0.64f, 0.28f, 1.0f), t));

        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
        draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
    }

    inline void SwitchWithText(const char* label, bool* v) {
        ToggleButton(label, v);
        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);
        ImGui::Text("%s", label);
    }

    inline void DrawHUD() {
        static bool open = true;
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("FreeFire Modern Panel", &open, ImGuiWindowFlags_NoCollapse)) {
            
            // Layout de 2 columnas: Menú Izquierdo (Tabs) y Contenido Derecho
            ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);
            
            static int current_tab = 0;
            if (ImGui::Selectable(ICON_FA_CROSSHAIRS "Aimbot", current_tab == 0)) current_tab = 0;
            if (ImGui::Selectable(ICON_FA_EYE "Visuals", current_tab == 1)) current_tab = 1;
            if (ImGui::Selectable(ICON_FA_SHIELD_ALT "Esp", current_tab == 2)) current_tab = 2;
            if (ImGui::Selectable(ICON_FA_COG "Settings", current_tab == 3)) current_tab = 3;
            
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("Content", ImVec2(0, 0), true);

            if (current_tab == 0) { // Aimbot
                ImGui::Text("Aimbot Settings");
                ImGui::Separator();
                
                static bool aimbot_enable = false;
                static bool head_safe = false;
                static float fov = 15.0f;
                static int target_bone = 0;
                
                SwitchWithText("Enable Aimbot", &aimbot_enable);
                SwitchWithText("Safe Head Hitbox", &head_safe);
                
                ImGui::Spacing();
                ImGui::SliderFloat("FOV", &fov, 1.0f, 180.0f, "%.1f degrees");
                
                const char* bones[] = { "Head", "Neck", "Chest", "Pelvis" };
                ImGui::Combo("Target Bone", &target_bone, bones, IM_ARRAYSIZE(bones));
            }
            else if (current_tab == 1) { // Visuals / Misc
                ImGui::Text("Visual Enhancements");
                ImGui::Separator();

                static bool wallhack = false;
                static bool no_recoil = false;
                static bool black_sky = false;

                SwitchWithText("Wallhack (Entity Outline)", &wallhack);
                SwitchWithText("No Recoil", &no_recoil);
                SwitchWithText("Black Sky", &black_sky);
            }
            else if (current_tab == 2) { // ESP
               ImGui::Text("ESP Configuration");
               ImGui::Separator();
               
               static bool esp_box = false;
               static bool esp_lines = false;
               
               SwitchWithText("Draw Box ESP", &esp_box);
               SwitchWithText("Draw Snaplines", &esp_lines);
            }
            else if (current_tab == 3) {
                ImGui::Text("Injector Engine Setup");
                ImGui::Separator();
                ImGui::TextColored(ImVec4(0.5f,0.5f,0.5f,1.0f), "Status: Waiting for process...");
            }

            ImGui::EndChild();
        }
        ImGui::End();
    }
}
