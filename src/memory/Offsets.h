#pragma once
#include <cstdint>

namespace Offsets {
    // Estas bases normalmente cambian por versión (BETA, V7A, PLAY, INDIA)
    constexpr uintptr_t InitBase = 0xA3F438C; // Ejemplo PLAY Store version

    // Game Entities
    constexpr uintptr_t StaticClass = 0x5C;
    constexpr uintptr_t CurrentMatch = 0x50;
    constexpr uintptr_t LocalPlayer = 0x7C;
    constexpr uintptr_t DictionaryEntities = 0x68;

    // Player Data
    constexpr uintptr_t Player_IsDead = 0x4C;
    constexpr uintptr_t Player_Name = 0x28C;
    constexpr uintptr_t Player_Data = 0x44;
    constexpr uintptr_t IsBot = 0x294;

    // Aimbot Data
    constexpr uintptr_t AimRotation = 0x3A8;
    constexpr uintptr_t HeadBone = 0x3F8;
    constexpr uintptr_t SpineX = 0x400;
    constexpr uintptr_t ViewMatrix = 0xBC; // de Camera
}
