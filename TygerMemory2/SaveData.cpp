
#include "savedata.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) { // Initialize only if Data hasn't been set
        uintptr_t address = Core::moduleBase + 0x4EB580;
        Data = reinterpret_cast<SaveDataStruct*>(reinterpret_cast<int*>(address));
    }
    return Data;
}


LinkedList<MissionStruct> SaveData::MissionList(int missionState) {
    if (missionState > 6 || missionState < 0) {
        throw std::out_of_range("Index " + std::to_string(missionState) + " is out of bounds (lower bound = 0, upperbound = 6)");
    }
    uintptr_t listBase = Core::moduleBase + 0x4EB580+0x14c + (missionState * 0x10);
    LinkedList<MissionStruct> missionList(
        (int*)listBase,
        *(uintptr_t*)(listBase + 0x08), // offset to head ptr
        *(uintptr_t*)(listBase + 0x04), // offset to tail ptr
        0x28, // offset to prev in each MissionStruct
        0x24  // offset to next in each MissionStruct
    );
    return missionList;
}


std::optional<MissionStruct> SaveData::findMissionByID(int missionId) {
    for (int i = 0; i < 7; i++) {
        LinkedList<MissionStruct> list = SaveData::MissionList(i);
        std::optional<MissionStruct> mission = SaveData::findMissionByID(list, missionId);
        if (mission.has_value()) {
            return mission;
        }
    }
    return std::nullopt;
}

std::optional<MissionStruct> SaveData::findMissionByID(const LinkedList<MissionStruct>& list, int targetID)
{
    for (auto node = list.getHead(); node.isValid(); node = node.getNext()) {
        MissionStruct mission = node.getData();
        if (mission.getRawID() == targetID) {
            return mission;
        }
    }
    return std::nullopt;
}

LinkedList<ItemStruct> SaveData::GetShopItemList(int shopId)
{
    ShopStruct* shop = reinterpret_cast<ShopStruct*>(SaveData::GetData()->FirstShop + (shopId - 1));

    LinkedList<ItemStruct> itemList(
        (int*)&(shop->numItems),
        (uintptr_t)(shop->firstItem), // offset to head ptr
        (uintptr_t)(shop->lastItem),
        0x28, // offset to prev in each ItemStruct
        0x24  // offset to next in each ItemStruct
    );
    return itemList;
}

std::optional<ItemStruct> SaveData::findItemByID(const LinkedList<ItemStruct>& list, int targetID)
{
    for (auto node = list.getHead(); node.isValid(); node = node.getNext()) {
        ItemStruct item = node.getData();
        if (item.itemId == targetID) {
            return item;
        }
    }
    return std::nullopt;
}
//36dca0 may contain code to load chuncks.