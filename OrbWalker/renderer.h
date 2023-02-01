#pragma once

#include "defines.h"

class Renderer {
private:
	union {
		D3DMATRIX viewMatrix;
		DEFINE_MEMBER_N(D3DMATRIX, projMatrix, 0x40);
		DEFINE_MEMBER_N(int, width, 0x94);
		DEFINE_MEMBER_N(int, height, 0x98);
	};
public:
	constexpr D3DMATRIX Get();
	Vector2 WorldToScreen(Vector3);
};
