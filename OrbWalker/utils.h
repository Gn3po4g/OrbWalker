#pragma once
#include "vector.h"

inline D3DMATRIX viewProjMatrix;
inline int width, height;

void Print(const char*);
float GetGameTime();
void SetViewProjMatrix();
Vector3 GetMouseWorldPosition();
Vector2 WorldToScreen(Vector3);
bool IsLeagueInForeground();
void Click(Vector2);
void Attack(Vector2);