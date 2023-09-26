#pragma once

constexpr float interval = .033f;

class Script {
public:
  void update();
  virtual void extra_update();
  virtual bool can_attack();
  virtual bool can_do_action();
  virtual bool is_reloading();
  virtual bool is_attacking();
  virtual void idle();
  virtual void attack();
  virtual float draw_range();

protected:
  float game_time{};
  float last_attack_time{-FLT_MAX};
  float last_action_time{-FLT_MAX};
  uintptr_t last_spell_cast{};

  bool has_buff(std::string_view name);
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

class Zeri : public Script {
public:
  void extra_update() override{};
  bool can_attack() override;
  bool is_reloading() override;
  bool is_attacking() override { return false; };
  void attack() override;
  float draw_range() override;
};