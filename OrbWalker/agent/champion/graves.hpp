#pragma once

 #include "memory/offset.hpp"

class Graves : public script {
public:
  bool is_reloading() override { return game_time < last_attack_time + self->AttackDelay() * .15f; };
};