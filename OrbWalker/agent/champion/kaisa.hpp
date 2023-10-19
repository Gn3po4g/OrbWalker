#pragma once

#include "agent/script.hpp"

class Kaisa : public script {
  bool can_attack() override { return script::can_attack() && !has_buff(self.get(), "KaisaE"); };
};