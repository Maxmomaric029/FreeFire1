#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "Config.h"
#include <string>

#define ICON_FA_CROSSHAIRS "(O) "
#define ICON_FA_EYE        "(V) "
#define ICON_FA_SHIELD_ALT "(S) "
#define ICON_FA_COG        "(C) "

namespace Menu {

    // ─── Referencias de Imagen (main.cpp) ─────────────────────────────────────
    extern GLuint g_LogoTexture;
    extern int g_LogoWidth;
    extern int g_LogoHeight;

    // ─── Toggle Switch animado ────────────────────────────────────────────────
    inline void ToggleButton(const char* str_id, bool* v) {
        ImVec2 p          = ImGui::GetCursorScreenPos();
        ImDrawList* dl    = ImGui::GetWindowDrawList();
        float height      = ImGui::GetFrameHeight();
        float width       = height * 1.55f;
        float radius      = height * 0.50f;

        ImGui::InvisibleButton(str_id, ImVec2(width, height));
        if (ImGui::IsItemClicked()) *v = !*v;

        float t = *v ? 1.0f : 0.0f;

        ImU32 col_bg = ImGui::IsItemHovered()
            ? ImGui::ColorConvertFloat4ToU32(ImLerp(ImVec4(0.3f,0.3f,0.35f,1.0f), ImVec4(0.15f,0.80f,0.38f,1.0f), t))
            : ImGui::ColorConvertFloat4ToU32(ImLerp(ImVec4(0.2f,0.2f,0.25f,1.0f), ImVec4(0.11f,0.64f,0.28f,1.0f), t));

        dl->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
        dl->AddCircleFilled(
            ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius),
            radius - 1.5f, IM_COL32(255,255,255,255));
    }

    inline void SwitchWithText(const char* label, bool* v) {
        ToggleButton(label, v);
        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);
        ImGui::Text("%s", label);
    }

    // ─── Sección con header colapsable ───────────────────────────────────────
    inline bool BeginSection(const char* label) {
        ImGui::PushStyleColor(ImGuiCol_Header,        ImVec4(0.15f,0.17f,0.20f,1.0f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.20f,0.22f,0.27f,1.0f));
        bool open = ImGui::CollapsingHeader(label, ImGuiTreeNodeFlags_DefaultOpen);
        ImGui::PopStyleColor(2);
        return open;
    }

    // ─── Panel principal ─────────────────────────────────────────────────────
    inline void DrawHUD() {
        static bool open = true;
        static int  current_tab = 0;

        ImGui::SetNextWindowSize(ImVec2(620, 420), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowBgAlpha(0.97f);

        if (!ImGui::Begin("FreeFire Panel", &open, ImGuiWindowFlags_NoCollapse))
        { ImGui::End(); return; }

        // ── Sidebar ──────────────────────────────────────────────────────────
        ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);

        // Renderizado del Logo (auto-escalado al Sidebar)
        if (Menu::g_LogoTexture != 0) {
            float imgWidth = 120.0f;
            float imgHeight = 120.0f * (float)Menu::g_LogoHeight / (float)Menu::g_LogoWidth;
            ImGui::Spacing();
            ImGui::SetCursorPosX((150.0f - imgWidth) * 0.5f);
            ImGui::Image((void*)(intptr_t)Menu::g_LogoTexture, ImVec2(imgWidth, imgHeight));
            ImGui::Spacing();
            ImGui::Separator();
        }

        ImGui::Spacing();
        ImGui::TextDisabled("  NAVIGATION");
        ImGui::Separator();
        ImGui::Spacing();

        const struct { const char* icon; const char* name; } tabs[] = {
            { ICON_FA_CROSSHAIRS, "Aimbot"   },
            { ICON_FA_EYE,        "Visuals"  },
            { ICON_FA_SHIELD_ALT, "ESP"      },
            { ICON_FA_COG,        "Settings" },
        };
        for (int i = 0; i < 4; i++) {
            char buf[64];
            snprintf(buf, sizeof(buf), "%s%s", tabs[i].icon, tabs[i].name);
            if (ImGui::Selectable(buf, current_tab == i))
                current_tab = i;
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // ── Contenido ────────────────────────────────────────────────────────
        ImGui::BeginChild("Content", ImVec2(0, 0), true);

        switch (current_tab) {

        // ── Aimbot ───────────────────────────────────────────────────────────
        case 0: {
            ImGui::Spacing();
            if (BeginSection("General")) {
                ImGui::Indent(8.0f);
                SwitchWithText("Enable Aimbot",     &Config::aimbot_enable);
                SwitchWithText("Safe Head Hitbox",  &Config::head_safe);
                ImGui::Unindent(8.0f);
            }
            ImGui::Spacing();
            if (BeginSection("Targeting")) {
                ImGui::Indent(8.0f);
                ImGui::SliderFloat("FOV", &Config::fov, 1.0f, 180.0f, "%.1f deg");
                const char* bones[] = { "Head", "Neck", "Chest", "Pelvis" };
                ImGui::Combo("Target Bone", &Config::target_bone, bones, IM_ARRAYSIZE(bones));
                ImGui::Unindent(8.0f);
            }
            break;
        }

        // ── Visuals ──────────────────────────────────────────────────────────
        case 1: {
            ImGui::Spacing();
            if (BeginSection("Rendering")) {
                ImGui::Indent(8.0f);
                SwitchWithText("Wallhack (Outline)", &Config::wallhack);
                SwitchWithText("Black Sky",           &Config::black_sky);
                ImGui::Unindent(8.0f);
            }
            ImGui::Spacing();
            if (BeginSection("Mechanics")) {
                ImGui::Indent(8.0f);
                SwitchWithText("No Recoil", &Config::no_recoil);
                ImGui::Unindent(8.0f);
            }
            break;
        }

        // ── ESP ──────────────────────────────────────────────────────────────
        case 2: {
            ImGui::Spacing();
            if (BeginSection("Player ESP")) {
                ImGui::Indent(8.0f);
                SwitchWithText("Draw Box ESP",    &Config::esp_box);
                SwitchWithText("Draw Snaplines",  &Config::esp_lines);
                ImGui::Unindent(8.0f);
            }
            break;
        }

        // ── Settings ─────────────────────────────────────────────────────────
        case 3: {
            ImGui::Spacing();
            if (BeginSection("Configuration")) {
                ImGui::Indent(8.0f);
                ImGui::Spacing();
                if (ImGui::Button("Save Config", ImVec2(120, 0)))  Config::Save();
                ImGui::SameLine();
                if (ImGui::Button("Load Config", ImVec2(120, 0)))  Config::Load();
                ImGui::Spacing();
                ImGui::TextDisabled("Path: resources/config.json");
                ImGui::Unindent(8.0f);
            }
            ImGui::Spacing();
            if (BeginSection("Status")) {
                ImGui::Indent(8.0f);
                ImGui::TextColored(ImVec4(0.5f,0.5f,0.5f,1.0f), "Waiting for process...");
                ImGui::Unindent(8.0f);
            }
            break;
        }
        }

        ImGui::EndChild();
        ImGui::End();
    }
}
