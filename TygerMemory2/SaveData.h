#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"
#include "MemoryLinkedList.h"
#include <optional>

struct ShopStruct {
	uintptr_t maybeINIstrings;
	int shopId;
	int titleId;
	int descId;
	bool flag;
	char boolAlignmentPadding[0x3];
	char Padding[0x20];
	int numItems;
	uintptr_t somethingwithmissions1;
	uintptr_t somethingwithmissions2;
};


struct ItemStruct {
	uintptr_t maybeINIstrings;
	int itemId;
	int titleId;
	int descId;

	bool purchased;
	char boolAlignmentPadding[0x3];
	int type;
	char Padding[0x8];

	char Padding[0x4];
	uintptr_t nextItem;
	uintptr_t previousItem;
	uintptr_t maybeRelatedMissionList;

	uintptr_t startofMissionData;
	uintptr_t targetString;
	uintptr_t TDAIconString;
	int Price;

	int ShopId;
	int subtype;
	int currencyType;
	uintptr_t ShopIconNameString;
};

class ItemWrapper {
public:
	uintptr_t address;
	ItemWrapper(uintptr_t addr) : address(addr) {}

	int getRawID() const {
		return *(int*)(address + 0x04);
	}

	short getID() const {
		return *(short*)(address + 0x04);
	}

	char getIDType() const {
		return *(char*)(address + 0x07);
	}

	int getTitleId() const {
		return *(int*)(address + 0x08); // titleId offset
	}
	int getDescId() const {
		return *(int*)(address + 0x08); // titleId offset
	}

	bool getPuchusedStatus() const {
		return *(bool*)(address + 0x10);
	}

	void setPuchusedStatus(bool purchased) {
		*(bool*)(address + 0x10) = purchased;
	}

	int getPrice() const {
		return *(int*)(address + 0x3c);
	}

	void setPrice(int price) {
		*(int*)(address + 0x3c) = price;
	}

	int getCurrencyType() const {
		return *(int*)(address + 0x48);
	}
};

struct MissionStruct {
	uintptr_t maybeINIstrings;
	int id; // format 3 bytes number, last byte m
	int titleId;
	int descId;

	int status;
	int type;
	MissionStruct** preconditionMissionArray;
	int preconditionMissionCount;

	int numberPreconditionMissionNeeded;
	MissionStruct* previusMission;
	MissionStruct* NextMission;
	int unknown0x2c;
	int unknown0x30;
	int unknown0x34;
	int timelimit;
	int unknown0x3c;
	int unknown0x40;
	int unknown0x44;
	int unknown0x48;
	ItemStruct* requiredItemStruct;
	int cutscene;
	int reward;
	int unknown0x58;
	uintptr_t susarray;
	int unknown0x60;
	int unknown0x64;
	int itemHeadingID;
	int itemBodyID;
	int failureHeadingID;
	int failureBodyID;
	int failureActionID;
	int failureResponseType;
	char musicstr[0x20];
	char Undiscovered[0x34];
};

class MissionWrapper {
public:
	uintptr_t address;
	MissionWrapper(uintptr_t addr) : address(addr) {}

	int getTitleId() const {
		return *(int*)(address + 0x08); // titleId offset
	}

	//const char* getMusicStr() const {
	//	return (const char*)(address + 0x5C); // musicstr offset
	//}

	int getRawID() const {
		return *(int*)(address + 0x04);
	}

	short getID() const {
		return *(short*)(address + 0x04);
	}

	char getIDType() const {
		return *(char*)(address + 0x07);
	}

	int getStatus() const {
		return *(int*)(address + 0x10);
	}

	std::vector<MissionWrapper> getPreconditionMissions() const {
		std::vector<MissionWrapper> results;

		// read the pointer to the array of pointers
		MissionStruct** arrayPtr = *(MissionStruct***)(address + offsetof(MissionStruct, preconditionMissionArray));

		// read the count
		int count = *(int*)(address + offsetof(MissionStruct, preconditionMissionCount));

		// basic sanity checks
		if (arrayPtr == nullptr || count <= 0 || count > 1000) return results;

		results.reserve(count);

		for (int i = 0; i < count; ++i) {
			MissionStruct* preconditionPtr = arrayPtr[i];
			if (preconditionPtr != nullptr) {
				results.emplace_back((uintptr_t)preconditionPtr);
			}
		}

		return results;
	}
	/**
	 * @brief Gets the number of missions inside the precondition array at state 5 to unlock this mission.
	 * @return The number of required missions.
	 */
	int getNumberOfMissionsRequired() {
		return *(int*)(address + 0x20);
	}
	/**
	 * @brief Sets the number of missions inside the precondition array at state 5 unlock this mission.
	 * @param numRequired The new number of required missions.
	 */
	void setNumberOfMissionsRequired(int numRequired) {
		*(int*)(address + 0x20) = numRequired;
	}
};

struct SaveDataStruct {
	char percentComplete;
	char unk1[3];
	float playtime; //seconds
	int Opals;
	char paddingc[0x4];

	char padding10[0x10];
	char padding20[0x10];
	char padding30[0x10];
	char padding40[0x10];
	char padding50[0x10];
	char padding60[0x10];
	char padding70[0x10];

	uintptr_t unk80;
	uintptr_t MaybeLevelData;
	uintptr_t SomePtrToLinkedList;
	int unk8c;

	int unk90;
	char padding94[0xC];

	int unka0;
	char paddinga4[0x4];
	int unka8;
	float unkac;//1

	float unkb0;//1
	float unkb4;//0.65
	char paddingb8[0x4];
	float unkbc;//1

	float unkc0;//1
	float unkc4;//0.81
	unsigned char unkc8;
	float unkcc; //periodically changes

	//0x30 length start boomerang
	int paddingd0;
	bool GotBoomerang;
	bool GotMultirang;
	bool GotFlamerang;
	bool GotLavarang;

	bool GotFrostyrang;
	bool GotFreezerang;
	bool GotZappyrang;
	bool GotThunderrang;

	bool GotLasharang;
	bool GotWarparang;
	bool GotInfrarang;
	bool GotXrang;

	bool GotSmasharang;
	bool GotKaboomarang;
	bool GotMegarang;
	bool GotOmegarang;


	bool GotDeadlyrang;
	bool GotDoomarang;
	bool GotAquarang;
	bool Got_rang;

	bool GotCraftyrang;
	bool GotCamerarang;
	char RangPadding[0x2];

	char Rang2Padding[0x4];

	int CurrentRangSave;
	int CurrentRangLive;
	int unkf8;
	float unkfc;//1
	//end boomerang
	float unk100;//0.5
	float unk104;//0.5
	int HeroDamageDefault; //unsure
	int HeroDamageRace;//unsure

	int HeroDamageHelicopter;//unsure
	char padding114[0xc];

	int unk120;
	char padding124[0xc];

	char padding130[0x8];
	//0xb0 long mission start address
	char MissionStart[0x4];
	int TotalMissions;

	char padding2[0x4];
	int NumMissionLists;

	MissionStruct* CrocStruct1;
	int MissionListStatus0Count;
	MissionStruct* ListStatus0Start;
	MissionStruct* ListStatus0End;

	uintptr_t StartofMissionData0;
	int MissionListStatus1Count;
	MissionStruct* ListStatus1Start;
	MissionStruct* LisStatus1End;

	uintptr_t StartofMissionData1;
	int MissionListStatus2Count;
	MissionStruct* ListStatus2Start;
	MissionStruct* ListStatus2End;

	uintptr_t StartofMissionData2;
	int MissionListStatus3Count; //0x12
	MissionStruct* ListStatus3Start;
	MissionStruct* ListStatus3End;

	uintptr_t StartofMissionData3;
	int MissionListStatus4Count; //0x12
	MissionStruct* ListStatus4Start;
	MissionStruct* ListStatus4End;

	uintptr_t StartofMissionData4;
	int MissionListStatus5Count; //0x12
	MissionStruct* ListStatus5Start;
	MissionStruct* ListStatus5End;

	uintptr_t StartofMissionData5;
	int MissionListStatus6Count; //0x12
	MissionStruct* ListStatus6Start;
	MissionStruct* ListStatus6End;

	uintptr_t StartofMissionData6;
	uintptr_t unknown1;
	MissionStruct* TrainingProgram1;
	MissionStruct* TreeRescue;

	MissionStruct* CrocStruct2;
	char padding3[0xc];

	int NumStartingMissions;
	MissionStruct* TrainingProgram;
	MissionStruct* TreeRescue2;
	MissionStruct* CrocStruct3;
	//end missions

	char padding1F4[0xc];
	ItemStruct* FirstItem; //Itemlist

	int TotalItems;
	uintptr_t MaybeRacedata; //linked list
	int mayberacedatalength; //7
	uintptr_t unknown210;

	char padding214[0x2c];
	//collectables
	int unk240c;
	uintptr_t unknown244;

	char padding234[0x4];

	uintptr_t CogBitArray;
	int CogTotal;
	int CogCollected;
	char CogPadding[0x4];
	int Cogunknown;
	uintptr_t BilbyBitArray;
	int BilbyTotal;
	int BilbyCollected;
	char BilbyPadding[0x4];
	int Bilbyunknown;
	uintptr_t FrameBitArray;
	int FrameTotal;
	int FrameCollected;
	char FramePadding[0x4];
	int Frameunknown;
	uintptr_t OrbBitArray;
	int OrbTotal;
	int OrbCollected;
	char OrbPadding[0x4];
	int Orbunknown;
	uintptr_t SteveBitArray;
	int SteveTotal;
	int SteveCollected;
	char StevePadding[0x4];
	int Steveunknown;
	uintptr_t FrillBitArray;
	int FrillTotal;
	int FrillCollected;
	char FrillPadding[0x4];
	int Frillunknown;
	char paddingEnd[0x4];
};


class TYGERMEM2 SaveData {

protected:
	uintptr_t baseAddress;
	static SaveDataStruct* Data;

public:
	static SaveDataStruct* GetData();
	/**
	 * @brief Returns the list of missions with a specific state
	 * @param missionState is the state for the mission fom 0-6 inclusive.
	 * 0 is unavailable. 1 is available but not shown. 2 is available and shown. 3 is active. 4 is able to turn in, 5 is done. 6 is something wierd.
	 * @return The Linked list of missions.
	 */
	static LinkedList<MissionWrapper> MissionList(int missionState);
	static std::optional<MissionWrapper>findMissionByID(int missionId);
	static std::optional<MissionWrapper>findMissionByID(const LinkedList<MissionWrapper>& list, int targetID);

	static LinkedList<ItemWrapper> ItemList(int shopId);
	static std::optional<ItemWrapper> findItemByID(const LinkedList<ItemWrapper>& list, int targetID);
};