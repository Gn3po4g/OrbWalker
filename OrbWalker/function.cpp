#include "stdafx.hpp"

using namespace offset;

struct W2S {
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

INT2 WorldToScreen(FLOAT3 pos) {
	w2s = (W2S*)oViewProjMatrices;
	using namespace DirectX;
	auto V = XMVECTOR{ pos.x, pos.y, pos.z, 1.f };
	auto M = XMLoadFloat4x4(&w2s->view_matrix) * XMLoadFloat4x4(&w2s->proj_matrix);
	auto coord = XMVector3TransformCoord(V, M);
	return {
		(int)((1 + XMVectorGetX(coord)) / 2 * w2s->width),
		(int)((1 - XMVectorGetY(coord)) / 2 * w2s->height)
	};
}

void Attack(Object* target) {
	using fnIssueOrder = int(__fastcall*)(uintptr_t, bool, int, int, int, int, int);
	const auto pos = WorldToScreen(target->position());
	auto hudInput = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x48);
	((fnIssueOrder)oIssueOrder)(hudInput, false, 0, 1, pos.x, pos.y, 1);
}


void Move2Mouse() {
	using fnIssueMove = bool(__fastcall*)(uintptr_t, int x, int y, bool isAttackMove, int zeroOrOne, int order);
	if (POINT pos; GetCursorPos(&pos)) {
		auto hudInput = *(uintptr_t*)(*(uintptr_t*)oHudInstance + 0x28);
		((fnIssueMove)oIssueMove)(hudInput, pos.x, pos.y, false, 0, 1);
	}
}