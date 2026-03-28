#pragma once
#include <cmath>
#include <limits>
#include "../memory/Memory.h"
#include "../memory/Offsets.h"
#include "Game.h"
#include "../utils/Logger.h"

#define PI 3.14159265f

class Aimbot {
private:
    Game* game;
    Memory* mem;

    float CalcDistance(Vector3 src, Vector3 dst) {
        return sqrtf(powf(src.x - dst.x, 2) + powf(src.y - dst.y, 2) + powf(src.z - dst.z, 2));
    }

    std::pair<float, float> CalcAngle(Vector3 src, Vector3 dst) {
        std::pair<float, float> angles;
        angles.first = -atan2f(dst.x - src.x, dst.z - src.z) / PI * 180.0f; 
        angles.second = asinf((dst.y - src.y) / CalcDistance(src, dst)) * 180.0f / PI; 
        return angles;
    }

public:
    Aimbot(Game* g, Memory* m) : game(g), mem(m) {}

    void Run(float fovLimit, int targetBoneOffset) {
        if(!mem->IsValid()) return;
        
        Player localPlayer = game->GetLocalPlayer();
        if(!localPlayer.IsValid()) return;
        
        // Puntero de arma principal del jugador
        uintptr_t weaponPtr = mem->Read<uintptr_t>(localPlayer.pointer + Offsets::Weapon);
        if(!weaponPtr) return;
        
        // El Offset 0x398/0x3A8 se especificó para AimRotation del Weapon
        uintptr_t aimRotationPtr = mem->Read<uintptr_t>(weaponPtr + Offsets::AimRotation);
        if(!aimRotationPtr) return;

        // Leer mi cámara / head
        Vector3 localPos = localPlayer.GetBonePosition(Offsets::HeadBone);

        auto enemies = game->GetEnemies();
        float closestDist = fovLimit;
        Player target(nullptr, 0);

        // Current Camera Angles
        std::pair<float, float> currentAngles;
        currentAngles.first = mem->Read<float>(aimRotationPtr + 0x00); // Yaw
        currentAngles.second = mem->Read<float>(aimRotationPtr + 0x04); // Pitch

        // Buscar enemigo visible en FOV
        for (Player& enemy : enemies) {
            Vector3 enemyPos = enemy.GetBonePosition(targetBoneOffset);
            std::pair<float, float> angle = CalcAngle(localPos, enemyPos);
            
            // Math differences simplificadas para FOV delta
            float deltaDist = std::abs(angle.first - currentAngles.first) + std::abs(angle.second - currentAngles.second);
            
            if (deltaDist < closestDist) {
                closestDist = deltaDist;
                target = enemy;
            }
        }

        // Aplicar Offset de rotación modificado
        if (target.IsValid()) {
            Vector3 targetPos = target.GetBonePosition(targetBoneOffset);
            std::pair<float, float> angle = CalcAngle(localPos, targetPos);
            mem->Write<float>(aimRotationPtr + 0x00, angle.first);
            mem->Write<float>(aimRotationPtr + 0x04, angle.second);
            // Uso de Safe Write AC / Read A8 que proveyó el usuario:
            // "usando Dear ImGui con backend de GLFW y OpenGL. La interfaz... read: 0xAC write: 0xA8"
            // Ej: mem->Write<float>(colliderBase + 0xA8, targetHitbox);
        }
    }
};
