module;
#include <cstdint>
#include <DirectXMath.h>
export module Function;
import Object;

using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
using fnIssueOrder = int(__fastcall*)(uintptr_t, int, int, int, int, int, int);
using fnGetAttackCastDelay = float(__fastcall*)(const Object* const);
using fnGetAttackDelay = float(__fastcall*)(const Object* const);
using fnIsAlive = bool(__fastcall*)(const Object* const);
using fnGetRadius = float(__fastcall*)(const Object* const);

export {
	using DirectX::XMINT2;
	using DirectX::XMFLOAT3;
	fnPrintChat PrintChat;
	fnIssueOrder IssueOrder;
	fnGetAttackCastDelay GetAttackCastDelay;
	fnGetAttackDelay GetAttackDelay;
	fnIsAlive IsAlive;
	fnGetRadius GetRadius;
	void InitFunction();
	bool IsChatOpen();
	bool IsLeagueInBackground();
	XMINT2 WorldToScreen(const XMFLOAT3);
}