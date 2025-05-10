#include "pch.h"
#include "core.h"
#include <iostream>
#include <psapi.h>
#include <windows.h>
#include <tchar.h>
#include "Logging.h"

DWORD Core::processId = 0;
HANDLE Core::hProcess = 0;
uintptr_t Core::moduleBase = 0;

bool Core::initialize(HMODULE hModule)
{
	Logging::del();
	Logging::log("TygerMemory Initializing...");
	moduleBase = (uintptr_t)hModule;
	if (moduleBase == 0) {
		Logging::log("Failed to load .exe module.");
		return false;
	}
	Logging::log("TygerMemory Initialized.");
	return true;
}

uintptr_t Core::getPointerAddress(uintptr_t baseAddr, const std::vector<int>& offsets)
{
	uintptr_t currentAddr = baseAddr;
	for (size_t i = 0; i < offsets.size(); i++) {
		uintptr_t* pointer = reinterpret_cast<uintptr_t*>(currentAddr);
		currentAddr = *pointer;
		if (currentAddr == 0)
			return 0;
		currentAddr += offsets[i];
	}
	return currentAddr;
}

void Core::SetReadOnlyValue(void* address, void* value, size_t size) {
	DWORD oldProtection;
	//Change the memory access to ReadWrite to be able to change the hardcoded value (usually its read only)
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtection);

	memcpy(address, value, size);

	//Set it back to the old access protection
	VirtualProtect(address, size, oldProtection, &oldProtection);
}