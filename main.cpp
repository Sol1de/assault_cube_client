#include <iostream>
#include "process_finder/ProcessFinder.h"
#include "memory_handler/MemoryHandler.h"
#include "Offsets.h"

int main() {
    // Processus cible
    const char* targetProcess = "ac_client.exe";

    std::cout << "[*] Recherche de " << targetProcess << "..." <<std::endl;

    // Récupère le PID (identifiant unique du processus)
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

    // Récupère l'adresse de base du module (où le jeu est chargé en mémoire)
    uint32_t moduleBase = GetModuleBaseAddress(processId, targetProcess);

    if (moduleBase == 0) {
        std::cout << "[!] Module non trouve\n";
        return 1;
    }
    std::cout << "[+] Module base: 0x" << std::hex << moduleBase << std::dec << "\n";

    // Lit le pointeur vers localPlayer (le jeu stocke l'adresse du joueur ici)
    auto localPlayer = ReadMemory<uint32_t>(processHandle, moduleBase + Offsets::localPlayer);

    if (localPlayer == 0) {
        std::cout << "[!] localPlayer est NULL - es-tu en jeu ?" << std::endl;
        return 1;
    }

    // Lit la vie à partir de l'adresse du joueur + offset health
    auto localPlayerHealth = ReadMemory<int>(processHandle, localPlayer + Offsets::health);

    std::cout << "[*] Local player health: " << localPlayerHealth << std::endl;

    // Libère le handle (évite les fuites de ressources)
    CloseHandle(processHandle);
    return 0;
}