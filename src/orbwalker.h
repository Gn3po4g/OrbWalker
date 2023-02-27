#pragma once

#include "renderer.h"

class OrbWalker {
	static inline Renderer* renderer{};
	static inline Object* me{};
	static inline ObjList* heroes{};
	static inline ObjList* attackables{};
	static inline ObjList* turrets{};
	static inline ObjList* inhibitors{};
	static inline ObjList* minions{};
	static inline DWORD_PTR HUDInput{};
	static inline XMFLOAT3* MousePos{};
	static inline ULONGLONG lastAttackTime{};
	static inline ULONGLONG lastMoveTime{};
public:
	static void Initialize();
	static void AttackChampion();
	static void CleanLane();
	static void LastHit();
};