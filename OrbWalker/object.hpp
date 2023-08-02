#pragma once

#include <DirectXMath.h>
#include <cstddef>

class Object
{
  std::byte pad0[0x3C];
  int32_t team; //0x003C
  std::byte pad1[0x1E0];

public:
  DirectX::XMFLOAT3 position; //0x0220
private:
  std::byte pad2[0xE4];
  bool visible; //0x0310
  std::byte pad3[0xB9F];
  bool targetable; //0x0EB0
  std::byte pad4[0x1A7];

public:
  float health; //0x1058/
private:
  std::byte pad5[0x658];
  float attackrange; //0x16B4
public:
  float acd();
  float ad();
  bool AttackableFor(Object*);
  bool InRangeOf(Object*);
};

extern Object* last_object;

class ObjList
{
  std::byte pad0[0x8];
  Object** list;
  int size;

public:
  Object* GetLowestHealth(Object*, bool);
};
