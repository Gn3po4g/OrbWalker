#include "function.hpp"
#include "offset.hpp"
#include <cstddef>
#include <Windows.h>

using namespace offset;

struct W2S
{
	DirectX::XMFLOAT4X4 view_matrix;
	DirectX::XMFLOAT4X4 proj_matrix;

private:
	std::byte pad[0x14];

public:
	int width;
	int height;
} *w2s;

float GameTime() {
	if (!oGameTime) return 0.f;
	return *(float*)oGameTime;
}

bool IsChatOpen() {
	return *(bool*)(*(uintptr_t*)oChatClient + 0xC90);
}

bool IsLeagueInBackground() {
	return *(bool*)(*(uintptr_t*)oHudInstance + 0xB9);
}

void PrintMessage(std::string color, std::string text) {
	using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
	const auto wrapped = "<font color=" + color + '>' + text + "</font>";
	((fnPrintChat)oPrintChat)(oChatClient, wrapped.data(), 4);
}

DirectX::XMINT2 WorldToScreen(DirectX::XMFLOAT3 pos) {
	w2s = (W2S*)oViewProjMatrices;
	using namespace DirectX;
	auto V = XMVectorSetW(XMLoadFloat3(&pos), 1.f);
	auto M = XMLoadFloat4x4(&w2s->view_matrix) * XMLoadFloat4x4(&w2s->proj_matrix);
	auto coord = XMVector3TransformCoord(V, M);
	return {
		(int)((1 + XMVectorGetX(coord)) / 2 * w2s->width),
		(int)((1 - XMVectorGetY(coord)) / 2 * w2s->height)
	};
}

void Attack(Object* me, Object* obj) {
	const auto pos = WorldToScreen(obj->position());
	auto pFloatCheck1 = (float*)((uintptr_t)me + 0x84), pFloatCheck2 = (float*)((uintptr_t)me + 0x88);
	auto pCheck = (DWORD*)((uintptr_t)me + 0xD4);
	auto floatCheck1 = *pFloatCheck1, floatCheck2 = *pFloatCheck2;
	auto check = *pCheck;
	*pFloatCheck1 = 0.f;
	*pFloatCheck2 = 0.f;
	*pCheck = 0;

	typedef bool(__fastcall* fnIssueOrder)(Object* player, int order, bool isAttackMove, bool isMinion, int screenX, int screenY, int unknown);
	fnIssueOrder _fnIssueOrder = (fnIssueOrder)((uintptr_t)GetModuleHandle(nullptr) + 0x8A0010);
	_fnIssueOrder(me, 2, false, false, pos.x, pos.y, 1);

	*pFloatCheck1 = floatCheck1;
	*pFloatCheck2 = floatCheck2;
	*pCheck = check;
}


void Move2Mouse() {
	using fnIssueMove = bool(__fastcall*)(uintptr_t hudInput, int screenX, int screenY, bool isAttackMove, int zeroOrOne, int order);
	fnIssueMove _fnIssueMove = (fnIssueMove)((uintptr_t)GetModuleHandle(nullptr) + 0x88A460);
	if (POINT pos; GetCursorPos(&pos)) {
		auto hudInput = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x28);
		_fnIssueMove(hudInput, pos.x, pos.y, false, 0, 1);
	}
}