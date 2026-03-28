#pragma once
#include <windows.h>
#include <map>
#include <functional>

namespace Hotkeys {
    inline std::map<int, std::function<void()>> keyCallbacks;
    inline bool IsKeyToggled(int vKey) {
        return (GetAsyncKeyState(vKey) & 1) != 0;
    }

    inline void RegisterHotkey(int vKey, std::function<void()> callback) {
        keyCallbacks[vKey] = callback;
    }

    inline void Poll() {
        for(auto& pair : keyCallbacks) {
            if(IsKeyToggled(pair.first)) {
                pair.second();
            }
        }
    }
}
