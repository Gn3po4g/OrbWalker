#pragma once
#include "framework.h"

namespace offsets {
	extern DWORD oGameTime;
	extern DWORD oLocalPlayer;
	extern DWORD oHudInstance;
	extern DWORD oHeroList;
	extern DWORD oTurretList;
	extern DWORD oInhibitorList;
	extern DWORD oMinionList;

	extern DWORD oIssueOrder;
	extern DWORD oIsAlive;
	extern DWORD oGetAttackDelay;
	extern DWORD oGetAttackCastDelay;
}

struct OffsetSignature {
	std::string pattern;
	bool read;
	DWORD* offset;
};

extern std::vector<OffsetSignature> signaturesToScan;

BYTE* FindAddress(const std::string& pattern);
void Scan();
