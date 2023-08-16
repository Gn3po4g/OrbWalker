class Object {
	template<typename T>
	T prop(uintptr_t offset) {
		return *(T*)((uintptr_t)this + offset);
	}
	int team();
	bool visible();
	bool targetable();
	float attackrange();
public:
	FLOAT3 position();
	float health();
	float AttackDelay();
	float AttackWindup();
	bool IsAlive();
	bool AttackableFor(Object*);
	bool InRangeOf(Object*);
};

extern Object* last_object;

class ObjList {
	template<typename T>
	T prop(uintptr_t offset) {
		return *(T*)((uintptr_t)this + offset);
	}
	Object** list();
	int size();
public:
	Object* GetLowestHealth(bool);
};
