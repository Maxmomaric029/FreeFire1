#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include "../utils/Logger.h"

using json = nlohmann::json;

class Config {
public:
    static inline bool  aimbot_enable = false;
    static inline bool  head_safe     = false;
    static inline float fov           = 15.0f;
    static inline int   target_bone   = 0;
    static inline bool  wallhack      = false;
    static inline bool  no_recoil     = false;
    static inline bool  black_sky     = false;
    static inline bool  esp_box       = false;
    static inline bool  esp_lines     = false;

    static void Load(const std::string& path = "resources/config.json") {
        std::ifstream file(path);
        if (!file.is_open()) {
            Logger::Error("Could not open config file: " + path);
            return;
        }
        try {
            json j;
            file >> j;

            aimbot_enable = j.value("aimbot_enabled",   false);
            head_safe     = j.value("head_safe",         false);   // ← faltaba
            fov           = j.value("aimbot_fov",        15.0f);
            target_bone   = j.value("aimbot_bone",       0);
            wallhack      = j.value("wallhack_enabled",  false);
            no_recoil     = j.value("no_recoil_enabled", false);
            black_sky     = j.value("black_sky_enabled", false);   // ← faltaba
            esp_box       = j.value("esp_box_enabled",   true);
            esp_lines     = j.value("esp_lines_enabled", false);   // ← faltaba

            Logger::Info("Configuration loaded successfully");
        } catch (const std::exception& e) {                        // ← typo corregido
            Logger::Error("Error parsing config: " + std::string(e.what()));
        }
    }

    static void Save(const std::string& path = "resources/config.json") {
        json j;
        j["aimbot_enabled"]    = aimbot_enable;
        j["head_safe"]         = head_safe;
        j["aimbot_fov"]        = fov;
        j["aimbot_bone"]       = target_bone;
        j["wallhack_enabled"]  = wallhack;
        j["no_recoil_enabled"] = no_recoil;
        j["black_sky_enabled"] = black_sky;
        j["esp_box_enabled"]   = esp_box;
        j["esp_lines_enabled"] = esp_lines;

        std::ofstream file(path);
        if (file.is_open()) {
            file << j.dump(4);
            Logger::Info("Configuration saved");
        } else {
            Logger::Error("Could not write config file: " + path);
        }
    }
};
