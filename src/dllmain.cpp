#include "pch.h"
#include <process.h>

std::unique_ptr<Functions> f;
const int* GameState;

unsigned int __stdcall Start(void*) {
	const auto _ = std::make_unique<Memory>();
	f = std::make_unique<Functions>();
	const auto o = std::make_unique<OrbWalker>();
	while(*GameState == 2) {
		Sleep(30);
		if(f->IsChatOpen() || f->IsLeagueInBackground()) continue;
		if((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) o->AttackObject(true);
		else if((GetAsyncKeyState('V') & 0x8000) != 0) o->AttackObject(false);
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	if(dwReason == DLL_PROCESS_ATTACH) {
		_beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
		CloseHandle(hModule);
	}
	return TRUE;
}
