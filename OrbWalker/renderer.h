#pragma once

#include "pad.h"

using namespace DirectX;

class Renderer {
	XMMATRIX viewMatrix;
	XMMATRIX projMatrix;
	PAD(0x14);
private:
	int width;
	int height;

public:
	XMINT2 WorldToScreen(const XMFLOAT3&) const;
};
