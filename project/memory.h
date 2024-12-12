#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <string_view>

namespace pidder {
    DWORD get_process_id(const CHAR* name) noexcept {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0UL);
        if (ss == INVALID_HANDLE_VALUE) {
            return 0;
        }

        DWORD pid = 0;

        do {
            if (!strcmp(name, pe.szExeFile)) {
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(ss, &pe));

        CloseHandle(ss);
        return pid;
    }
}

class Memory {
public:
    std::uintptr_t processId = 0;        
    void* processHandle = nullptr;

    ~Memory() {
        if (processHandle) {
            CloseHandle(processHandle);
        }
    }

    std::uintptr_t GetModuleAddress(const std::string_view moduleName) const noexcept {
        MODULEENTRY32 entry = { };
        entry.dwSize = sizeof(MODULEENTRY32);

        HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
        if (snapShot == INVALID_HANDLE_VALUE) {
            return 0; 
        }

        std::uintptr_t result = 0;

        if (Module32First(snapShot, &entry)) {
            do {
                if (!moduleName.compare(entry.szModule)) {
                    result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
                    break;
                }
            } while (Module32Next(snapShot, &entry));
        }

        CloseHandle(snapShot);
        return result;
    }

    template <typename T>
    T Read(const std::uintptr_t& address) const noexcept {
        T value = { };
        ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), nullptr);
        return value;
    }

    template <typename T>
    void Write(const std::uintptr_t& address, const T& value) const noexcept {
        WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), nullptr);
    }
};
