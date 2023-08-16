namespace script {
	enum class Type { AutoKite, CleanLane };

	Object* LocalPlayer();
	ObjList* Heroes();
	ObjList* Minions();
	ObjList* Turrets();

	void Execute(Type type);
}