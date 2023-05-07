#pragma once

enum class Type { AutoKite, CleanLane, LastHit };

namespace OrbWalker {
	extern bool* p_aco;
	void Initialize();
	void Execute(const Type&);
}