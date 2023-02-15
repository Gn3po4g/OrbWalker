#include "pch.h"
#include <process.h>

unsigned int __stdcall Start(void*) {
	Memory::Initialize();
	Functions::Initialize();
	OrbWalker::Initialize();
	const auto aco = (bool*)(*(PDWORD_PTR)(*(PDWORD_PTR)offsets.oHudInstance + 0x30) + 0x20);
	while (Memory::GameState && *Memory::GameState == 2) {
		if (Functions::IsChatOpen() || Functions::IsLeagueInBackground()) continue;
		*aco = GetAsyncKeyState(VK_SPACE) & 0x8000;
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) OrbWalker::AttackObject(Type::space);
		else if ((GetAsyncKeyState('V') & 0x8000) != 0) OrbWalker::AttackObject(Type::v);
		else if ((GetAsyncKeyState('X') & 0x8000) != 0) OrbWalker::AttackObject(Type::x);
		this_thread::sleep_for(50ms);
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID) {
	if (dwReason == DLL_PROCESS_ATTACH) {
		_beginthreadex(nullptr, 0, Start, nullptr, 0, nullptr);
		CloseHandle(hModule);
	}
	return TRUE;
}
