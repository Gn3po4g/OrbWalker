#include "pch.h"

void Renderer::Init() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.f;
			for (int k = 0; k < 4; k++) {
				sum = sum + viewMatrix.m[i][k] * projMatrix.m[k][j];
			}
			viewProjMatrix.m[i][j] = sum;
		}
	}
}

Vector2 Renderer::WorldToScreen(Vector3 pos) {
	Vector2 screen = { (float)width, (float)height };

	float x, y, z, w;
	x = pos.x * viewProjMatrix._11 + pos.y * viewProjMatrix._21 + pos.z * viewProjMatrix._31 + viewProjMatrix._41;
	y = pos.x * viewProjMatrix._12 + pos.y * viewProjMatrix._22 + pos.z * viewProjMatrix._32 + viewProjMatrix._42;
	z = pos.x * viewProjMatrix._13 + pos.y * viewProjMatrix._23 + pos.z * viewProjMatrix._33 + viewProjMatrix._43;
	w = pos.x * viewProjMatrix._14 + pos.y * viewProjMatrix._24 + pos.z * viewProjMatrix._34 + viewProjMatrix._44;

	if (w < 1.0f)w = 1.f;

	Vector2 M{ x / w,y / w };
	return { (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f) ,-(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f) };
}
