#include "pch.h"

Functions::Functions() {
	IssueOrder = reinterpret_cast<funcTypes::fnIssueOrder>(BASE + offsets::oIssueOrder);
	GetAttackCastDelay = reinterpret_cast<funcTypes::fnGetAttackCastDelay>(BASE + offsets::oGetAttackCastDelay);
	GetAttackDelay = reinterpret_cast<funcTypes::fnGetAttackDelay>(BASE + offsets::oGetAttackDelay);
	IsAlive = reinterpret_cast<funcTypes::fnIsAlive>(BASE + offsets::oIsAlive);
}

std::unique_ptr<Functions> functions;