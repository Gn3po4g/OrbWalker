#pragma once

enum class Type { AutoKite, CleanLane };

extern bool* p_aco;

void InitOrb();
void Execute(Type);
