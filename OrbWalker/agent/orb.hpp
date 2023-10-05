#pragma once

#include "script.hpp"

#include "class/struct.hpp"

class Orb {
public:
  Object *markedObject;
  Script *script;
  enum class OrbState { Off, Kite, Clear } orbState;

  Orb();
  void update();

private:
  void check_marked_object();
  void check_orb_state();
};

extern Orb *orb;