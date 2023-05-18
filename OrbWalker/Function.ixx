module;
#include <cstdint>
#include <DirectXMath.h>
export module Function;
import Object;

using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
using fnIssueOrder = int(__fastcall*)(uintptr_t, int, int, int, int, int, int);
using fnAttackCastDelay = float(__fastcall*)(Object*);
using fnAttackDelay = float(__fastcall*)(Object*);
using fnIsAlive = bool(__fastcall*)(Object*);
using fnBonusRadius = float(__fastcall*)(Object*);

export {
	using DirectX::XMINT2;
	using DirectX::XMFLOAT3;
	fnPrintChat PrintChat;
	fnIssueOrder IssueOrder;
	fnAttackCastDelay AttackCastDelay;
	fnAttackDelay AttackDelay;
	fnIsAlive IsAlive;
	fnBonusRadius BonusRadius;
	void InitFunction();
	bool IsChatOpen();
	bool IsLeagueInBackground();
	XMINT2 WorldToScreen(XMFLOAT3);
}