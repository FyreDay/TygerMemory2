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



class ItemStruct {
public:
	uintptr_t itemINIPtr;
	short itemId;
	char typeCharPadding;
	char typeChar;
	int titleId;
	int descId;

	bool purchased;
	char boolAlignmentPadding[0x3];
	int type;
	uintptr_t requirementsArrayPtr;
	int requirementsArrayLength;

	bool locked;
	char Padding2[0x3];
	uintptr_t nextItem;
	uintptr_t previousItem;
	uintptr_t numItemsInShopPtr;

	uintptr_t startofMissionData;
	uintptr_t targetString;
	uintptr_t TDAIconString;
	int price;

	int ShopId;
	int subtype;
	int currencyType;
	uintptr_t ShopIconNameString;

	int getRawID() const {
		return *reinterpret_cast<const int*>(&this->itemId);
	}

	void setItemRequirements(uintptr_t itemPtrArray, int size) {
		this->requirementsArrayPtr = itemPtrArray;
		this->requirementsArrayLength = size;
	}
};

struct ShopStruct {
	uintptr_t shopINI;
	int shopId;
	int titleId;
	int descId;

	bool flag;
	char boolAlignmentPadding[0x3];
	char Padding14[0xC];

	char Padding20[0x10];

	char Padding30[0x4];
	int numItems;
	ItemStruct* lastItem;
	ItemStruct* firstItem;
};

class MissionStruct {
public:
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

	int getRawID() const {
		return *reinterpret_cast<const int*>(&this->id);
	}

	std::vector<MissionStruct> getPreconditionMissions() const {
		std::vector<MissionStruct> results;

		// basic sanity checks
		if (this->preconditionMissionArray == nullptr || this->preconditionMissionCount <= 0 || this->preconditionMissionCount > 1000) return results;

		results.reserve(this->preconditionMissionCount);

		for (int i = 0; i < this->preconditionMissionCount; ++i) {
			MissionStruct* preconditionPtr = this->preconditionMissionArray[i];

			if (preconditionPtr != nullptr) {
				results.emplace_back(*preconditionPtr);
			}
		}

		return results;
	}
};

struct SaveDataStruct {
	char percentComplete;
	char unk1[3];
	float playtime; //seconds
	int Opals;
	int GameMode; // 2 for hardcore
	
	char padding10[0x10];
	char padding20[0x10];
	char padding30[0x10];
	char padding40[0x10];
	char padding50[0x10];
	char padding60[0x10];
	char padding70[0x10];

	uintptr_t unkPtr;
	uintptr_t LinkedListofLv3; //0: lv2 4: first object 8:
	uintptr_t SomePtrToLinkedList;
	int unk8c; // 1

	int vibration; // boolean
	int controlScheme;
	int cart1ControlScheme;
	int cart2ControlScheme;

	bool unkSettingsFlag1;
	bool unkSettingsFlag2;
	bool unkSettingsFlag3;
	bool swimmingInvert;
	bool doomerangInvert;
	bool unkSettingsFlag4;
	bool unkSettingsFlag5;
	bool unkSettingsFlag6;
	int unka8; // 1
	float tysViewInvertX; // 1 or -1

	float tysViewInvertY; // 1 or -1
	float tysViewSpeed;
	bool tysViewDirection; // 1 for body 0 for camera
	bool unkSettingsFlag7;
	bool unkSettingsFlag8;
	bool unkSettingsFlag9;
	float cameraInvertX; // 1 or -1
	float cameraInvertY; // 1 or -1
	float cameraSpeed;
	bool cameraAutoCenter;
	bool cameraMoveWithJump;
	bool unkSettingsFlag10;
	bool unkSettingsFlag11;
	float cameraZoom;

	//0x30 length start boomerang
	int damageTakenTy;
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

	int unkRangCount2; // Changed to 1 when doing donuts in fourbie. Could be some kind of skill point flags???

	int CurrentRangSave;
	int CurrentRangLive;
	char shopsVisitedFlags;
	char shopsVisitedPadding[0x3];

	float unkfc;
	float unk100;
	float unk104;
	int damageTakenTyGlobal; // Applies across all saves
	int damageTakenRace; // unsure
	int unkDamageTaken; // unsure
	char padding114[0xc];

	int enemiesKilledGlobal; // Applies across all saves
	char padding124[0xc];

	char padding130[0x4];

	int gameState; // 2 = minigame

	// 0xb0 long mission start address
	char MissionStart[0x4];
	int TotalMissions;

	char padding2[0x4];
	int NumMissionLists;
	//0: unavailable
	MissionStruct* CrocStruct1;
	int MissionListStatus0Count;
	MissionStruct* ListStatus0Start;
	MissionStruct* ListStatus0End;
	//1:available but unknown
	uintptr_t StartofMissionData0;
	int MissionListStatus1Count;
	MissionStruct* ListStatus1Start;
	MissionStruct* ListStatus1End;
	//2: known and on map
	uintptr_t StartofMissionData1;
	int MissionListStatus2Count;
	MissionStruct* ListStatus2Start;
	MissionStruct* ListStatus2End;
	//3: active
	uintptr_t StartofMissionData2;
	int MissionListStatus3Count; //0x12
	MissionStruct* ListStatus3Start;
	MissionStruct* ListStatus3End;
	//4: able to turn in
	uintptr_t StartofMissionData3;
	int MissionListStatus4Count; //0x12
	MissionStruct* ListStatus4Start;
	MissionStruct* ListStatus4End;
	//5: complete
	uintptr_t StartofMissionData4;
	int MissionListStatus5Count; //0x12
	MissionStruct* ListStatus5Start;
	MissionStruct* ListStatus5End;
	//6: replayable
	uintptr_t StartofMissionData5;
	int MissionListStatus6Count; //0x12
	MissionStruct* ListStatus6Start;
	MissionStruct* ListStatus6End;

	uintptr_t StartofMissionData6;
	uintptr_t unknown1;
	MissionStruct* TrainingProgram1;
	MissionStruct* TreeRescue;

	MissionStruct* CrocStruct2;
	MissionStruct* activeMission;
	int callSheetCount;
	MissionStruct* callSheetMissions[6];
	//end missions

	ItemStruct* FirstItem; // Item list
	int TotalItems;
	ShopStruct* FirstShop; // Shop list
	int shopCount; // 7

	uintptr_t settingsIni;
	char padding214[0x2c];
	int unk240c;
	uintptr_t missionsIni;

	//collectables
	char unknown234[0x4];

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

	char unkDataBlock[0x400];
	int cheatsUsed; // boolean
	int mapRotation; // boolean
	int currentTySkin;
	int currentFourbieSkin;
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
	static LinkedList<MissionStruct> MissionList(int missionState);
	static std::optional<MissionStruct>findMissionByID(int missionId);
	static std::optional<MissionStruct>findMissionByID(const LinkedList<MissionStruct>& list, int targetID);

	static LinkedList<ItemStruct> GetShopItemList(int shopId);
	static std::optional<ItemStruct> findItemByID(const LinkedList<ItemStruct>& list, int targetID);
};