#pragma once

#include "class/obj_list.hpp"
#include "class/object.hpp"

class script {
public:
  static script &inst();
  void update();
  virtual void run(SpellCast *, Object *);

protected:
  script() = default;

  virtual bool can_attack();
  virtual bool is_reloading();
  virtual bool is_attacking();
  virtual void idle();
  virtual void attack();
  virtual float real_range();
  virtual bool in_attack_range(Object *);

  float game_time{};
  float last_attack_time{-FLT_MAX};
  float end_attack_time{-FLT_MAX};
  std::string last_cast_spell;
  Object *markedObject{};
  enum class OrbState { Off, Kite, Clear } orbState{OrbState::Off};

  void do_action(std::function<void()> fun);
  void check_marked_object();
  void check_orb_state();
  bool in_skill_range(Object *, float);
  Object *get_attack_target();
  Object *get_skill_target(float);

private:
  inline static std::unique_ptr<script> instance_;
};