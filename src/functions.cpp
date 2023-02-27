#include "pch.h"

void Functions::Initialize() {
	PrintChat = (fnPrintChat)offsets.oPrintChat;
	IssueOrder = (fnIssueOrder)offsets.oIssueOrder;
	GetAttackCastDelay = (fnGetAttackCastDelay)offsets.oGetAttackCastDelay;
	GetAttackDelay = (fnGetAttackDelay)offsets.oGetAttackDelay;
	IsAlive = (fnIsAlive)offsets.oIsAlive;
	GetRadius = (fnGetRadius)offsets.oGetRadius;
}

bool Functions::IsChatOpen() {
	return *(bool*)(*(PDWORD)offsets.oChatClient + 0x820);
}

bool Functions::IsLeagueInBackground() {
	return *(bool*)(*(PDWORD)offsets.oHudInstance + 0x69);
}

ULONGLONG Functions::GetGameTime() {
	return static_cast<ULONGLONG>(*(float*)offsets.oGameTime * 1000);
}