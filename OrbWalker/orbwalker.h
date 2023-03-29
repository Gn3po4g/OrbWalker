#pragma once

enum class Type { AutoKite, CleanLane, LastHit };

namespace OrbWalker {
	extern bool* pAttackChampionsOnly;

	void Initialize();
	void Execute(Type);
}