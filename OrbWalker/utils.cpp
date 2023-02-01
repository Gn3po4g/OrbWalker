#include "pch.h"

void Print(const char* message) {
	functions->PrintChat((DWORD*)oChatClient, message, 0);
};

float GetGameTime() {
	return *(float*)oGameTime;
}

Vector3 GetMouseWorldPosition() {
	DWORD MousePtr = *(DWORD*)(*(DWORD*)oHudInstance + 0x14);
	return *(Vector3*)(MousePtr + 0x1C);
}

bool IsLeagueInForeground() {
	return !*(*reinterpret_cast<bool**>(BASE + oHudInstance) + 0x69);
}

void Click(Vector2 pos) {
	DWORD HUDInput = *(DWORD*)(*(DWORD*)(oHudInstance)+0x24);
	functions->IssueOrder(HUDInput, 0, 0, 0, (int)pos.x, (int)pos.y, 0);
	functions->IssueOrder(HUDInput, 1, 0, 0, (int)pos.x, (int)pos.y, 0);
}

void Attack(Vector2 pos) {
	DWORD HUDInput = *(DWORD*)(*(DWORD*)(oHudInstance)+0x24);
	functions->IssueOrder(HUDInput, 0, 1, 0, (int)pos.x, (int)pos.y, 0);
	functions->IssueOrder(HUDInput, 1, 1, 0, (int)pos.x, (int)pos.y, 0);
};