#pragma once
#include "object.h"

namespace funcTypes {
	using fnIssueOrder = int *(__thiscall *)(Object* obj, int order, Vector3* pos, Object* target, bool isAttackMove, bool isMinion, DWORD unknown);
	using fnGetAttackCastDelay = float(__cdecl*)(Object* pObj);
	using fnGetAttackDelay = float(__cdecl*)(Object* pObj);
	using fnIsAlive = bool(__thiscall*)(Object* pObj);
}

class Functions {
public:
	Functions();
	funcTypes::fnGetAttackCastDelay GetAttackCastDelay = nullptr;
	funcTypes::fnGetAttackDelay GetAttackDelay = nullptr;
	funcTypes::fnIsAlive IsAlive = nullptr;
	funcTypes::fnIssueOrder IssueOrder = nullptr;
};

extern std::unique_ptr<Functions> functions;