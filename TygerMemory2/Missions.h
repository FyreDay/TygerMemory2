#pragma once
#ifdef TYGERMEM2_EXPORTS
#define TYGERMEM2 __declspec(dllexport)
#else
#define TYGERMEM2 __declspec(dllimport)
#endif
#include "core.h"
#include "framework.h"
#include "SaveData.h"

class TYGERMEM2 Missions {
public:
	static void UpdateMissionState(MissionStruct* mission, int state, char unk);
};