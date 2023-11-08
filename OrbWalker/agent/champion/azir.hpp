#pragma once

#include "agent/script.hpp"

class Azir : public script {
  bool in_attack_range(Object *obj) override {
    auto soldiers = std::span(ObjList::minions()->data, ObjList::minions()->size)
                  | std::views::filter([](Object *soldier) {
                      return soldier->name() == "AzirSoldier" && soldier->IsAlive()
                          && soldier->position() - Object::self()->position()
                               <= Object::self()->BonusRadius() + 660.f + soldier->BonusRadius();
                    })
                  | std::ranges::to<std::vector>();
    return obj->position() - Object::self()->position()
          <= Object::self()->attack_range() + Object::self()->BonusRadius() + obj->BonusRadius()
        || !obj->compare_type_flags(Building) && std::ranges::any_of(soldiers, [obj](Object *soldier) {
             return soldier->position() - obj->position() <= soldier->attack_range();
           });
  }
};