module;
#include <DirectXMath.h>
#include <chrono>
export module Object;

export {
	using DirectX::XMFLOAT3;
	using std::chrono::duration;

	class Object {
	public:
		XMFLOAT3 position() const;
		float health() const;
		duration<float> acd() const;
		duration<float> ad() const;
		bool AttackableFor(Object* const) const;
		bool InRangeOf(Object* const) const;
	};

	Object* last_object;

	class ObjList {
	public:
		Object* GetLowestHealth(Object* const, const bool) const;
	};
}