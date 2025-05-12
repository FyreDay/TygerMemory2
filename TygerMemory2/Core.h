#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include <vector>
#include <string>
#include <functional>
#define WIN32_LEAN_AND_MEAN 
#include "Logging.h"
#include <iostream>
#include <psapi.h>
#include <tchar.h>
#include "framework.h"


class TYGERMEM2 Core
{
private:
	static DWORD processId;
	static HANDLE hProcess;
public:
	static uintptr_t moduleBase;
	/// <summary>
	///		Initializes the API by passing it the exe module handle for address offsets.
	/// </summary>
	/// <param name="hModule:">
	///		<para>The exe module handle.</para>
	///		<para>For usage with TygerFramework, use:</para>
	///		<c>Core::initialize((HMODULE)API::Get()->param()->TyHModule)</c>
	/// </param>
	/// <returns>
	///		<para>True if successfully initialized.</para>
	///		<para>This should be checked before using the API to avoid access violations.</para>
	/// </returns>
	static bool initialize(HMODULE hModule);
	/// <summary>
	///		Gets the address pointed to by a given path.
	/// </summary>
	/// <param name="baseAddress:">
	///		<para>The base address for the path.</para> 
	///		<para>This is assumed relative to the module base.</para>
	/// </param>
	/// <param name="offsets:">
	///		<para>A vector (list) of the integer offsets in the path.</para>
	/// </param>
	/// <returns>
	///		<para>The address pointed to by the path provided.</para>
	/// </returns>
	static uintptr_t getPointerAddress(uintptr_t baseAddress, const std::vector<int>& offsets);

	/// <summary>
	/// Writes a value to any read only memory with the length of the specified
	/// </summary>
	/// <param name="address:">The destination address to write to</param>
	/// <param name="value:">The value to write</param>
	/// <param name="size:">The size in bytes of the value</param>
	static void SetReadOnlyValue(void* address, void* value, size_t size);
};