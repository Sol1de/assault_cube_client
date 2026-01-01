#pragma once
#include <cstdint>

namespace Offsets {
    constexpr uintptr_t localPlayer = 0x0018AC00; // Offset du pointeur vers le joueur
    constexpr uintptr_t health = 0xEC; // Offset de la vie du joueur
}
