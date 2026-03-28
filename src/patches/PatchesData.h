#pragma once
#include <string>
#include <vector>

struct Patch {
    std::string name;
    std::string searchPattern;
    std::string replacePattern;
    uintptr_t cachedAddress = 0;
    bool isActive = false;
};

namespace PatchesData {
    inline std::vector<Patch> allPatches = {
        {
            "Wallhack",
            "3F AE 47 81 3F AE 47 81 3F AE 47 81 3F 00 1A B7 EE DC 3A 9F ED 30", // Simplificado para lectura
            "3F AE 47 81 3F AE 47 81 BF AE 47 81 3F AE 1A B7 EE DC 3A 9F ED 30"
        },
        {
            "No Recoil",
            "01 EE 00 0A 81 EE 10 0A 10 EE 10 8C BD E8 00 00 7A 44 F0 48 2D E9 10 B0 8D E2 02 8B 2D ED 08 D0 4D E2 00 50 A0 E1",
            "01 EE 00 0A 81 EE 10 0A 10 EE 10 8C BD E8 00 00 7A FF F0 48 2D E9 10 B0 8D E2 02 8B 2D ED 08 D0 4D E2 00 50 A0 E1"
        },
        {
            "Fast Reload",
            "30 48 2D E9 08 B0 8D E2 00 40 A0 E1 77 08 02 E3 00 10 A0 E3 76 C3 46 EB 01 00 50 E3",
            "30 48 2D E9 08 B0 8D E2 00 40 A0 E1 77 08 02 E3 00 10 A0 E3 00 C3 46 EB 01 00 50 E3"
        },
        {
            "Black Sky",
            "A4 70 7D 3F 3A CD 13 3F 0A D7 23 3C BD 37 86 35",
            "A4 70 7D 3F 3A CD 13 3F 0A D7 23 3C 00 00 80 BF"
        }
    };
}
