module;
#include <DirectXMath.h>
module Function;
import Offset;

using namespace DirectX;

XMFLOAT4X4* view_matrix;
XMFLOAT4X4* proj_matrix;
int* width;
int* height;

void InitFunction() {
	PrintChat = (fnPrintChat)offset.oPrintChat;
	IssueOrder = (fnIssueOrder)offset.oIssueOrder;
	GetAttackCastDelay = (fnGetAttackCastDelay)offset.oGetAttackCastDelay;
	GetAttackDelay = (fnGetAttackDelay)offset.oGetAttackDelay;
	IsAlive = (fnIsAlive)offset.oIsAlive;
	GetRadius = (fnGetRadius)offset.oGetRadius;
	view_matrix = (XMFLOAT4X4*)(offset.oViewProjMatrices + 0x00);
	proj_matrix = (XMFLOAT4X4*)(offset.oViewProjMatrices + 0x40);
	width = (int*)(offset.oViewProjMatrices + 0x94);
	height = (int*)(offset.oViewProjMatrices + 0x98);
}

bool IsChatOpen() {
	return *(bool*)(*(uintptr_t*)offset.oChatClient + 0xC90);
}

bool IsLeagueInBackground() {
	return *(bool*)(*(uintptr_t*)offset.oHudInstance + 0xB9);
}

XMINT2 WorldToScreen(const XMFLOAT3 pos) {
	FXMVECTOR V = XMVectorSetW(XMLoadFloat3(&pos), 1.f);
	FXMMATRIX M = XMLoadFloat4x4(view_matrix) * XMLoadFloat4x4(proj_matrix);
	FXMVECTOR coord = XMVector3TransformCoord(V, M);
	return {
		(int)((1 + XMVectorGetX(coord)) / 2 * *width),
		(int)((1 - XMVectorGetY(coord)) / 2 * *height)
	};
}