#pragma region Includes
#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "memory.h"
#include "Setting.h"

#include "KeyAuth/skStr.h"
#include "KeyAuth/auth.hpp"
#include "KeyAuth/utils.hpp"
#pragma endregion

#pragma region KeyAuth
using namespace KeyAuth;

std::string name = skCrypt("").decrypt();
std::string ownerid = skCrypt("").decrypt();
std::string secret = skCrypt("").decrypt();
std::string version = skCrypt("").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, version, url, path);
#pragma endregion

#pragma region randomTitle
static const char rnum[] = "0123456789" "qwertyuiopasdfghjklzxcvbnm" "QWERTYUIOPASDFGHJKLZXCVBNM";
int staticLength = sizeof(rnum) - 1;
std::string RandomTitle;

char GetRandom() {
    return rnum[rand() % staticLength];
}
void SetRandomTitle() {
    RandomTitle.clear();
    for (unsigned int i = 0; i < 1; ++i) {
        RandomTitle += GetRandom();
    }
    SetConsoleTitle(RandomTitle.c_str());

}
void SetRandomTitleThread() {
    while (true) {
        SetRandomTitle();
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }
}
#pragma endregion

#pragma region Blur
typedef enum WINDOWCOMPOSITIONATTRIB {
    WCA_UNDEFINED,
    WCA_NCRENDERING_ENABLED,
    WCA_NCRENDERING_POLICY,
    WCA_TRANSITIONS_FORCEDISABLED,
    WCA_ALLOW_NCPAINT,
    WCA_CAPTION_BUTTON_BOUNDS,
    WCA_NONCLIENT_RTL_LAYOUT,
    WCA_FORCE_ICONIC_REPRESENTATION,
    WCA_EXTENDED_FRAME_BOUNDS,
    WCA_HAS_ICONIC_BITMAP,
    WCA_THEME_ATTRIBUTES,
    WCA_NCRENDERING_EXILED,
    WCA_NCADORNMENTINFO,
    WCA_EXCLUDED_FROM_LIVEPREVIEW,
    WCA_VIDEO_OVERLAY_ACTIVE,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE,
    WCA_DISALLOW_PEEK,
    WCA_CLOAK,
    WCA_CLOAKED,
    WCA_ACCENT_POLICY,
    WCA_FREEZE_REPRESENTATION,
    WCA_EVER_UNCLOAKED,
    WCA_VISUAL_OWNER,
    WCA_LAST,
} WINDOWCOMPOSITIONATTRIB;
typedef struct WINDOWCOMPOSITIONATTRIBDATA {
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;
typedef enum ACCENT_STATE {
    ACCENT_DISABLED,
    ACCENT_ENABLE_GRADIENT,
    ACCENT_ENABLE_TRANSPARENTGRADIENT,
    ACCENT_ENABLE_BLURBEHIND,
    ACCENT_INVALID_STATE
} ACCENT_STATE;
typedef struct ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;
typedef BOOL(WINAPI* pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
static auto SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(LoadLibrary("user32.dll"), "SetWindowCompositionAttribute");
#pragma endregion

#pragma region ASCII
void SetConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void AsciiName() {
    std::cout << skCrypt(R"(
           __ _                   _                         
          / _(_)                 | |                        
         | |_ _ _ __  _ __   __ _| |_   _ _ __   ___  _ __  
         |  _| | '_ \| '_ \ / _` | | | | | '_ \ / _ \| '_ \ 
         | | | | | | | | | | (_| | | |_| | | | | (_) | |_) |
         |_| |_|_| |_|_| |_|\__,_|_|\__, |_| |_|\___/| .__/ 
                                     __/ |           | |    
                                    |___/            |_|                                                                                                             
    )") << std::endl;

    // Blue line
    SetConsoleColor(8);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~https://github.com/finnalynop~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
    SetConsoleColor(7); // Reset to default color
}
#pragma endregion

#pragma region Auth
bool AuthenticateUser() {
    AsciiName();
    std::string key;
    std::cout << skCrypt("[ AUTH ] Enter license: ");
    std::cin >> key;

    KeyAuthApp.init();

    KeyAuthApp.license(key);

    if (KeyAuthApp.response.success) {
        std::cout << skCrypt("[ AUTH ] Authorization successful.\n");
        Sleep(400);
        return true;
    }
    else {
        std::cerr << skCrypt("[ AUTH ] Invalid key or access has expired.\n");
        Sleep(1000);
        return false;
    }
}
#pragma endregion

#pragma region Menu
void cheatMenu() {
    AsciiName();
    std::cout << skCrypt("\n[ F ] WallHack") << std::endl;
    std::cout << skCrypt("\n[ Z ] Chams") << std::endl;
    std::cout << skCrypt("\n[ X ] WallHack v2") << std::endl;
    std::cout << skCrypt("\n[ C ] Delete Effects on screen") << std::endl;
}
#pragma endregion


int main()
{
    HWND hWnd = GetConsoleWindow();
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

    if (SetWindowCompositionAttribute) {
        ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
        WINDOWCOMPOSITIONATTRIBDATA data;
        data.Attrib = WCA_ACCENT_POLICY;
        data.pvData = &accent;
        data.cbData = sizeof(accent);
        SetWindowCompositionAttribute(hWnd, &data);
    }

    // Remove scroll bar
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStd, &csbi);
    COORD scrollbar = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
    SetConsoleScreenBufferSize(hStd, scrollbar);

    std::thread titleThread(SetRandomTitleThread);
    titleThread.detach();
    if (!AuthenticateUser()) {
        std::cout << skCrypt("[ DEBUG ] Login ERROR") << std::endl;
        Sleep(1000);
        return 0;
    }

    DWORD pid = pidder::get_process_id("stalcraft.exe");
    if (!pid) {
        std::cout << skCrypt("[ INFO ] Trying to find game..\n");
        do {
            pid = pidder::get_process_id("stalcraft.exe");
            Sleep(200UL);
        } while (!pid);
    }

    Memory memory;
    memory.processId = pid;
    memory.processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (!memory.processHandle) {
        std::cerr << skCrypt("\n\t[ ERROR ] Failed to open process with sufficient privileges!") << std::endl;
        return -1;
    }

    std::uintptr_t baseAddress = memory.GetModuleAddress("nvoglv64.dll");
    
    const std::string spinner = "|/-\\";
    int attempt = 0;

    do {
        uintptr_t baseAddress = memory.GetModuleAddress("nvoglv64.dll");
        bool baseAddressFound = (baseAddress != 0);
        ++attempt;
        std::cout << "\r" << "[ INFO ] Loading [" << spinner[attempt % spinner.length()] << "]";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (baseAddressFound) break;
    } while (true);

    //Offsets
    std::uintptr_t wallhackAddress = baseAddress + 0x7B4C0C;//updated
    std::uintptr_t chamsAddress = baseAddress + 0x7B451C; //updated

    system("cls");
    cheatMenu();
    while (true)
    {
        if (GetAsyncKeyState(0x5A) & 0x8000) //F
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to revert. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallHackInstruction, sizeof(newWallHackInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallHackInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabled = !wallhackEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x58) & 0x8000) //Z
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (chamsEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to revert. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, newChamsInstruction, sizeof(newChamsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newChamsInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            chamsEnabled = !chamsEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x58) & 0x8000) //X
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabledv2)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to revert. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallhackInstructionv2, sizeof(newWallhackInstructionv2), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallhackInstructionv2))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabledv2 = !wallhackEnabledv2;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x43) & 0x8000) //C
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (deleteEffects)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to revert. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, deleteEffectsInstruction, sizeof(deleteEffectsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(deleteEffectsInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            deleteEffects = !deleteEffects;
        }
    }

    return 0;
}
