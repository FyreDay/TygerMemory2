#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"


/**
* VTable notes
* +0x8 handles the occilation
*/
struct UIElementStruct {
	uintptr_t vtable;
	char* TypeName;
	uintptr_t anotherVtable;
	UIElementStruct* parentUiElement;

	UIElementStruct* nextUiElementInList;
	bool drawn;
	bool enabled;
	bool currentlySelected;
	bool interactable;
	float Blue;
	float Red;

	float Green;
	float Alpha;
	char unk28[8];

	char unk30[4];
	float unk34;
	char unk38[8];

	char unk40[8];
	float size;
	char unk4c[4];

	char unk50[8];
	int unk58;
	UIElementStruct* firstChildUiElement;
	int numChildElements;
};

class TYGERMEM2 MKUI {
	
public:
	static uintptr_t GetBaseUI();
	static UIElementStruct* GetMainMenu();
	static UIElementStruct* FindChildElementByName(UIElementStruct* parent,const char* childname);
private:
	static inline int BaseUIOffset = 0x4EDD4C;
};