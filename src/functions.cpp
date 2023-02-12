#include "pch.h"

Functions::fnPrintChat Functions::PrintChat{};
Functions::fnIssueOrder Functions::IssueOrder{};
Functions::fnGetAttackCastDelay Functions::GetAttackCastDelay{};
Functions::fnGetAttackDelay Functions::GetAttackDelay{};
Functions::fnIsAlive Functions::IsAlive{};
Functions::fnGetRadius Functions::GetRadius{};

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