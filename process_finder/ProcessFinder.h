#pragma once
#include <windows.h>

DWORD GetProcessId(const char* processName);
uintptr_t GetModuleBaseAddress(DWORD processId, const char* moduleName);