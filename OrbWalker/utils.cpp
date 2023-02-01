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

Vector2 WorldToScreen(Vector3 pos) {
	float x, y, z, w;
	x = pos.x * viewProjMatrix._11 + pos.y * viewProjMatrix._21 + pos.z * viewProjMatrix._31 + viewProjMatrix._41;
	y = pos.x * viewProjMatrix._12 + pos.y * viewProjMatrix._22 + pos.z * viewProjMatrix._32 + viewProjMatrix._42;
	z = pos.x * viewProjMatrix._13 + pos.y * viewProjMatrix._23 + pos.z * viewProjMatrix._33 + viewProjMatrix._43;
	w = pos.x * viewProjMatrix._14 + pos.y * viewProjMatrix._24 + pos.z * viewProjMatrix._34 + viewProjMatrix._44;
	if (w < 1.0f) w = 1.f;
	Vector2 screen{ (float)width, (float)height };
	Vector2 M{ x / w,y / w };
	return { (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f) ,-(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f) };
}

bool IsLeagueInForeground() {
	return !*(*reinterpret_cast<bool**>(BASE + oHudInstance) + 0x69);
}

void Click(Vector2 pos) {
	DWORD HUDInput = *(DWORD*)(*(DWORD*)(oHudInstance)+0x24);
	functions->IssueOrder(HUDInput, 0, 0, 1, (int)pos.x, (int)pos.y, 0);
	functions->IssueOrder(HUDInput, 1, 0, 1, (int)pos.x, (int)pos.y, 0);
}

void Attack(Vector2 pos) {
	DWORD HUDInput = *(DWORD*)(*(DWORD*)(oHudInstance)+0x24);
	functions->IssueOrder(HUDInput, 0, 1, 1, (int)pos.x, (int)pos.y, 0);
	functions->IssueOrder(HUDInput, 1, 1, 1, (int)pos.x, (int)pos.y, 0);
};