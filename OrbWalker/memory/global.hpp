#pragma once

#include <dxgi.h>

#include "class/object.hpp"
#include "class/obj_list.hpp"

inline namespace global {
inline IDXGISwapChain* swap_chain{};

inline GameState *game_state{};
inline Object *self{};
inline ObjList *heros{};
inline ObjList *minions{};
inline ObjList *turrets{};
inline ObjList *inhibs{};
inline Object **objUnderMouse{};

void Init();
} // namespace global