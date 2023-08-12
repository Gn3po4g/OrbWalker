#pragma once

#include <cstdint>

namespace offset {
	extern uintptr_t
		oGameTime,
		oLocalPlayer,
		oViewProjMatrices,
		oHeroList,
		oTurretList,
		oMinionList,
		oChatClient,
		oHudInstance,

		oPrintChat,
		oIssueOrder,
		oAttackDelay,
		oAttackWindup,
		oIsAlive,
		oBonusRadius;

	void Init();
};