#pragma once

#include "defines.h"

class Renderer {
public:
	union {
		D3DMATRIX viewMatrix;
		DEFINE_MEMBER_N(D3DMATRIX, projMatrix, 0x40);
		DEFINE_MEMBER_N(int, width, 0x94);
		DEFINE_MEMBER_N(int, height, 0x98);
	};

	[[nodiscard]] constexpr D3DMATRIX Get() const
	{
		D3DMATRIX viewProjMatrix;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0.f;
				for (int k = 0; k < 4; k++) {
					sum += viewMatrix.m[i][k] * projMatrix.m[k][j];
				}
				viewProjMatrix.m[i][j] = sum;
			}
		}
		return viewProjMatrix;
	}

	[[nodiscard]] Vector2 WorldToScreen(Vector3 pos) const
	{
		const Vector2 screen = { static_cast<float>(width), static_cast<float>(height) };
		const auto viewProjMatrix = Get();
		const auto x = pos.x * viewProjMatrix._11 + pos.y * viewProjMatrix._21 + pos.z * viewProjMatrix._31 + viewProjMatrix._41;
		const auto y = pos.x * viewProjMatrix._12 + pos.y * viewProjMatrix._22 + pos.z * viewProjMatrix._32 + viewProjMatrix._42;
		auto w = pos.x * viewProjMatrix._14 + pos.y * viewProjMatrix._24 + pos.z * viewProjMatrix._34 + viewProjMatrix._44;
		if (w < 1.0f)w = 1.f;
		const Vector2 M{ x / w,y / w };
		return { (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f) ,-(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f) };
	}
};
