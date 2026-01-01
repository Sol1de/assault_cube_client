#pragma once
#include <windows.h>

// Fonction générique (change en fonction du type int, float, etc...)
template <class Type>
Type ReadMemory(HANDLE processHandle, uintptr_t address) {
    // Initialisation + clean de l'espace mémoire alloué à value (evite garbage values)
    Type value{};

    // On copie/colle la valeur souhaité depuis address dans value
    ReadProcessMemory(processHandle,  (LPCVOID)address, &value, sizeof(Type), nullptr);
    return value;
}

template <class Type>
bool WriteMemory(HANDLE processHandle, uintptr_t address, Type value) {
    // On ecrit la valeur souhaité depuis value dans address
    return WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(Type), nullptr);
}