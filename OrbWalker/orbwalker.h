#pragma once

enum class Type { AutoKite, CleanLane, LastHit };

namespace OrbWalker {
	void Initialize();
	void execute(const Type&);
}