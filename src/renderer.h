#pragma once

#include "pad.h"

class Renderer {
private:
	XMFLOAT4X4 view_matrix;
	XMFLOAT4X4 proj_matrix;
	PAD(0x14);
	int width;
	int height;

public:
	XMINT2 WorldToScreen(const XMFLOAT3&) const;
};
