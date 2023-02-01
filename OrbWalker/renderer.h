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
	D3DMATRIX viewProjMatrix;
public:
	void Init();
	Vector2 WorldToScreen(Vector3);
};
