#pragma once

#include <DirectXMath.h>
#include "object.hpp"
#include <string>

float GameTime();
bool IsChatOpen();
bool IsLeagueInBackground();
void PrintMessage(std::string, std::string);
DirectX::XMINT2 WorldToScreen(DirectX::XMFLOAT3);
void Attack(Object*, Object*);
void Move2Mouse();