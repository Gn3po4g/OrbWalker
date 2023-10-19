#pragma once

#include "class/obj_list.hpp"
#include "class/object.hpp"

inline namespace global {
inline void *swap_chain{};

inline std::unique_ptr<GameState> game_state;
inline std::unique_ptr<Object> self;
inline std::unique_ptr<ObjList> heros;
inline std::unique_ptr<ObjList> minions;
inline std::unique_ptr<ObjList> turrets;
inline std::unique_ptr<ObjList> inhibs;
inline std::unique_ptr<Object *> objUnderMouse;

inline void *vmt_in_obj{};

void Init();
} // namespace global