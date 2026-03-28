#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "Config.h"
#include "Glow.h"
#include "Theme.h"
#include <GL/gl.h>
#include <string>
#include <cmath>   // sinf, para animación pulse

// ── Font Awesome (reemplaza con el header real si tienes FA integrado) ────────
#define ICON_AIMBOT   "\xef\x84\x9b"  // fa-crosshairs   U+F11B
#define ICON_VISUALS  "\xef\x81\xae"  // fa-eye          U+F06E
#define ICON_ESP      "\xef\x83\xa1"  // fa-shield       U+F0E1 (shield-alt)
#define ICON_SETTINGS "\xef\x80\x93"  // fa-cog          U+F013

namespace Menu {

    // ─────────────────────────────────────────────────────────────────────────
    // Toggle Switch  —  colores sincronizados con paleta BloodWorld
    // ─────────────────────────────────────────────────────────────────────────
    inline void ToggleButton(const char* str_id, bool* v) {
        ImVec2 p      = ImGui::GetCursorScreenPos();
        ImDrawList* dl= ImGui::GetWindowDrawList();
        float height  = ImGui::GetFrameHeight();
        float width   = height * 1.60f;
        float radius  = height * 0.50f;

        ImGui::InvisibleButton(str_id, ImVec2(width, height));
        if (ImGui::IsItemClicked()) *v = !*v;

        float t = *v ? 1.0f : 0.0f;

        // Fondo: apagado = gris oscuro | encendido = rojo eléctrico
        ImVec4 off_n  = { 0.14f, 0.14f, 0.17f, 1.f };
        ImVec4 off_h  = { 0.20f, 0.20f, 0.24f, 1.f };
        ImVec4 on_n   = { 0.85f, 0.08f, 0.08f, 1.f }; // rojo
        ImVec4 on_h   = { 1.00f, 0.18f, 0.18f, 1.f };

        ImU32 col_bg = ImGui::IsItemHovered()
            ? ImGui::ColorConvertFloat4ToU32(ImLerp(off_h, on_h, t))
            : ImGui::ColorConvertFloat4ToU32(ImLerp(off_n, on_n, t));

        dl->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);

        // Pequeño glow cuando está ON
        if (t > 0.5f) {
            ImU32 glow = IM_COL32(217, 20, 20, (ImU32)(60 * t));
            dl->AddRectFilled(ImVec2(p.x - 2, p.y - 2),
                              ImVec2(p.x + width + 2, p.y + height + 2),
                              glow, height * 0.5f + 2);
        }

        // Círculo blanco
        float cx = p.x + radius + t * (width - radius * 2.0f);
        dl->AddCircleFilled(ImVec2(cx, p.y + radius), radius - 2.0f,
                            IM_COL32(240, 240, 245, 255));
    }

    inline void SwitchWithText(const char* label, bool* v) {
        ToggleButton(label, v);
        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);
        ImGui::Text("%s", label);
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Sección colapsable — con línea de acento morado a la izquierda
    // ─────────────────────────────────────────────────────────────────────────
    inline bool BeginSection(const char* label) {
        ImGui::PushStyleColor(ImGuiCol_Header,        ImVec4(0.18f, 0.05f, 0.28f, 0.55f));
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.30f, 0.08f, 0.45f, 0.70f));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive,  ImVec4(0.50f, 0.10f, 0.90f, 0.80f));
        bool open = ImGui::CollapsingHeader(label, ImGuiTreeNodeFlags_DefaultOpen);
        ImGui::PopStyleColor(3);

        if (open) {
            // Línea morada vertical a la izquierda del contenido
            ImVec2 cur = ImGui::GetCursorScreenPos();
            float  h   = ImGui::GetTextLineHeightWithSpacing() * 3.5f; // estimado
            Glow::Line(ImGui::GetWindowDrawList(),
                       ImVec2(cur.x - 4, cur.y),
                       ImVec2(cur.x - 4, cur.y + h),
                       Theme::U32_PURPLE, 1.5f, 3.0f);
        }
        return open;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Botón estilizado con glow rojo
    // ─────────────────────────────────────────────────────────────────────────
    inline bool GlowButton(const char* label, ImVec2 size = ImVec2(0,0)) {
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.22f, 0.04f, 0.04f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.85f, 0.08f, 0.08f, 1.f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.55f, 0.05f, 0.05f, 1.f));
        bool clicked = ImGui::Button(label, size);
        ImGui::PopStyleColor(3);

        if (ImGui::IsItemHovered()) {
            ImVec2 mn = ImGui::GetItemRectMin();
            ImVec2 mx = ImGui::GetItemRectMax();
            Glow::Rect(ImGui::GetWindowDrawList(), mn, mx,
                       Theme::U32_RED_GLOW, 4.f, 4.f);
        }
        return clicked;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Input con solo línea inferior (estilo Delete Hex)
    // ─────────────────────────────────────────────────────────────────────────
    inline void UnderlineInput(const char* label, char* buf, size_t buf_size,
                               ImGuiInputTextFlags flags = 0) {
        ImGui::PushStyleColor(ImGuiCol_FrameBg,        ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0,0,0,0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,  ImVec4(0,0,0,0));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
        ImGui::InputText(label, buf, buf_size, flags);
        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar();

        // Línea roja inferior
        ImVec2 mn = ImGui::GetItemRectMin();
        ImVec2 mx = ImGui::GetItemRectMax();
        bool   hv = ImGui::IsItemActive() || ImGui::IsItemHovered();
        ImU32  lc = hv ? Theme::U32_RED_GLOW : Theme::U32_RED;
        float  li = hv ? 3.5f : 1.5f;
        Glow::Line(ImGui::GetWindowDrawList(),
                   ImVec2(mn.x, mx.y), ImVec2(mx.x, mx.y),
                   lc, 1.5f, li);
    }

    // ─────────────────────────────────────────────────────────────────────────
    //  DrawHUD — ventana principal
    // ─────────────────────────────────────────────────────────────────────────
    inline void DrawHUD() {
        static bool open       = true;
        static int  current_tab= 0;

        const float WIN_W = 650.f;
        const float WIN_H = 430.f;
        const float SIDE_W= 140.f;

        ImGui::SetNextWindowSize(ImVec2(WIN_W, WIN_H), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.97f);

        // Sin padding para control total del layout
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

        const ImGuiWindowFlags wflags =
            ImGuiWindowFlags_NoCollapse  |
            ImGuiWindowFlags_NoTitleBar  |
            ImGuiWindowFlags_NoResize    |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse;

        if (!ImGui::Begin("##bloodworld", &open, wflags)) {
            ImGui::PopStyleVar();
            ImGui::End();
            return;
        }
        ImGui::PopStyleVar(); // restaurar padding

        ImDrawList* dl  = ImGui::GetWindowDrawList();
        ImVec2      wPos= ImGui::GetWindowPos();
        ImVec2      wSz = ImGui::GetWindowSize();

        // ── Borde exterior con glow rojo ──────────────────────────────────────
        Glow::Rect(dl,
            ImVec2(wPos.x + 1, wPos.y + 1),
            ImVec2(wPos.x + wSz.x - 1, wPos.y + wSz.y - 1),
            Theme::U32_RED, 6.f, 8.f);

        // ── Línea divisoria sidebar | contenido ───────────────────────────────
        Glow::Line(dl,
            ImVec2(wPos.x + SIDE_W, wPos.y + 10),
            ImVec2(wPos.x + SIDE_W, wPos.y + wSz.y - 10),
            Theme::U32_RED, 1.0f, 5.0f);

        // ── X decorativas de fondo ────────────────────────────────────────────
        // Grupo izquierdo (sidebar bg)
        Glow::DecorativeX(dl, ImVec2(wPos.x + 70,  wPos.y + 260), 55.f, IM_COL32(217,20,20, 18), 1.0f, 3.f);
        Glow::DecorativeX(dl, ImVec2(wPos.x + 100, wPos.y + 340), 30.f, IM_COL32(217,20,20, 12), 0.8f, 2.f);
        // Grupo derecho (content bg)
        Glow::DecorativeX(dl, ImVec2(wPos.x + 540, wPos.y + 360), 60.f, IM_COL32(128,25,230, 15), 1.0f, 3.f);
        Glow::DecorativeX(dl, ImVec2(wPos.x + 480, wPos.y +  60), 35.f, IM_COL32( 13,115,242, 12), 0.8f, 2.f);
        Glow::DecorativeX(dl, ImVec2(wPos.x + 580, wPos.y + 200), 25.f, IM_COL32(217,20,20, 10), 0.8f, 2.f);

        // ── Línea superior decorativa (degradado rojo → morado) ───────────────
        dl->AddRectFilledMultiColor(
            ImVec2(wPos.x + 1,        wPos.y + 1),
            ImVec2(wPos.x + wSz.x/2,  wPos.y + 2),
            IM_COL32(217,20,20,200), IM_COL32(128,25,230,200),
            IM_COL32(128,25,230,200), IM_COL32(217,20,20,200));
        dl->AddRectFilledMultiColor(
            ImVec2(wPos.x + wSz.x/2,  wPos.y + 1),
            ImVec2(wPos.x + wSz.x - 1,wPos.y + 2),
            IM_COL32(128,25,230,200), IM_COL32( 13,115,242,200),
            IM_COL32( 13,115,242,200), IM_COL32(128,25,230,200));

        // ══════════════════════════════════════════════════════════════════════
        // SIDEBAR
        // ══════════════════════════════════════════════════════════════════════
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::BeginChild("##sidebar", ImVec2(SIDE_W, 0), false);

        // ── Logo en texto con glow ────────────────────────────────────────────
        ImGui::Spacing(); ImGui::Spacing();

        // "Blood" en rojo con glow
        {
            const char* txt1 = "Blood";
            ImVec2 tsz1 = ImGui::CalcTextSize(txt1);
            float  cx1  = (SIDE_W - tsz1.x) * 0.5f;
            ImVec2 tpos1= ImVec2(wPos.x + cx1, wPos.y + ImGui::GetCursorPosY());
            Glow::Text(dl, tpos1, Theme::U32_RED, txt1, 7.0f);
            ImGui::Dummy(ImVec2(0, tsz1.y + 2));
        }
        // "World" en blanco con glow suave azul
        {
            const char* txt2 = "World";
            ImVec2 tsz2 = ImGui::CalcTextSize(txt2);
            float  cx2  = (SIDE_W - tsz2.x) * 0.5f;
            ImVec2 tpos2= ImVec2(wPos.x + cx2, wPos.y + ImGui::GetCursorPosY());
            Glow::Text(dl, tpos2, Theme::U32_WHITE, txt2, 3.5f);
            ImGui::Dummy(ImVec2(0, tsz2.y + 2));
        }
        // Subtítulo versión en morado dimmer
        {
            const char* ver = "v1.0.0";
            ImVec2 vsz = ImGui::CalcTextSize(ver);
            float  vcx = (SIDE_W - vsz.x) * 0.5f;
            ImGui::SetCursorPosX(vcx);
            ImGui::TextColored(ImVec4(0.50f, 0.10f, 0.90f, 0.70f), "%s", ver);
        }

        ImGui::Spacing();
        // Separador rojo
        {
            ImVec2 sp = ImGui::GetCursorScreenPos();
            Glow::Line(dl,
                ImVec2(sp.x + 8,          sp.y),
                ImVec2(sp.x + SIDE_W - 18, sp.y),
                Theme::U32_RED, 1.0f, 3.0f);
            ImGui::Dummy(ImVec2(0, 6));
        }

        ImGui::Spacing();
        ImGui::SetCursorPosX(6);
        ImGui::TextColored(ImVec4(0.35f,0.35f,0.40f,1.f), "MENU");
        ImGui::Spacing();

        // ── Tabs del sidebar ──────────────────────────────────────────────────
        struct TabInfo { const char* icon; const char* name; };
        static const TabInfo tabs[] = {
            { ICON_AIMBOT,   "  Aimbot"    },
            { ICON_VISUALS,  "  Visuals"   },
            { ICON_ESP,      "  ESP"       },
            { ICON_SETTINGS, "  Settings"  },
        };

        for (int i = 0; i < 4; i++) {
            bool selected = (current_tab == i);
            ImVec2 item_pos = ImGui::GetCursorScreenPos();
            float  item_w   = SIDE_W - 12;
            float  item_h   = ImGui::GetFrameHeight() + 4;

            // Fondo activo con glow rojo
            if (selected) {
                Glow::RectFilled(dl,
                    item_pos,
                    ImVec2(item_pos.x + item_w, item_pos.y + item_h),
                    IM_COL32(120, 10, 10, 120), 3.f, 3.f);
                // Acento vertical izquierdo
                Glow::Line(dl,
                    ImVec2(item_pos.x + 2, item_pos.y + 3),
                    ImVec2(item_pos.x + 2, item_pos.y + item_h - 3),
                    Theme::U32_RED, 2.5f, 4.f);
            }

            char buf[64];
            snprintf(buf, sizeof(buf), "%s%s##tab%d", tabs[i].icon, tabs[i].name, i);

            ImGui::PushStyleColor(ImGuiCol_HeaderActive,  ImVec4(0,0,0,0));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered,
                selected ? ImVec4(0,0,0,0) : ImVec4(0.20f,0.05f,0.05f,0.50f));
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0,0,0,0));

            if (ImGui::Selectable(buf, selected, 0, ImVec2(item_w, item_h)))
                current_tab = i;

            ImGui::PopStyleColor(3);
        }

        // Footer
        ImGui::SetCursorPosY(WIN_H - 30);
        {
            ImVec2 fp = ImGui::GetCursorScreenPos();
            Glow::Line(dl,
                ImVec2(fp.x + 6,           fp.y),
                ImVec2(fp.x + SIDE_W - 16, fp.y),
                Theme::U32_PURPLE, 0.8f, 2.f);
            ImGui::Dummy(ImVec2(0, 4));
        }
        ImGui::SetCursorPosX(4);
        ImGui::TextColored(ImVec4(0.30f,0.30f,0.35f,1.f), " BloodWorld");

        ImGui::EndChild();
        ImGui::PopStyleVar();

        // ══════════════════════════════════════════════════════════════════════
        // CONTENT AREA
        // ══════════════════════════════════════════════════════════════════════
        ImGui::SetCursorPos(ImVec2(SIDE_W + 6, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 10));
        ImGui::BeginChild("##content", ImVec2(0, 0), false);

        switch (current_tab) {

        // ── Aimbot ─────────────────────────────────────────────────────────
        case 0: {
            ImGui::Spacing();
            // Título de sección con glow
            {
                ImVec2 tp = ImGui::GetCursorScreenPos();
                Glow::Text(dl, tp, Theme::U32_RED, "AIMBOT", 4.f);
                ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight() + 6));
                Glow::Line(dl,
                    ImVec2(tp.x, tp.y + ImGui::GetTextLineHeight() + 8),
                    ImVec2(tp.x + 200, tp.y + ImGui::GetTextLineHeight() + 8),
                    Theme::U32_RED, 1.f, 3.f);
            }
            ImGui::Spacing();

            if (BeginSection("General")) {
                ImGui::Indent(12.f);
                SwitchWithText("Enable Aimbot",  &Config::aimbot_enable);
                SwitchWithText("Safe Head Hitbox",  &Config::head_safe);
                ImGui::Unindent(12.f);
            }
            ImGui::Spacing();
            if (BeginSection("Targeting")) {
                ImGui::Indent(12.f);
                ImGui::SliderFloat("FOV", &Config::fov, 1.f, 180.f, "%.1f deg");
                const char* items[] = { "Head", "Neck", "Chest", "Pelvis" };
                ImGui::Combo("Target Bone", &Config::target_bone, items, IM_ARRAYSIZE(items));
                ImGui::Unindent(12.f);
            }
            break;
        }

        // ── Visuals ─────────────────────────────────────────────────────────
        case 1: {
            ImGui::Spacing();
            {
                ImVec2 tp = ImGui::GetCursorScreenPos();
                Glow::Text(dl, tp, Theme::U32_BLUE, "VISUALS", 4.f);
                ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight() + 6));
                Glow::Line(dl,
                    ImVec2(tp.x, tp.y + ImGui::GetTextLineHeight() + 8),
                    ImVec2(tp.x + 200, tp.y + ImGui::GetTextLineHeight() + 8),
                    Theme::U32_BLUE, 1.f, 3.f);
            }
            ImGui::Spacing();

            if (BeginSection("Rendering")) {
                ImGui::Indent(12.f);
                SwitchWithText("Wallhack (Outline)", &Config::wallhack);
                SwitchWithText("Black Sky", &Config::black_sky);
                ImGui::Unindent(12.f);
            }
            ImGui::Spacing();
            if (BeginSection("Mechanics")) {
                ImGui::Indent(12.f);
                SwitchWithText("No Recoil", &Config::no_recoil);
                ImGui::Unindent(12.f);
            }
            break;
        }

        // ── ESP ─────────────────────────────────────────────────────────
        case 2: {
            ImGui::Spacing();
            {
                ImVec2 tp = ImGui::GetCursorScreenPos();
                Glow::Text(dl, tp, Theme::U32_PURPLE, "ESP", 4.f);
                ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight() + 6));
                Glow::Line(dl,
                    ImVec2(tp.x, tp.y + ImGui::GetTextLineHeight() + 8),
                    ImVec2(tp.x + 200, tp.y + ImGui::GetTextLineHeight() + 8),
                    Theme::U32_PURPLE, 1.f, 3.f);
            }
            ImGui::Spacing();

            if (BeginSection("Options")) {
                ImGui::Indent(12.f);
                SwitchWithText("Draw Box ESP", &Config::esp_box);
                SwitchWithText("Draw Snaplines", &Config::esp_lines);
                ImGui::Unindent(12.f);
            }
            break;
        }

        // ── Settings ──────────────────────────────────────────────────────────
        case 3: {
            ImGui::Spacing();
            {
                ImVec2 tp = ImGui::GetCursorScreenPos();
                Glow::Text(dl, tp, Theme::U32_WHITE, "SETTINGS", 3.f);
                ImGui::Dummy(ImVec2(0, ImGui::GetTextLineHeight() + 6));
                Glow::Line(dl,
                    ImVec2(tp.x, tp.y + ImGui::GetTextLineHeight() + 8),
                    ImVec2(tp.x + 200, tp.y + ImGui::GetTextLineHeight() + 8),
                    Theme::U32_WHITE, 1.f, 2.f);
            }
            ImGui::Spacing();

            if (BeginSection("Configuration")) {
                ImGui::Indent(12.f);
                ImGui::Spacing();
                if (GlowButton("Save Config", ImVec2(120, 0))) Config::Save();
                ImGui::SameLine();
                if (GlowButton("Load Config", ImVec2(120, 0))) Config::Load();
                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.35f,0.35f,0.40f,1.f),
                    "Path: resources/config.json");
                ImGui::Unindent(12.f);
            }
            ImGui::Spacing();
            if (BeginSection("Status")) {
                ImGui::Indent(12.f);
                // Indicador pulsante
                static float pulse_t = 0.f;
                pulse_t += ImGui::GetIO().DeltaTime * 2.f;
                float alpha = 0.5f + 0.5f * sinf(pulse_t);
                ImGui::TextColored(
                    ImVec4(0.85f, 0.08f, 0.08f, alpha),
                    "● Waiting for process...");
                ImGui::Unindent(12.f);
            }
            break;
        }
        } // switch

        ImGui::EndChild();
        ImGui::PopStyleVar();

        ImGui::End();
    }

} // namespace Menu
