#include <iostream>
#include "process_finder/ProcessFinder.h"

int main() {
    const char* targetProcess = "ac_client.exe";

    std::cout << "[*] Recherche de " << targetProcess << "..." <<std::endl;

    const DWORD processId = GetProcessId(targetProcess);

    if (processId == 0) {
        std::cout << "[!] Processus non trouve" << std::endl;
        return 1;
    } else {
        std::cout << "[*] Processus trouve: " << processId << std::endl;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    if (processHandle != NULL) {
        std::cout << "[*] Handle obtenu avec succes!" << std::endl;
    } else {
        std::cout << "[!] Impossible d'obtenir le handle" << std::endl;
        return 1;
    }

    return 0;
}