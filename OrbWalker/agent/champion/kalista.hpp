#pragma once

#include "agent/script.hpp"

class Kalista : public script {
  bool is_attacking() override { return game_time < last_attack_time + interval * 5; };
};