#include "pch.h"

void __stdcall Start() {
	do {
		Sleep(500);
		Scan(true);
	} while (GetGameTime() < 0.5);
	Scan(false);
	orbWalker = std::make_unique<OrbWalker>();
	functions = std::make_unique<Functions>();
	Print("Noroby's League of Legends Orbwalker");
	ULONGLONG lastLoop = 0;
	while (true)
	{
		if (GetTickCount64() > lastLoop + 20) {
			lastLoop = GetTickCount64();
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) orbWalker->AttackObject(true);
			else if ((GetAsyncKeyState('V') & 0x8000) != 0) orbWalker->AttackObject(false);
		}
	}
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
		return TRUE;
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		return TRUE;
	}
	return FALSE;
}
