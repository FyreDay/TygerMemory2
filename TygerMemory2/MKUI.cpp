#include "MKUI.h"

uintptr_t MKUI::GetBaseUI()
{
	uintptr_t address = Core::moduleBase + BaseUIOffset;
    return address;
}

UIElementStruct* MKUI::GetMainMenu()
{
    uintptr_t uiManager = *(uintptr_t*)(GetBaseUI());

    // Add 0x4FC to get the main menu pointer
    UIElementStruct* mainMenu = *(UIElementStruct**)(uiManager + 0x4FC);

    return mainMenu;
}

UIElementStruct* MKUI::FindChildElementByName(UIElementStruct* parent,const char* childTypeName)
{
    if (parent == nullptr || childTypeName == nullptr || parent->firstChildUiElement == nullptr) {
        return nullptr;
    }
    UIElementStruct* currentChild = parent->firstChildUiElement;

    for (int i = 0; i < parent->numChildElements; ++i) {
        if (currentChild != nullptr && currentChild->TypeName != nullptr) {
            if (strcmp(currentChild->TypeName, childTypeName) == 0) {
                return currentChild;
            }
        }

        // Move to the next sibling
        currentChild = currentChild->nextUiElementInList;
    }

    // Not found
    return nullptr;
}

//2f3a00 is click handler

// __thiscall FUN_006f6240(undefined4 *param_1,char *param_2,undefined4 param_3)
