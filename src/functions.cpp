#include "pch.h"

Functions::Functions() :
	PrintChat{ (fnPrintChat)offsets.oPrintChat },
	IssueOrder{ (fnIssueOrder)offsets.oIssueOrder },
	GetAttackCastDelay{ (fnGetAttackCastDelay)offsets.oGetAttackCastDelay },
	GetAttackDelay{ (fnGetAttackDelay)offsets.oGetAttackDelay },
	IsAlive{ (fnIsAlive)offsets.oIsAlive },
	GetRadius{ (fnGetRadius)offsets.oGetRadius } {
}

bool Functions::IsChatOpen() const {
	return *(bool*)(*(PDWORD)offsets.oChatClient + 0x820);
}

bool Functions::IsLeagueInBackground() const {
	return *(bool*)(*(PDWORD)offsets.oHudInstance + 0x69);
}