#pragma once
#include "object.h"

namespace funcTypes {
	using fnPrintChat = void(__thiscall*)(DWORD*, const char*, int);
	using fnIssueOrder = int(__thiscall*)(DWORD HudThisPtr, int state, int IsAttack, int IsAttackCommand, int x, int y, int AttackAndMove);
	using fnGetAttackCastDelay = float(__cdecl*)(Object* pObj);
	using fnGetAttackDelay = float(__cdecl*)(Object* pObj);
	using fnIsAlive = bool(__thiscall*)(Object* pObj);
}

class Functions {
public:
	Functions();
	funcTypes::fnPrintChat PrintChat;
	funcTypes::fnIssueOrder IssueOrder;
	funcTypes::fnGetAttackCastDelay GetAttackCastDelay;
	funcTypes::fnGetAttackDelay GetAttackDelay;
	funcTypes::fnIsAlive IsAlive;
};

extern std::unique_ptr<Functions> functions;