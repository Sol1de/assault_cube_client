#pragma once
#include <windows.h>

// Fonction générique (change en fonction du type int, float, etc...)
template <class Type>
Type ReadMemory(HANDLE processHandle, uintptr_t adress) {
    // Initialisation + clean de l'espace mémoire alloué à value (evite garbage values)
    Type value{};

    // On copie/colle la valeur souhaité depuis adress dans value
    ReadProcessMemory(processHandle, (LPCVOID)adress, &value, sizeof(Type), nullptr);
    return value;
}