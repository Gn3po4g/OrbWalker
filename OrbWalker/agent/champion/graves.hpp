#pragma once

class Graves : public script {
public:
  bool is_reloading() override { return game_time < last_attack_time + Object::self()->AttackDelay() / 7; };
};