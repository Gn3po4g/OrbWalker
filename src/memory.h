#pragma once

inline struct Offsets {
	DWORD_PTR oGameTime;
	DWORD_PTR oChatClient;
	DWORD_PTR oLocalPlayer;
	DWORD_PTR oHudInstance;
	DWORD_PTR oViewProjMatrices;
	DWORD_PTR oHeroList;
	DWORD_PTR oTurretList;
	DWORD_PTR oInhibitorList;
	DWORD_PTR oMinionList;
	DWORD_PTR oPrintChat;
	DWORD_PTR oIssueOrder;
	DWORD_PTR oGetAttackDelay;
	DWORD_PTR oGetAttackCastDelay;
	DWORD_PTR oIsAlive;
	DWORD_PTR oGetRadius;
} offsets;

class Memory {
	static PBYTE FindAddress(const string&);
	static void Scan(const bool);
public:
	static int* GameState;
	static void Initialize();
};
