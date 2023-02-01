#include "pch.h"

Functions::Functions() {
	PrintChat = funcTypes::fnPrintChat(oPrintChat);
	IssueOrder = funcTypes::fnIssueOrder(oIssueOrder);
	GetAttackCastDelay = funcTypes::fnGetAttackCastDelay(oGetAttackCastDelay);
	GetAttackDelay = funcTypes::fnGetAttackDelay(oGetAttackDelay);
	IsAlive = funcTypes::fnIsAlive(oIsAlive);
}

std::unique_ptr<Functions> functions;