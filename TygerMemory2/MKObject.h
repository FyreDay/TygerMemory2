#pragma once
#ifdef TYGERMEM_EXPORTS2
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"

struct MKObjectStruct {
	uintptr_t vtable;
	int unk;
	ObjectHeaderStruct* ObjectHeader;
};

struct ObjectHeaderStruct {
	int unk;
	int unk2;
	uintptr_t objectType;
};

class TYGERMEM2 MKObject {
public:
	static uintptr_t GetMKObject(int id);
};