#pragma once
#ifdef TYGERMEM_EXPORTS2
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"

struct SaveDataStruct {
	unsigned char percentComplete;
	short unk1;
	unsigned char unk2;
	float playtime; //seconds
	const int Opals;
	char padding1[0x74];
	uintptr_t unk3;
	uintptr_t MaybeLevelData;
	uintptr_t SomePtrToLinkedList;
	int unk6;
	int unk7;
	char padding2[0xC];
	int unk8;
	char padding2[0x4];
	int unk9;
	float unk10;//1
	float unk11;//1
	float unk12;//0.65
	char padding3[0x4];
	float unk10;//1
	float unk11;//1
	float unk12;//0.81
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
	int unk27;
	char padding10[0x10];
	MissionDataStruct MissionData;
	char padding4[0xc];
	ShopDataStruct* ShopData; //linked list
	int ShopDataLength;
	uintptr_t MaybeRacedata;
	int mayberacedatalength; //7
	uintptr_t unknown4;
	char padding5[0xc];
	char padding5[0x20];
	CollectablesStruct CollectableData;
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

struct MissionDataStruct {
	char padding1[0x4];
	int TotalMissions;
	char padding2[0x4];
	int NumMissionLists;
	MissionStruct* CrocStruct1;
	int MissionList1Count; //0x27
	MissionStruct* List1Start;
	MissionStruct* List1End;
	MissionDataStruct* StartofMissionData1;
	int MissionList2Count; //0x3
	MissionStruct* List2Start;
	MissionStruct* List2End;
	MissionDataStruct* StartofMissionData2;
	int MissionList3Count; //0x12
	MissionStruct* List3Start;
	MissionStruct* List3End;
	MissionDataStruct* StartofMissionData3;
	char List4padding[0xc];
	MissionDataStruct* StartofMissionData4;
	char List5padding[0xc];
	MissionDataStruct* StartofMissionData5;
	int MissionListCurrawongCount; //0x1
	MissionStruct* ListCurrawongStart;
	MissionStruct* ListCurrawongEnd;
	MissionDataStruct* StartofMissionData6;
	char List7padding[0xc];
	MissionDataStruct* StartofMissionData7;
	uintptr_t unknown1;
	MissionStruct* TrainingProgram1;
	MissionStruct* TreeRescue;
	MissionStruct* CrocStruct2;
	char padding3[0xc];
	int NumStartingMissions;
	MissionStruct* TrainingProgram;
	MissionStruct* TreeRescue2;
	MissionStruct* CrocStruct2;
};

struct MissionStruct {
	int unk1;
};

struct ShopDataStruct {
	ShopItemStruct LifterBunyip;
	ShopItemStruct ThermoBunyip;
	ShopItemStruct BilbyMap;
	ShopItemStruct CogMap;
	ShopItemStruct AnomaliesMap;
	ShopItemStruct Flamerang;
	ShopItemStruct Frostyrang;
	ShopItemStruct Shop031;
	ShopItemStruct Lasharang;
	ShopItemStruct Infrarang;
	ShopItemStruct Smasharang;
	ShopItemStruct Megarang;
	ShopItemStruct Shop032;
	ShopItemStruct Shop033;
	ShopItemStruct Shop034;
	ShopItemStruct Zappyrang;
	ShopItemStruct Shop035;
	ShopItemStruct Shop036;
	ShopItemStruct Shop037;
	ShopItemStruct Shop038;
	ShopItemStruct UnusedShop2Item;
	ShopItemStruct Shop039;
	ShopItemStruct Shop0310;
	ShopItemStruct UnusedShop3Item;
	ShopItemStruct UnusedShop6Item;
	ShopItemStruct SubBunyip;
	//ITems continue but are unused and for shops that dont exist
};

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

struct CollectableStruct {
	int* BitArray;
	int Total;
	int Collected;
	char Padding[0x4];
	int unknownInt;
};


class TYGERMEM2 SaveData {

protected:
	uintptr_t baseAddress;
	static SaveDataStruct* Data;

public:
	static SaveDataStruct* GetData();
};