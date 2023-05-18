export module OrbWalker;

export {
	enum class Type { AutoKite, CleanLane };

	bool* p_aco;

	void InitOrb();
	void Execute(const Type&);
}