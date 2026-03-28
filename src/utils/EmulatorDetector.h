#pragma once
#include <string>
#include <vector>

struct EmulatorInfo {
    std::string name;
    std::string processName;
    std::string auxiliaryProcess; // sometimes HD-Player.exe uses another process for input
};

class EmulatorDetector {
private:
    std::vector<EmulatorInfo> knownEmulators;

public:
    EmulatorDetector();

    // Devuelve el nombre del proceso detectado, vacío si no se encuentra
    std::string DetectRunningEmulator();
    std::string GetDetectedEmulatorName() const;
};
