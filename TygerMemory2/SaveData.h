#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"

struct ShopItemStruct {
	int* UnknownPtr;
	short ItemId;
	char idfiller;
	char itemLabel; //i
	int unknownInt;
	int unknownIntPlusOne;
	int Purchused; //FFFFFFFFFF
	char paddingpurchuse[0x3];
	int ShopId;
	char Padding[0xc];
	char Unknown2[0x18];
	int Price;
	char Unknown3[0x10];
};

struct CollectableStruct {
	long* BitArray;
	int Total;
	int Collected;
	char Padding[0x4];
	int unknownInt;
};


struct CollectablesStruct {
	int unk1;
	uintptr_t unknown1;
	char padding1[0x4];
	CollectableStruct Cogs;
	CollectableStruct Bilbies;
	CollectableStruct Frames;
	CollectableStruct Orbs;
	CollectableStruct Steve;
	CollectableStruct Frills;
	char padding2[0x4];
};

struct ItemStruct {
	uintptr_t maybeINIstrings;
	int itemId;// format 3 bytes number, last byte m
	int titleId;
	int descId;
	int unknown0x10;
	int type;
	char Undiscovered[0x34]; 
};

struct MissionStruct {
	uintptr_t maybeINIstrings;
	uintptr_t id; // format 3 bytes number, last byte m
	int titleId;
	int descId;
	int status;
	int type;
	MissionStruct** preconditionMissionArray;
	int preconditionMissionCount;
	int numNeeded;
	MissionStruct* nextHighestId;
	MissionStruct* lastHighestId;
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




struct MissionDataStruct {
	char padding1[0x4];
	int TotalMissions;
	char padding2[0x4];
	int NumMissionLists;
	MissionStruct* CrocStruct1;
	int MissionListStatus0Count; 
	MissionStruct* ListStatus0Start;
	MissionStruct* ListStatus0End;
	MissionDataStruct* StartofMissionData0;
	int MissionListStatus1Count; 
	MissionStruct* ListStatus1Start;
	MissionStruct* LisStatus1End;
	MissionDataStruct* StartofMissionData1;
	int MissionListStatus2Count; 
	MissionStruct* ListStatus2Start;
	MissionStruct* ListStatus2End;
	MissionDataStruct* StartofMissionData2;
	int MissionListStatus3Count; //0x12
	MissionStruct* ListStatus3Start;
	MissionStruct* ListStatus3End;
	MissionDataStruct* StartofMissionData3;
	int MissionListStatus4Count; //0x12
	MissionStruct* ListStatus4Start;
	MissionStruct* ListStatus4End;
	MissionDataStruct* StartofMissionData4;
	int MissionListStatus5Count; //0x12
	MissionStruct* ListStatus5Start;
	MissionStruct* ListStatus5End;
	MissionDataStruct* StartofMissionData5;
	int MissionListStatus6Count; //0x12
	MissionStruct* ListStatus6Start;
	MissionStruct* ListStatus6End;
	MissionDataStruct* StartofMissionData6;
	uintptr_t unknown1;
	MissionStruct* TrainingProgram1;
	MissionStruct* TreeRescue;
	MissionStruct* CrocStruct2;
	char padding3[0xc];
	int NumStartingMissions;
	MissionStruct* TrainingProgram;
	MissionStruct* TreeRescue2;
	MissionStruct* CrocStruct3;
};






struct BoomarangStruct {
	bool GotBoomerang;
	bool GotMultirang;
	bool GotFlamerang;
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
	char RangPadding[0x6];
	char CurrentRangSave;
	char SavePadding[0x3];
	char CurrentRangLive;
	char LivePadding[0x3];
};



struct SaveDataStruct {
	unsigned char percentComplete;
	short unk1;
	unsigned char unk2;
	float playtime; //seconds
	const int Opals;
	char padding0[0x74];
	uintptr_t unk3;
	uintptr_t MaybeLevelData;
	uintptr_t SomePtrToLinkedList;
	int unk6;
	int unk7;
	char padding1[0xC];
	int unk8;
	char padding2[0x4];
	int unk9;
	float unk10;//1
	float unk11;//1
	float unk12;//0.65
	char padding3[0x4];
	float unk27;//1
	float unk28;//1
	float unk29;//0.81
	unsigned char unk13;
	unsigned char unk14;
	unsigned char unk15;
	unsigned char unk16;
	float unk17; //periodically changes
	char padding4[0x4];
	BoomarangStruct BoomerangData;
	char padding5[0x4];
	float CurrentLevelDefault;//1
	float CurrentLevelRace;//0.5
	float CurrentLevelHelicopter;//0.5
	int HeroDamageDefault; //unsure
	int HeroDamageRace;//unsure
	int HeroDamageHelicopter;//unsure
	char padding8[0xc];
	int unk26;
	char padding10[0x10];
	MissionDataStruct MissionData;
	char padding11[0xc];
	ItemStruct* FirstItem; //Itemlist
	int TotalItems;
	uintptr_t MaybeRacedata; //linked list
	int mayberacedatalength; //7
	uintptr_t unknown4;
	char padding6[0xc];
	char padding7[0x20];
	CollectablesStruct CollectableData;
};




class TYGERMEM2 SaveData {

protected:
	uintptr_t baseAddress;
	static SaveDataStruct* Data;

public:
	static SaveDataStruct* GetData();
	
};