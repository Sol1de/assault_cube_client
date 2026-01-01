#include "ProcessFinder.h"
#include <iostream>
#include <TlHelp32.h>

DWORD GetProcessId(const char* processName) {
    DWORD pid = 0; // unsigned integer (always > 0)

    // Renvoi une liste des processus en cours sur le systeme a un instant T
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    // Structure pour stocker les infos de chaque processus
    PROCESSENTRY32 entry;

    // Indique à Windows la taille de structure attendue
    entry.dwSize = sizeof(PROCESSENTRY32);

    // Parcourt tous les process jusqu'à trouver le bon
    if (Process32First(snapshot, &entry)) {
        do {
            if (strcmp(entry.szExeFile, processName) == 0) {
                pid = entry.th32ProcessID;
                break;
            }

        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);

    return pid;
}

uintptr_t GetModuleBaseAddress(DWORD processId, const char *moduleName) {
    uintptr_t baseAddress = 0; // unsigned integer (always > 0)

    // Renvoi une liste des modules (EXE et DLL) du jeu pour trouver leur adresse de départ en mémoire
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    // Structure pour stocker les infos de chaque module
    MODULEENTRY32 entry;

    // Indique à Windows la taille de structure attendue
    entry.dwSize = sizeof(MODULEENTRY32);

    // Parcourt tous les modules jusqu'à trouver le bon
    if (Module32First(snapshot, &entry)) {
        do {
            if (strcmp(entry.szModule, moduleName) == 0) {
                baseAddress = (uintptr_t)entry.modBaseAddr;
                break;
            }
        } while (Module32Next(snapshot, &entry));
    }

    // Libère le handle (évite les fuites de ressources)
    CloseHandle(snapshot);
    return baseAddress;
}
