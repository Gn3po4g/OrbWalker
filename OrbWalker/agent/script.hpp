#pragma once

#include "class/object.hpp"

constexpr float interval = 1.f / 30;

class script {
public:
  static script &inst();
  void update();
  virtual void run(SpellCast *spell_cast, Object *obj);

protected:
  script() = default;

  virtual bool can_attack();
  virtual bool can_do_action();
  virtual bool is_reloading();
  virtual bool is_attacking();
  virtual void idle();
  virtual void attack();
  virtual float real_range();

  float game_time{};
  float last_attack_time{-FLT_MAX};
  float last_action_time{-FLT_MAX};
  Object *markedObject{};
  enum class OrbState { Off, Kite, Clear } orbState{OrbState::Off};

  void check_marked_object();
  void check_orb_state();
  Object *get_target(float, bool);
  bool has_buff(std::string_view);

private:
  inline static std::unique_ptr<script> instance_;
};