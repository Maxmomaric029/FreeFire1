#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <sstream>
#include "../utils/Logger.h"

class Memory {
private:
    DWORD processId = 0;
    HANDLE hProcess = nullptr;

    // Utilidad: Convierte un signature style "AA BB ?? CC" a un vector de bytes y una máscara "xx?x"
    bool ParseSignature(const std::string& signature, std::vector<uint8_t>& pattern, std::string& mask) const {
        std::istringstream stream(signature);
        std::string word;
        while (stream >> word) {
            if (word == "??" || word == "?") {
                pattern.push_back(0);
                mask += '?';
            } else {
                pattern.push_back((uint8_t)strtoul(word.c_str(), nullptr, 16));
                mask += 'x';
            }
        }
        return !pattern.empty();
    }

public:
    Memory() {}
    Memory(const wchar_t* processName) { Attach(processName); }

    ~Memory() { if (hProcess) CloseHandle(hProcess); }

    bool Attach(const wchar_t* processName) {
        PROCESSENTRY32W entry;
        entry.dwSize = sizeof(PROCESSENTRY32W);
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32FirstW(snapshot, &entry) == TRUE) {
            while (Process32NextW(snapshot, &entry) == TRUE) {
                if (wcscmp(entry.szExeFile, processName) == 0) {
                    processId = entry.th32ProcessID;
                    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
                    Logger::Info("Attached to process: " + std::to_string(processId));
                    break;
                }
            }
        }
        CloseHandle(snapshot);
        return IsValid();
    }

    bool IsValid() const { return hProcess != nullptr; }

    template<typename T>
    T Read(uintptr_t address) const {
        T value{};
        if (hProcess)
            ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    template<typename T>
    bool Write(uintptr_t address, const T& value) const {
        if (!hProcess) return false;
        return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), NULL);
    }

    bool WriteBytes(uintptr_t address, const std::vector<uint8_t>& bytes) const {
        if (!hProcess) return false;
        DWORD oldProtect;
        VirtualProtectEx(hProcess, (LPVOID)address, bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
        bool result = WriteProcessMemory(hProcess, (LPVOID)address, bytes.data(), bytes.size(), NULL);
        VirtualProtectEx(hProcess, (LPVOID)address, bytes.size(), oldProtect, &oldProtect);
        return result;
    }

    // Escaner AOB
    uintptr_t FindPattern(const std::string& signature, uintptr_t startAddress = 0, size_t searchSize = 0x7FFFFFFF) const {
        if (!IsValid()) return 0;
        
        std::vector<uint8_t> pattern;
        std::string mask;
        if (!ParseSignature(signature, pattern, mask)) return 0;

        const size_t bufferSize = 4096 * 10;
        std::vector<uint8_t> buffer(bufferSize);
        SIZE_T bytesRead = 0;
        
        // Buscamos utilizando memoria paginada para ser ágiles
        for (uintptr_t i = startAddress; i < startAddress + searchSize; i += bufferSize - pattern.size()) {
            if (ReadProcessMemory(hProcess, (LPCVOID)i, buffer.data(), bufferSize, &bytesRead)) {
                for (size_t b = 0; b < bytesRead - pattern.size(); ++b) {
                    bool match = true;
                    for (size_t p = 0; p < pattern.size(); ++p) {
                        if (mask[p] == 'x' && buffer[b + p] != pattern[p]) {
                            match = false;
                            break;
                        }
                    }
                    if (match) return i + b;
                }
            }
        }
        return 0;
    }
};
