#pragma once

#include "script.hpp"

#include "class/struct.hpp"

class Orb {
public:
  Object *markedObject;
  Object *self;
  ObjList *minions;
  ObjList *heros;
  ObjList *turrets;
  Script *script;

  enum class OrbState { Off, Kite, Clear } orbState;

  Orb();
  void update();

private:
  std::map<std::string_view, Script *> scripts{
    {"Ashe",       new Ashe()      },
    {"Cassiopeia", new Cassiopeia()},
    {"Graves",     new Graves()    },
    {"Kaisa",      new Kaisa()     },
    {"Zeri",       new Zeri()      }
  };

  void check_marked_object();
  void check_orb_state();
};

extern Orb *orb;