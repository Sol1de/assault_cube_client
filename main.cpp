#include <iostream>
#include "process_finder/ProcessFinder.h"
#include "memory_reader/MemoryReader.h"

int main() {
    // Processus cible
    const char* targetProcess = "ac_client.exe";

    std::cout << "[*] Recherche de " << targetProcess << "..." <<std::endl;

    // On stock l'id du processus cible
    const DWORD processId = GetProcessId(targetProcess);

    if (processId == 0) {
        std::cout << "[!] Processus non trouve" << std::endl;
        return 1;
    }
    std::cout << "[*] Processus trouve: " << processId << std::endl;

    // On ouvre un accès total (handle) au processus cible pour lire/écrire dans sa mémoire
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    if (processHandle == NULL) {
        std::cout << "[!] Impossible d'obtenir le handle" << std::endl;
        return 1;
    }

    std::cout << "[*] Handle obtenu avec succes!" << std::endl;

    const uintptr_t healthAddress = 0x009F2B8C;
    int health = ReadMemory<int>(processHandle, healthAddress);

    std::cout << "[*] Health: " << health << std::endl;

    return 0;
}