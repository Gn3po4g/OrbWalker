#pragma once

#include "agent/script.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"

class Azir : public script {
  bool in_attack_range(Object *obj) override {
    auto soldiers =
      std::span(minions->data, minions->size) | std::views::filter([](Object *soldier) {
        return soldier->name() == "AzirSoldier" && soldier->IsAlive()
            && soldier->position() - self->position() <= self->BonusRadius() + 660.f + soldier->BonusRadius();
      })
      | std::ranges::to<std::vector>();
    return obj->position() - self->position() <= self->attack_range() + self->BonusRadius() + obj->BonusRadius()
        || !obj->compare_type_flags(Building) && std::ranges::any_of(soldiers, [obj](Object *soldier) {
             return soldier->position() - obj->position() <= soldier->attack_range();
           });
  }
};