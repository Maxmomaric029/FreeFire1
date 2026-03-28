#pragma once
#include "imgui.h"

namespace Glow {

    // Glow en un texto
    inline void Text(ImDrawList* dl, ImVec2 pos, ImU32 color, const char* text, float intensity = 4.0f) {
        // Capas de sombra (glow)
        for (float i = intensity; i > 0; i -= 1.0f) {
            ImU32 glow_col = (color & 0x00FFFFFF) | (ImU32)(50.0f * (i / intensity)) << 24;
            dl->AddText(ImVec2(pos.x - i, pos.y - i), glow_col, text);
            dl->AddText(ImVec2(pos.x + i, pos.y - i), glow_col, text);
            dl->AddText(ImVec2(pos.x - i, pos.y + i), glow_col, text);
            dl->AddText(ImVec2(pos.x + i, pos.y + i), glow_col, text);
        }
        // Texto real encima
        dl->AddText(pos, color, text);
    }

    // Glow en una línea (para decoraciones y separadores)
    inline void Line(ImDrawList* dl, ImVec2 a, ImVec2 b, ImU32 color, float thickness = 1.5f, float intensity = 6.0f) {
        for (float i = intensity; i > 0; i -= 1.5f) {
            ImU32 glow_col = (color & 0x00FFFFFF) | (ImU32)(40.0f * (i / intensity)) << 24;
            dl->AddLine(a, b, glow_col, thickness + i);
        }
        dl->AddLine(a, b, color, thickness);
    }

    // Glow en un rectángulo (para borders de ventana o secciones)
    inline void Rect(ImDrawList* dl, ImVec2 min, ImVec2 max, ImU32 color, float rounding = 4.0f, float intensity = 5.0f) {
        for (float i = intensity; i > 0; i -= 1.0f) {
            ImU32 glow_col = (color & 0x00FFFFFF) | (ImU32)(35.0f * (i / intensity)) << 24;
            dl->AddRect(
                ImVec2(min.x - i, min.y - i),
                ImVec2(max.x + i, max.y + i),
                glow_col, rounding + i);
        }
        dl->AddRect(min, max, color, rounding);
    }
}
