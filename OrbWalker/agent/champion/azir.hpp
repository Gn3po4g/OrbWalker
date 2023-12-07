#pragma once

#include "agent/script.hpp"

class Azir : public script {
  bool in_attack_range(Object *obj) override {
    auto soldiers = ObjList::minions()->all() | std::views::filter([](Object *soldier) {
                      return soldier->name() == "AzirSoldier" && soldier->IsAlive()
                          && distance(soldier->position(), Object::self()->position())
                               <= Object::self()->BonusRadius() + 660.f + soldier->BonusRadius();
                    })
                  | std::ranges::to<std::vector>();
    return distance(obj->position(), Object::self()->position())
          <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius()
        || obj->type() != Turret && obj->type() != Inhibitor && std::ranges::any_of(soldiers, [obj](Object *soldier) {
             return distance(soldier->position(), obj->position()) <= soldier->attack_range();
           });
  }
};