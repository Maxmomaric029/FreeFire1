#pragma once
#include "PatchesData.h"
#include "../memory/Memory.h"
#include "../utils/Logger.h"

class PatchManager {
private:
    Memory* mem;

    std::vector<uint8_t> SignatureToBytes(const std::string& sig) {
        std::vector<uint8_t> bytes;
        std::istringstream stream(sig);
        std::string word;
        while (stream >> word) {
            if (word != "??" && word != "?")
                bytes.push_back((uint8_t)strtoul(word.c_str(), nullptr, 16));
            else
                bytes.push_back(0); // Para reemplazar, los '?' no deben ocurrir en ReplacePattern
        }
        return bytes;
    }

public:
    PatchManager(Memory* memInst) : mem(memInst) {}

    void SetPatchState(const std::string& patchName, bool enable) {
        for (auto& p : PatchesData::allPatches) {
            if (p.name == patchName) {
                if (p.isActive == enable) return; // Ya está en el estado deseado
                
                if (enable) {
                    if (p.cachedAddress == 0) {
                        Logger::Info("Scanning AOB for: " + patchName);
                        p.cachedAddress = mem->FindPattern(p.searchPattern, 0x10000000, 0x50000000); // Rango de ejemplo
                    }
                    if (p.cachedAddress != 0) {
                        auto replaceBytes = SignatureToBytes(p.replacePattern);
                        if(mem->WriteBytes(p.cachedAddress, replaceBytes)) {
                            p.isActive = true;
                            Logger::Info("Patcher " + patchName + " Enabled at 0x" + std::to_string(p.cachedAddress));
                        }
                    } else {
                        Logger::Error("Failed to find pattern for " + patchName);
                    }
                } else {
                    // Restauración (escribimos el patrón original de búsqueda de vuelta)
                    if (p.cachedAddress != 0) {
                        auto origBytes = SignatureToBytes(p.searchPattern);
                        if(mem->WriteBytes(p.cachedAddress, origBytes)) {
                            p.isActive = false;
                            Logger::Info("Patcher " + patchName + " Disabled");
                        }
                    }
                }
                break;
            }
        }
    }
};
