#pragma once

#include "object.h"

class Functions {
	using fnPrintChat = void(__thiscall*)(PDWORD, const char*, int);
	using fnIssueOrder = int(__thiscall*)(DWORD, int, int, PDWORD, int, int, char);
	using fnGetAttackCastDelay = float(__cdecl*)(Object*);
	using fnGetAttackDelay = float(__cdecl*)(Object*);
	using fnIsAlive = bool(__thiscall*)(Object*);
public:
	Functions();
	fnPrintChat PrintChat;
	fnIssueOrder IssueOrder;
	fnGetAttackCastDelay GetAttackCastDelay;
	fnGetAttackDelay GetAttackDelay;
	fnIsAlive IsAlive;
	float GetGameTime() const;
	bool IsLeagueInForeground() const;
	DirectX::XMFLOAT3 GetMouseWorldPosition() const;
	void Click(const DirectX::XMINT2);
	void Attack(const DirectX::XMINT2);
};
