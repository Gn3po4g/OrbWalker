module;

#include <DirectXMath.h>

export module Object;

import std.core;

export {
	using DirectX::XMFLOAT3;
	using std::chrono::duration;
	using std::byte;

	class Object {
		byte pad0[0x3C];
		int32_t team; //0x003C
		byte pad1[0x1E0];
	public:
		XMFLOAT3 position; //0x0220
	private:
		byte pad2[0xE4];
		bool visible; //0x0310
		byte pad3[0xB9F];
		bool targetable; //0x0EB0
		byte pad4[0x1A7];
	public:
		float health; //0x1058/
	private:
		byte pad5[0x658];
		float attackrange; //0x16B4

	public:
		duration<float> acd();

		duration<float> ad();

		bool AttackableFor(Object *);

		bool InRangeOf(Object *);
	};

	Object *last_object = nullptr;

	class ObjList {
		byte pad0[0x8];
		Object **list;
		int size;
	public:
		Object *GetLowestHealth(Object *, bool);
	};
}