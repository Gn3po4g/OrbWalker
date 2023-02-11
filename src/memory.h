#pragma once

inline struct Offsets {
	PBYTE oGameState;

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
	PBYTE oGetRadius;
} offsets;

class Memory {
	std::tuple<PBYTE*, std::string, bool > sig_to_scan[14]{};

	PBYTE FindAddress(const std::string&) const;
	void Scan(const bool);
public:
	Memory();
};
