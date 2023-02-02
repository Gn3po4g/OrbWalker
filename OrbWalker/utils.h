#pragma once
#include "vector.h"

inline void Print(const char* message) {
	PrintChat(static_cast<DWORD*>(oChatClient), message, 0);
};

inline float GetGameTime() {
	return *static_cast<float*>(oGameTime);
}

inline Vector3 GetMouseWorldPosition() {
	const auto MousePtr = *reinterpret_cast<DWORD*>(*static_cast<DWORD*>(oHudInstance) + 0x14);
	return *reinterpret_cast<Vector3*>(MousePtr + 0x1C);
}

inline bool IsLeagueInForeground() {
	return !*(*static_cast<bool**>(oHudInstance) + 0x69);
}

inline void Click(const Vector2 pos) {
	const auto HUDInput = *reinterpret_cast<DWORD*>(*static_cast<DWORD*>(oHudInstance) + 0x24);
	IssueOrder(HUDInput, 0, 0, 0, static_cast<int>(pos.x), static_cast<int>(pos.y), 0);
	IssueOrder(HUDInput, 1, 0, 0, static_cast<int>(pos.x), static_cast<int>(pos.y), 0);
}

inline void Attack(const Vector2 pos) {
	const auto HUDInput = *reinterpret_cast<DWORD*>(*static_cast<DWORD*>(oHudInstance) + 0x24);
	IssueOrder(HUDInput, 0, 1, 0, static_cast<int>(pos.x), static_cast<int>(pos.y), 0);
	IssueOrder(HUDInput, 1, 1, 0, static_cast<int>(pos.x), static_cast<int>(pos.y), 0);
};