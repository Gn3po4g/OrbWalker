#pragma once

inline struct Offsets {
	PBYTE oGameState;
	PBYTE oGameTime;
	PBYTE oChatClient;
	PBYTE oLocalPlayer;
	PBYTE oHudInstance;
	PBYTE oViewProjMatrices;
	PBYTE oHeroList;
	PBYTE oTurretList;
	PBYTE oInhibitorList;
	PBYTE oMinionList;
	PBYTE oPrintChat;
	PBYTE oIssueOrder;
	PBYTE oGetAttackDelay;
	PBYTE oGetAttackCastDelay;
	PBYTE oIsAlive;
} offsets;

class Memory {
	std::array<std::tuple<PBYTE*, std::string, bool>, 14> sig_to_scan;

	PBYTE FindAddress(const std::string&);
public:
	Memory();
	void Scan(const bool);
};