#include "Missions.h"


void Missions::UpdateMissionState(uintptr_t mission, int state, char unk) {
    uintptr_t result;
    typedef void(__thiscall* FunType)(int thisPtr, int param2, char param3);
    FunType callFunc = reinterpret_cast<FunType>(Core::moduleBase + 0x00297340);
    callFunc((int)mission, state, unk);
}