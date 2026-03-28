#pragma once
#include "imgui.h"

namespace Glow {

    // ── Texto con glow ────────────────────────────────────────────────────────
    inline void Text(ImDrawList* dl, ImVec2 pos, ImU32 color, const char* text,
                     float intensity = 5.0f, ImFont* font = nullptr, float font_size = 0.0f) {
        float sz = (font_size > 0.f) ? font_size : (font ? font->FontSize : ImGui::GetFontSize());
        for (float i = intensity; i > 0.f; i -= 1.0f) {
            float a  = 60.f * (i / intensity);
            ImU32 gc = (color & 0x00FFFFFF) | ((ImU32)a << 24);
            dl->AddText(font, sz, ImVec2(pos.x - i, pos.y    ), gc, text);
            dl->AddText(font, sz, ImVec2(pos.x + i, pos.y    ), gc, text);
            dl->AddText(font, sz, ImVec2(pos.x,     pos.y - i), gc, text);
            dl->AddText(font, sz, ImVec2(pos.x,     pos.y + i), gc, text);
        }
        dl->AddText(font, sz, pos, color, text);
    }

    // ── Línea con glow ────────────────────────────────────────────────────────
    inline void Line(ImDrawList* dl, ImVec2 a, ImVec2 b, ImU32 color,
                     float thickness = 1.5f, float intensity = 6.0f) {
        for (float i = intensity; i > 0.f; i -= 1.5f) {
            float a_ = 45.f * (i / intensity);
            ImU32 gc = (color & 0x00FFFFFF) | ((ImU32)a_ << 24);
            dl->AddLine(a, b, gc, thickness + i);
        }
        dl->AddLine(a, b, color, thickness);
    }

    // ── Rectángulo con glow ───────────────────────────────────────────────────
    inline void Rect(ImDrawList* dl, ImVec2 mn, ImVec2 mx, ImU32 color,
                     float rounding = 5.0f, float intensity = 6.0f) {
        for (float i = intensity; i > 0.f; i -= 1.0f) {
            float a  = 38.f * (i / intensity);
            ImU32 gc = (color & 0x00FFFFFF) | ((ImU32)a << 24);
            dl->AddRect(ImVec2(mn.x - i, mn.y - i),
                        ImVec2(mx.x + i, mx.y + i),
                        gc, rounding + i);
        }
        dl->AddRect(mn, mx, color, rounding);
    }

    // ── Relleno con glow (para sidebar activo, etc.) ─────────────────────────
    inline void RectFilled(ImDrawList* dl, ImVec2 mn, ImVec2 mx, ImU32 color,
                           float rounding = 3.0f, float glow_intensity = 4.0f) {
        // Capa de glow exterior
        for (float i = glow_intensity; i > 0.f; i -= 1.0f) {
            float a  = 30.f * (i / glow_intensity);
            ImU32 gc = (color & 0x00FFFFFF) | ((ImU32)a << 24);
            dl->AddRectFilled(ImVec2(mn.x - i, mn.y - i),
                              ImVec2(mx.x + i, mx.y + i),
                              gc, rounding + i);
        }
        dl->AddRectFilled(mn, mx, color, rounding);
    }

    // ── X decorativa ─────────────────────────────────────────────────────────
    inline void DecorativeX(ImDrawList* dl, ImVec2 center, float size, ImU32 color,
                            float thickness = 1.2f, float intensity = 4.0f) {
        float h = size * 0.5f;
        Line(dl, ImVec2(center.x - h, center.y - h),
                 ImVec2(center.x + h, center.y + h), color, thickness, intensity);
        Line(dl, ImVec2(center.x + h, center.y - h),
                 ImVec2(center.x - h, center.y + h), color, thickness, intensity);
    }
}
