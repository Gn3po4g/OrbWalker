#include "pch.h"

Functions::Functions() :
	PrintChat{ (fnPrintChat)offsets.oPrintChat },
	IssueOrder{ (fnIssueOrder)offsets.oIssueOrder },
	GetAttackCastDelay{ (fnGetAttackCastDelay)offsets.oGetAttackCastDelay },
	GetAttackDelay{ (fnGetAttackDelay)offsets.oGetAttackDelay },
	IsAlive{ (fnIsAlive)offsets.oIsAlive },
	GetRadius{(fnGetRadius)offsets.oGetRadius} {
}

float Functions::GetGameTime() const {
	return *(float*)offsets.oGameTime;
}

bool Functions::IsLeagueInForeground() const {
	return !*(bool*)(*(PDWORD)offsets.oHudInstance + 0x69);
}

DirectX::XMFLOAT3 Functions::GetMouseWorldPosition() const {
	const auto MousePtr = *(DWORD*)(*(DWORD*)offsets.oHudInstance + 0x14);
	return *(DirectX::XMFLOAT3*)(MousePtr + 0x1C);
}

void Functions::Click(const DirectX::XMINT2 pos) {
	const auto HUDInput = *(PDWORD)(*(PDWORD)offsets.oHudInstance + 0x24);
	IssueOrder(HUDInput, 0, 0, nullptr, pos.x, pos.y, 0);
	IssueOrder(HUDInput, 1, 0, nullptr, pos.x, pos.y, 0);
}

void Functions::Attack(const DirectX::XMINT2 pos) {
	const auto HUDInput = *(PDWORD)(*(PDWORD)offsets.oHudInstance + 0x24);
	IssueOrder(HUDInput, 0, 1, nullptr, pos.x, pos.y, 0);
	IssueOrder(HUDInput, 1, 1, nullptr, pos.x, pos.y, 0);
}
