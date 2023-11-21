#pragma once

#include "agent/script.hpp"

class Kalista : public script {
  bool is_attacking() override { return false; };
};