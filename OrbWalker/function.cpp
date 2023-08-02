#include "function.hpp"
#include <cstddef>
#include "offset.hpp"

fnPrintChat PrintChat{};
fnIssueOrder IssueOrder{};
fnAttackCastDelay AttackCastDelay{};
fnAttackDelay AttackDelay{};
fnIsAlive IsAlive{};
fnBonusRadius BonusRadius{};

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

void InitFunction()
{
	PrintChat = (fnPrintChat)offset.oPrintChat;
	IssueOrder = (fnIssueOrder)offset.oIssueOrder;
	AttackCastDelay = (fnAttackCastDelay)offset.oAttackCastDelay;
	AttackDelay = (fnAttackDelay)offset.oAttackDelay;
	IsAlive = (fnIsAlive)offset.oIsAlive;
	BonusRadius = (fnBonusRadius)offset.oBonusRadius;
	w2s = (W2S*)offset.oViewProjMatrices;
}

float GameTime() {
	return *(float*)offset.oGameTime;
}

bool IsChatOpen()
{
	return *(bool*)(*(uintptr_t*)offset.oChatClient + 0xC90);
}

bool IsLeagueInBackground()
{
	return *(bool*)(*(uintptr_t*)offset.oHudInstance + 0xB9);
}

void PrintMessage(std::string color, std::string text) {
	const auto wrapped = "<font color=" + color + '>' + text + "</font>";
	PrintChat(offset.oChatClient, wrapped.data(), 4);
}

DirectX::XMINT2 WorldToScreen(DirectX::XMFLOAT3 pos)
{
	using namespace DirectX;
	auto V = XMVectorSetW(XMLoadFloat3(&pos), 1.f);
	auto M = XMLoadFloat4x4(&w2s->view_matrix) * XMLoadFloat4x4(&w2s->proj_matrix);
	auto coord = XMVector3TransformCoord(V, M);
	return {
		(int)((1 + XMVectorGetX(coord)) / 2 * w2s->width),
		(int)((1 - XMVectorGetY(coord)) / 2 * w2s->height)
	};
}
