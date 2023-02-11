#pragma once

#include "object.h"

class Functions {
	using fnPrintChat = void(__thiscall*)(PDWORD, const char*, int);
	using fnIssueOrder = int(__thiscall*)(DWORD, int, int, int, int, int, char);
	using fnGetAttackCastDelay = double(__cdecl*)(const Object*);
	using fnGetAttackDelay = double(__cdecl*)(const Object*);
	using fnIsAlive = bool(__thiscall*)(const Object*);
	using fnGetRadius = double(__thiscall*)(const Object*);
public:
	Functions();
	fnPrintChat PrintChat;
	fnIssueOrder IssueOrder;
	fnGetAttackCastDelay GetAttackCastDelay;
	fnGetAttackDelay GetAttackDelay;
	fnIsAlive IsAlive;
	fnGetRadius GetRadius;
	bool IsChatOpen() const;
	bool IsLeagueInBackground() const;
};
