#include "pch.h"

void CALLBACK TimerProc(HWND, UINT, UINT, DWORD)
{
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0) AttackObject(true);
	else if ((GetAsyncKeyState('V') & 0x8000) != 0) AttackObject(false);
}

void __stdcall Start()
{
	do
	{
		Sleep(500);
		Scan(true);
	}
	while (GetGameTime() < 0.5f);
	Scan(false);
	InitFunctions();
	InitOrbWalker();
	Print("Noroby's League of Legends Orbwalker");
	const auto tId = SetTimer(nullptr, 1, 20, TimerProc);
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}
	KillTimer(nullptr, tId);
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Start), nullptr, 0, nullptr);
		return TRUE;
	}
	if (dwReason == DLL_PROCESS_DETACH)
	{
		return TRUE;
	}
	return FALSE;
}
