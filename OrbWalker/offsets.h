#pragma once
#include "framework.h"

extern DWORD oGameTime;
extern DWORD oChatClient;
extern DWORD oLocalPlayer;
extern DWORD oHudInstance;
extern DWORD oViewProjMatrices;
extern DWORD oHeroList;
extern DWORD oTurretList;
extern DWORD oInhibitorList;
extern DWORD oMinionList;

extern DWORD oPrintChat;
extern DWORD oIssueOrder;
extern DWORD oIsAlive;
extern DWORD oGetAttackDelay;
extern DWORD oGetAttackCastDelay;

struct OffsetSignature {
	std::string pattern;
	bool read;
	DWORD* offset;
};

BYTE* FindAddress(const std::string& pattern);
void Scan(bool);
