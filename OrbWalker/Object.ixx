module;
#include <DirectXMath.h>
#include <chrono>
export module Object;

export {
	using DirectX::XMFLOAT3;
	using std::chrono::duration;

	class Object {
	public:
		XMFLOAT3 position();
		float health();
		duration<float> acd();
		duration<float> ad();
		bool AttackableFor(Object*);
		bool InRangeOf(Object*);
	};

	Object* last_object = nullptr;

	class ObjList {
	public:
		Object* GetLowestHealth(Object*, bool);
	};
}