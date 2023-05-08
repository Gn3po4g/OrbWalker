#include "pch.h"

namespace Functions {
	fnPrintChat PrintChat;
	fnIssueOrder IssueOrder;
	fnGetAttackCastDelay GetAttackCastDelay;
	fnGetAttackDelay GetAttackDelay;
	fnIsAlive IsAlive;
	fnGetRadius GetRadius;

	void Initialize() {
		PrintChat = (fnPrintChat)offsets.oPrintChat;
		IssueOrder = (fnIssueOrder)offsets.oIssueOrder;
		GetAttackCastDelay = (fnGetAttackCastDelay)offsets.oGetAttackCastDelay;
		GetAttackDelay = (fnGetAttackDelay)offsets.oGetAttackDelay;
		IsAlive = (fnIsAlive)offsets.oIsAlive;
		GetRadius = (fnGetRadius)offsets.oGetRadius;
	}

	bool IsChatOpen() {
		return *(bool*)(*(uintptr_t*)offsets.oChatClient + 0xC90);
	}

	bool IsLeagueInBackground() {
		return *(bool*)(*(uintptr_t*)offsets.oHudInstance + 0xB9);
	}
}