#pragma once
#include "objlist.h"
#include "object.h"

#define BASE (DWORD)GetModuleHandle(nullptr)

DWORD FindDevice(DWORD);
DWORD GetDeviceAddress(int);
Object* GetLocalPlayer();
ObjList* GetHeroList();
ObjList* GetTurretList();
ObjList* GetInhibitorList();
ObjList* GetMinionList();
float GetGameTime();
Vector3 GetMouseWorldPosition();
bool IsLeagueInForeground();
