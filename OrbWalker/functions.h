#pragma once
#include "object.h"
#include "offsets.h"

namespace funcTypes {
	using fnPrintChat = void(__thiscall*)(DWORD*, const char*, int);
	using fnIssueOrder = int(__thiscall*)(DWORD HudThisPtr, int state, int IsAttack, int IsAttackCommand, int x, int y, int AttackAndMove);
	using fnGetAttackCastDelay = float(__cdecl*)(Object* pObj);
	using fnGetAttackDelay = float(__cdecl*)(Object* pObj);
	using fnIsAlive = bool(__thiscall*)(Object* pObj);
}

inline funcTypes::fnPrintChat PrintChat;
inline funcTypes::fnIssueOrder IssueOrder;
inline funcTypes::fnGetAttackCastDelay GetAttackCastDelay;
inline funcTypes::fnGetAttackDelay GetAttackDelay;
inline funcTypes::fnIsAlive IsAlive;

inline void InitFunctions()
{
	PrintChat = static_cast<funcTypes::fnPrintChat>(oPrintChat);
	IssueOrder = static_cast<funcTypes::fnIssueOrder>(oIssueOrder);
	GetAttackCastDelay = static_cast<funcTypes::fnGetAttackCastDelay>(oGetAttackCastDelay);
	GetAttackDelay = static_cast<funcTypes::fnGetAttackDelay>(oGetAttackDelay);
	IsAlive = static_cast<funcTypes::fnIsAlive>(oIsAlive);
};