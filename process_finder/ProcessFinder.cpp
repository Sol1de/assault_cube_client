#include "ProcessFinder.h"
#include <iostream>
#include <TlHelp32.h>

DWORD GetProcessId(const char* processName) {
    DWORD pid = 0; // unsigned integer (always > 0)

    // Snapshot (etat a un instant T) de tous les processus
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    // On renvoi une erreur si le snapshot renvoyé est invalide
    if (snapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    // Structure qui va contenir les infos de chaque processus
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

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
