#include "EmulatorDetector.h"
#include <windows.h>
#include <TlHelp32.h>
#include <algorithm>

EmulatorDetector::EmulatorDetector() {
    knownEmulators = {
        {"BlueStacks", "HD-Player.exe", ""},
        {"LDPlayer", "dnplayer.exe", "LdBoxHeadless.exe"},
        {"SmartGaGa", "ProjectTitan.exe", ""},
        {"GameLoop", "aow_exe.exe", ""}
    };
}

std::string EmulatorDetector::DetectRunningEmulator() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE) return "";

    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    if (Process32FirstW(snapshot, &entry) == TRUE) {
        do {
            std::wstring wExeName = entry.szExeFile;
            std::string exeName(wExeName.length(), 0);
            std::transform(wExeName.begin(), wExeName.end(), exeName.begin(), [](wchar_t c) { return (char)c; });

            for (const auto& emu : knownEmulators) {
                // Comparamos el binario principal o su proceso auxiliar "headless"
                if (_stricmp(exeName.c_str(), emu.processName.c_str()) == 0 || 
                    (!emu.auxiliaryProcess.empty() && _stricmp(exeName.c_str(), emu.auxiliaryProcess.c_str()) == 0)) {
                    CloseHandle(snapshot);
                    
                    // Si encontramos LdBoxHeadless, la clase Memory usará dnplayer.exe o viceversa.
                    // Generalmente, a Memoria le damos al motor pesado: LdBoxHeadless o HD-Player.
                    return exeName; // Retornamos el ejecutable detectado (v.g. "HD-Player.exe")
                }
            }
        } while (Process32NextW(snapshot, &entry) == TRUE);
    }
    
    CloseHandle(snapshot);
    return "";
}

std::string EmulatorDetector::GetDetectedEmulatorName() const {
    // Si queremos el nombre amigable (e.g. "BlueStacks" en vez del .exe)
    // omitimos la lógica repetida, esto es sólo un esqueleto robusto.
    return "";
}
