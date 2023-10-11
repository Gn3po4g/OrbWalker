#pragma once

 #include "memory/global.hpp"

class Graves : public Script {
public:
  bool is_reloading() override { return game_time < last_attack_time + self->AttackDelay() * .15f; };
};