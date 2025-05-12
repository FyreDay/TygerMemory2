#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"

struct ObjectHeaderStruct {
	int unk;
	int unk2;
	uintptr_t objectType;
};

struct MKObjectStruct {
	uintptr_t vtable;
	int unk;
	ObjectHeaderStruct* ObjectHeader;
};

class TYGERMEM2 MKObject {
public:
	static uintptr_t GetMKObject(int id);
};