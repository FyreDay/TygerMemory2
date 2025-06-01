
#include "savedata.h"

SaveDataStruct* SaveData::Data = nullptr;

SaveDataStruct* SaveData::GetData() {
    if (!Data) { // Initialize only if Data hasn't been set
        uintptr_t address = Core::moduleBase + 0x4EB580;
        Data = reinterpret_cast<SaveDataStruct*>(reinterpret_cast<int*>(address));
    }
    return Data;
}

/**
 * @brief Returns the list of missions with a specific state
 * @param missionState is the state for the mission fom 0-6 inclusive.
 * 0 is unavailable. 1 is available but not shown. 2 is available and shown. 3 is active. 4 is able to turn in, 5 is done. 6 is something wierd.
 * @return The Linked list of missions.
 */
LinkedList<MissionWrapper> SaveData::MissionList(int missionState) {
    if (missionState > 6 || missionState < 0) {
        throw std::out_of_range("Index " + std::to_string(missionState) + " is out of bounds (lower bound = 0, upperbound = 6)");
    }
    uintptr_t listBase = Core::moduleBase + 0x4EB580+0x14c + (missionState * 0x10);
    LinkedList<MissionWrapper> missionList(
        listBase,
        0x00, // offset to length in list struct
        0x04, // offset to head ptr
        0x08, // offset to tail ptr
        0x24, // offset to prev in each MissionStruct
        0x28  // offset to next in each MissionStruct
    );
    return missionList;
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
//36dca0 may contain code to load chuncks.