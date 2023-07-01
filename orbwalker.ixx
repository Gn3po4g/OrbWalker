export module OrbWalker;

export {
	enum class Type { AutoKite, CleanLane };
	bool* p_aco = nullptr;

	void InitOrb();
	void Execute(Type);
}