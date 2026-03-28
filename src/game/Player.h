#pragma once
#include <string>
#include "../memory/Memory.h"
#include "../memory/Offsets.h"

struct Vector3 {
    float x, y, z;
};

class Player {
private:
    Memory* mem;
    uintptr_t pointer;

public:
    Player(Memory* memory, uintptr_t ptr) : mem(memory), pointer(ptr) {}

    bool IsValid() const {
        return pointer != 0;
    }

    bool IsDead() {
        if(!IsValid()) return true;
        return mem->Read<bool>(pointer + Offsets::Player_IsDead);
    }

    bool IsBot() {
        if(!IsValid()) return false;
        return mem->Read<bool>(pointer + Offsets::IsBot);
    }

    std::string GetName() {
        if(!IsValid()) return "";
        uintptr_t namePtr = mem->Read<uintptr_t>(pointer + Offsets::Player_Name);
        if(!namePtr) return "";
        // Leer string de Unity (C# string: length 4 bytes at offset 0x10, unicode chars at 0x14)
        int length = mem->Read<int>(namePtr + 0x10);
        if(length > 0 && length < 32) {
            char16_t buffer[32];
            mem->ReadProcessMemory(mem->hProcess, (LPCVOID)(namePtr + 0x14), buffer, length * 2, NULL);
            std::string result(buffer, buffer + length); // Simple conversion
            return result;
        }
        return "";
    }

    Vector3 GetBonePosition(int boneID) {
        if(!IsValid()) return {0,0,0};
        
        // Simulación de lectura de transform (por ejemplo desde HeadBone 0x3F8 o Spine)
        uintptr_t boneTransform = mem->Read<uintptr_t>(pointer + boneID); 
        if(!boneTransform) return {0,0,0};
        
        // La posición generalmente se encuentra en la jerarquía del Transform de Unity
        uintptr_t hierarchy = mem->Read<uintptr_t>(boneTransform + 0x38);
        uintptr_t posData = mem->Read<uintptr_t>(hierarchy + 0x18);
        
        return mem->Read<Vector3>(posData + 0x90);
    }
};
