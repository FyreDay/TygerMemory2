
#include "savedata.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) { // Initialize only if Data hasn't been set
        uintptr_t address = Core::moduleBase + 0x4EB580;
        Data = reinterpret_cast<SaveDataStruct*>(reinterpret_cast<int*>(address));
    }
    return Data;
}


LinkedList<MissionWrapper> SaveData::MissionList(int missionState) {
    if (missionState > 6 || missionState < 0) {
        throw std::out_of_range("Index " + std::to_string(missionState) + " is out of bounds (lower bound = 0, upperbound = 6)");
    }
    uintptr_t listBase = Core::moduleBase + 0x4EB580+0x14c + (missionState * 0x10);
    LinkedList<MissionWrapper> missionList(
        (int*)listBase,
        (uintptr_t*)(listBase + 0x08), // offset to head ptr
        (uintptr_t*)(listBase + 0x04), // offset to tail ptr
        0x28, // offset to prev in each MissionStruct
        0x24  // offset to next in each MissionStruct
    );
    return missionList;
}


std::optional<MissionWrapper> SaveData::findMissionByID(int missionId) {
    for (int i = 0; i < 7; i++) {
        LinkedList<MissionWrapper> list = SaveData::MissionList(i);
        std::optional<MissionWrapper> mission = SaveData::findMissionByID(list, missionId);
        if (mission.has_value()) {
            return mission;
        }
    }
    return std::nullopt;
}

std::optional<MissionWrapper> SaveData::findMissionByID(const LinkedList<MissionWrapper>& list, int targetID)
{
    for (auto node = list.getHead(); node.isValid(); node = node.getNext()) {
        MissionWrapper mission = node.getData();
        if (mission.getID() == targetID) {
            return mission;
        }
    }
    return std::nullopt;
}

LinkedList<ItemWrapper> SaveData::ItemList(int shopId)
{
    uintptr_t listBase = *(uintptr_t*)(Core::moduleBase + 0x4EB580 + 0x1F4);

    uintptr_t head = 0;

    switch (shopId) {
        case 1:
            head = listBase;
            break;
        case 2:
            head = listBase + 0x190;
            break;
        case 3:
            head = listBase + 0x230;
            break;
        case 4:
            head = listBase + 0xa0;
            break;
        default:
            throw std::out_of_range("Index " + std::to_string(shopId) + " is out of bounds (lower bound = 1, upperbound = 4)");
    };
    

    uintptr_t shopBase = *(uintptr_t*)(Core::moduleBase + 0x4EB580 + 0x1FC);
    ShopStruct* shop = reinterpret_cast<ShopStruct*>(shopBase + ((shopId-1) * 0x40));

    LinkedList<ItemWrapper> itemList(
        (int*)&(shop->numItems),
        head, // offset to head ptr
        0x28, // offset to prev in each ItemStruct
        0x24  // offset to next in each ItemStruct
    );
    return itemList;
}

std::optional<ItemWrapper> SaveData::findItemByID(const LinkedList<ItemWrapper>& list, int targetID)
{
    for (auto node = list.getHead(); node.isValid(); node = node.getNext()) {
        ItemWrapper item = node.getData();
        if (item.getID() == targetID) {
            return item;
        }
    }
    return std::nullopt;
}
//36dca0 may contain code to load chuncks.