#include "pch.h"

DWORD FindDevice(const DWORD len) {
	const auto dwObjBase = reinterpret_cast<DWORD>(LoadLibrary("d3d9.dll"));
	for (DWORD i = dwObjBase; i < dwObjBase + len; i++) {
		if (i &&
			*reinterpret_cast<WORD*>(i + 0x00) == 0x06C7 &&
			*reinterpret_cast<WORD*>(i + 0x06) == 0x8689 &&
			*reinterpret_cast<WORD*>(i + 0x0C) == 0x8689
		)
			return i + 2;
	}
	return dwObjBase;
}

DWORD GetDeviceAddress(const int vTableIndex) {
	const PDWORD vTable = *reinterpret_cast<DWORD**>(FindDevice(0x128000));
	return vTable[vTableIndex];
}


Object* GetLocalPlayer() {
	return *reinterpret_cast<Object**>(BASE + offsets::oLocalPlayer);
}

ObjList* GetHeroList() {
	return *reinterpret_cast<ObjList **>(BASE + offsets::oHeroList);
}

ObjList *GetTurretList() {
	return *reinterpret_cast<ObjList **>(BASE + offsets::oTurretList);
}

ObjList *GetInhibitorList() {
	return *reinterpret_cast<ObjList **>(BASE + offsets::oInhibitorList);
}

ObjList * GetMinionList() {
	return *reinterpret_cast<ObjList **>(BASE + offsets::oMinionList);
}

float GetGameTime() {
	return *reinterpret_cast<float*>(BASE + offsets::oGameTime) * 1000.f;
}

Vector3 GetMouseWorldPosition() {
	const auto p = *reinterpret_cast<DWORD*>(BASE + offsets::oHudInstance) + 0x19C;
	return *reinterpret_cast<Vector3*>(p);
}

bool IsLeagueInForeground() {
	return !*(*reinterpret_cast<bool**>(BASE + offsets::oHudInstance) + 0x69);
}
