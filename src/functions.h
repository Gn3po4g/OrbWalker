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
	static inline fnPrintChat PrintChat{};
	static inline fnIssueOrder IssueOrder{};
	static inline fnGetAttackCastDelay GetAttackCastDelay{};
	static inline fnGetAttackDelay GetAttackDelay{};
	static inline fnIsAlive IsAlive{};
	static inline fnGetRadius GetRadius{};
	static void Initialize();
	static bool IsChatOpen();
	static bool IsLeagueInBackground();
	static ULONGLONG GetGameTime();
};
