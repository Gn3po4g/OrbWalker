#pragma once

#include <DirectXMath.h>
#include "object.hpp"
#include <string>

using fnPrintChat = void(__fastcall*)(uintptr_t, const char*, int);
using fnIssueOrder = int(__fastcall*)(uintptr_t, int, int, int, int, int, int);
using fnAttackCastDelay = float(__fastcall*)(Object*);
using fnAttackDelay = float(__fastcall*)(Object*);
using fnIsAlive = bool(__fastcall*)(Object*);
using fnBonusRadius = float(__fastcall*)(Object*);

extern fnIssueOrder IssueOrder;
extern fnAttackCastDelay AttackCastDelay;
extern fnAttackDelay AttackDelay;
extern fnIsAlive IsAlive;
extern fnBonusRadius BonusRadius;
void InitFunction();
float GameTime();
bool IsChatOpen();
bool IsLeagueInBackground();
void PrintMessage(std::string, std::string);
DirectX::XMINT2 WorldToScreen(DirectX::XMFLOAT3);
