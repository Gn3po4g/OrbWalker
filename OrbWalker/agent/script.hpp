#pragma once

#include "class/struct.hpp"

constexpr float interval = .033f;

class Script {
public:
  Object *markedObject{};

  void update();
  virtual float draw_range();

protected:
  virtual void extra_update();
  virtual bool can_attack();
  virtual bool can_do_action();
  virtual bool is_reloading();
  virtual bool is_attacking();
  virtual void idle();
  virtual void attack();

  float game_time{};
  float last_attack_time{-FLT_MAX};
  float last_action_time{-FLT_MAX};
  enum class OrbState { Off, Kite, Clear } orbState{OrbState::Off};

  void check_marked_object();
  void check_orb_state();
  Object *get_target(float, bool);
  bool has_buff(std::string_view name);
};

extern Script *script;

void LoadScript();

class Ashe : public Script {
  void extra_update() override;
};

class Cassiopeia : public Script {
  void extra_update() override;
  bool can_attack() override;
  bool is_reloading() override;
  bool is_attacking() override { return false; };
  void attack() override;
  float draw_range() override;
};

class Graves : public Script {
public:
  bool is_reloading() override;
};

class Kaisa : public Script {
public:
  bool can_attack() override;
};

class Vayne : public Script {
public:
  void extra_update() override;
};

class Zeri : public Script {
public:
  void extra_update() override{};
  bool can_attack() override;
  bool is_reloading() override;
  bool is_attacking() override { return false; };
  void attack() override;
  float draw_range() override;
};