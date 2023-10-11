#pragma once

#include "agent/script.hpp"

class Kaisa : public Script {
  bool can_attack() override { return Script::can_attack() && !has_buff("KaisaE"); };
};