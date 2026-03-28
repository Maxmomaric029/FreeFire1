#pragma once
#include "../memory/Memory.h"
#include "../memory/Offsets.h"
#include "Player.h"

class Game {
private:
    Memory* mem;
    uintptr_t baseAddress;

public:
    Game(Memory* m) : mem(m) {
        // En un emulador, InitBase sería offset desde el módulo nativo, 
        // aquí es un offset fijo precompilado como ejemplo.
        baseAddress = Offsets::InitBase; 
    }

    uintptr_t GetMatchStatus() {
        uintptr_t staticClass = mem->Read<uintptr_t>(baseAddress + Offsets::StaticClass);
        if(!staticClass) return 0;
        return mem->Read<uintptr_t>(staticClass + 0x74); // MatchStatus 0x74
    }

    Player GetLocalPlayer() {
        uintptr_t staticClass = mem->Read<uintptr_t>(baseAddress + Offsets::StaticClass);
        uintptr_t currentMatch = mem->Read<uintptr_t>(staticClass + Offsets::CurrentMatch);
        uintptr_t localPlayerPtr = mem->Read<uintptr_t>(currentMatch + Offsets::LocalPlayer);
        return Player(mem, localPlayerPtr);
    }

    // Retorna una lista de enemigos en la partida
    std::vector<Player> GetEnemies() {
        std::vector<Player> enemies;
        uintptr_t staticClass = mem->Read<uintptr_t>(baseAddress + Offsets::StaticClass);
        uintptr_t currentMatch = mem->Read<uintptr_t>(staticClass + Offsets::CurrentMatch);
        uintptr_t dictEntities = mem->Read<uintptr_t>(currentMatch + Offsets::DictionaryEntities);
        
        // Simulación de iteración de Dictionary C#
        int numEntities = mem->Read<int>(dictEntities + 0x18); // Ejemplo: offset length C# dict
        uintptr_t entriesArray = mem->Read<uintptr_t>(dictEntities + 0x10);
        
        for (int i = 0; i < numEntities; i++) {
            // Cada Entry = {hashCode, next, key, value} (24 bytes)
            uintptr_t playerPtr = mem->Read<uintptr_t>(entriesArray + 0x20 + (i * 0x18) + 0x10); 
            if (playerPtr) {
                Player p(mem, playerPtr);
                if(!p.IsBot() && !p.IsDead()) {
                    enemies.push_back(p);
                }
            }
        }
        return enemies;
    }
};
