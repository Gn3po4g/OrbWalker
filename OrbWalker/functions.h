#pragma once

namespace Functions {
	using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
	using fnIssueOrder = int(__fastcall*)(uintptr_t, int, int, int, int, int, int);
	using fnGetAttackCastDelay = float(__fastcall*)(const Object* const);
	using fnGetAttackDelay = float(__fastcall*)(const Object* const);
	using fnIsAlive = bool(__fastcall*)(const Object* const);
	using fnGetRadius = float(__fastcall*)(const Object* const);
	extern fnPrintChat PrintChat;
	extern fnIssueOrder IssueOrder;
	extern fnGetAttackCastDelay GetAttackCastDelay;
	extern fnGetAttackDelay GetAttackDelay;
	extern fnIsAlive IsAlive;
	extern fnGetRadius GetRadius;
	void Initialize();
	bool IsChatOpen();
	bool IsLeagueInBackground();
};
