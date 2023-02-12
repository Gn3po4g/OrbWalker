#pragma once

#include "object.h"

class Functions {
	using fnPrintChat = void(__thiscall*)(DWORD_PTR, const char*, int);
	using fnIssueOrder = int(__thiscall*)(DWORD_PTR, int, int, int, int, int, char);
	using fnGetAttackCastDelay = double(__cdecl*)(const Object*);
	using fnGetAttackDelay = double(__cdecl*)(const Object*);
	using fnIsAlive = bool(__thiscall*)(const Object*);
	using fnGetRadius = double(__thiscall*)(const Object*);
public:
	static fnPrintChat PrintChat;
	static fnIssueOrder IssueOrder;
	static fnGetAttackCastDelay GetAttackCastDelay;
	static fnGetAttackDelay GetAttackDelay;
	static fnIsAlive IsAlive;
	static fnGetRadius GetRadius;
	static void Initialize();
	static bool IsChatOpen();
	static bool IsLeagueInBackground();
};
