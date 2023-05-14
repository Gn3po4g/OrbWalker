#pragma once

enum class Type { AutoKite, CleanLane };

namespace OrbWalker {
	extern bool* p_aco;
	void Initialize();
	void Execute(const Type&);
}