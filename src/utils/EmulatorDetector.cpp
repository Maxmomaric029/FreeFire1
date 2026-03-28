#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Función genérica para chequear si un archivo o directorio existe
bool CheckFileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

// Emular la lectura de una propiedad del sistema de Android (como getprop)
// En Android real esto usaría <sys/system_properties.h> y __system_property_get
std::string MockGetSystemProperty(const std::string& prop) {
    // Simulación: Si se corre en un emulador común, podría devolver estos valores
    if (prop == "ro.hardware") return "vbox86";
    if (prop == "ro.build.flavor") return "vbox86p-user";
    if (prop == "ro.product.board") return "unknown";
    return "normal_device_value";
}

bool DetectEmulator() {
    bool isEmulator = false;

    // 1. Artefactos de archivos: Buscar controladores o archivos típicos de emuladores
    std::vector<std::string> knownEmulatorFiles = {
        "/dev/socket/qemud",               // QEMU/Memu/Android Studio
        "/dev/qemu_pipe",                  // Interfaz QEMU
        "/system/lib/libc_malloc_debug_qemu.so",
        "/sys/qemu_trace",
        "/system/bin/nox-prop",            // Archivo de NOX Player
        "/system/bin/microvirt-prop"       // Archivo de MEmu
    };

    for (const auto& file : knownEmulatorFiles) {
        if (CheckFileExists(file)) {
            std::cout << "[! ALERTA] Artefacto de emulador detectado: " << file << std::endl;
            isEmulator = true;
        }
    }

    // 2. Propiedades del sistema: Revisar propiedades predeterminadas del hardware
    std::string hardware = MockGetSystemProperty("ro.hardware");
    if (hardware == "vbox86" || hardware == "nox" || hardware == "ttVM_x86") {
        std::cout << "[! ALERTA] Propiedad de hardware sospechosa: " << hardware << std::endl;
        isEmulator = true;
    }

    std::string board = MockGetSystemProperty("ro.product.board");
    if (board == "unknown" || board == "goldfish") {
        std::cout << "[! ALERTA] Propiedad de placa sospechosa: " << board << std::endl;
        isEmulator = true;
    }

    return isEmulator;
}

// Nota: se puede llamar a DetectEmulator() desde main.cpp o donde sea necesario
// para ejecutar la comprobación de seguridad abstacta.
