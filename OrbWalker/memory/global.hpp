#pragma once

#include "class/struct.hpp"

inline namespace global {
inline GameState *game_state{};
inline Object *self{};
inline ObjList *heros{};
inline ObjList *minions{};
inline ObjList *turrets{};
inline ObjList *inhibs{};
inline Object **objUnderMouse{};

void Init();
} // namespace global