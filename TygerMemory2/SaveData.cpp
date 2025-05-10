#include "pch.h"
#include "savedata.h"
#include "core.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) { // Initialize only if Data hasn't been set
        uintptr_t address = Core::moduleBase + 0x4EB580;
        Data = new SaveDataStruct();
        Data->percentComplete = *(unsigned char*)((char*)address + 0x0);
        Data->playtime = *(float*)((char*)address + 0x4);
        Data->Opals = *(int*)((char*)address + 0x8);
        
    }
    return Data;
}