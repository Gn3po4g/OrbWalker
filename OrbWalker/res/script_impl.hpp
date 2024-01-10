#pragma once

/// Akshan
class Akshan : public script {
  bool is_attacking() override { return game_time < last_attack_time + Object::self()->AttackWindup() + 0.15; }
};

/// Aphelios
class Aphelios : public script {
  bool in_attack_range(Object *obj) override {
    if (obj->has_buff("ApheliosCalibrumBonusRangeDebuff"_FNV)) {
      return distance(obj->position(), Object::self()->position())
          <= 1800.f + Object::self()->BonusRadius() + obj->BonusRadius();
    }
    return distance(obj->position(), Object::self()->position()) <= real_range() + obj->BonusRadius();
  }
};

/// Azir
class Azir : public script {
  bool in_attack_range(Object *obj) override {
    return distance(obj->position(), Object::self()->position()) <= real_range() + obj->BonusRadius()
        || obj->type() != Turret && obj->type() != Inhibitor
             && std::ranges::any_of(
               ObjList::minions()->all() | std::views::filter([](Object *soldier) {
                 return soldier->name() == "AzirSoldier" && soldier->IsAlive()
                     && distance(soldier->position(), Object::self()->position())
                          <= Object::self()->BonusRadius() + 660.f + soldier->BonusRadius();
               }),
               [obj](Object *soldier) {
                 return distance(soldier->position(), obj->position()) <= soldier->attack_range();
               }
             );
  }
};

/// Caitlyn
class Caitlyn : public script {
  bool in_attack_range(Object *obj) override {
    if (obj->has_buff("CaitlynEMissile"_FNV) || obj->has_buff("CaitlynWSnare"_FNV)) {
      return distance(obj->position(), Object::self()->position())
          <= 1300.f + Object::self()->BonusRadius() + obj->BonusRadius();
    } else {
      return distance(obj->position(), Object::self()->position()) <= real_range() + obj->BonusRadius();
    }
  }
};

/// Graves
class Graves : public script {
public:
  bool is_reloading() override { return game_time < last_attack_time + Object::self()->AttackDelay() / 7; };
};

/// Kalista
class Kalista : public script {
  bool is_attacking() override { return false; };
};

/// Sett
class Sett : public script {
  bool is_reloading() override {
    static constexpr auto first_attack =
      std::to_array<std::string_view>({"SettBasicAttack", "SettBasicAttack3", "SettQAttack"});
    if (std::ranges::count(first_attack, last_cast_spell)) {
      return game_time < last_attack_time + Object::self()->AttackDelay() / 2.5;
    }
    return game_time < last_attack_time + Object::self()->AttackDelay();
  }
};