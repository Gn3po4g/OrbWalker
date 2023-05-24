module;
#include <DirectXMath.h>
#include <chrono>
export module Object;

export {
	using DirectX::XMFLOAT3;
	using std::chrono::duration;
	using std::byte;

	class Object {
	private:
		byte pad13[60];
		int32_t team; //0x003C
		byte pad15[480];
	public:
		XMFLOAT3 position; //0x0220
	private:
		byte pad19[228];
		bool visible; //0x0310
		byte pad21[2975];
		bool targetable; //0x0EB0
		byte pad23[443];
	public:
		float health; //0x106C
	private:
		byte pad27[1620];
		float attackrange; //0x16C4

	public:
		duration<float> acd();
		duration<float> ad();
		bool AttackableFor(Object*);
		bool InRangeOf(Object*);
	};

	Object* last_object = nullptr;

	class ObjList {
	private:
		byte pad41[0x8];
		Object** list;
		int size;
	public:
		Object* GetLowestHealth(Object*, bool);
	};
}