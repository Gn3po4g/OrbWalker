#include "pch.hpp"

#include "agent/script.hpp"
#include "memory/global.hpp"

#include "cassiopeia.hpp"
#include "graves.hpp"
#include "kaisa.hpp"
#include "zeri.hpp"

constexpr auto reset_attack_spells = std::to_array<std::string_view>({
  "ApheliosCrescendumAttack", "AsheQ", "LucianE", "VayneTumble"
});

script &script::inst() {
  static std::once_flag singleton;
  std::call_once(
    singleton,
    [&] {
      switch(FNV(self->name().data())) {
      case FNVC("Cassiopeia"):
        instance_.reset(new Cassiopeia);
        break;
      case FNVC("Graves"):
        instance_.reset(new Graves);
        break;
      case FNVC("Kaisa"):
        instance_.reset(new Kaisa);
        break;
      case FNVC("Zeri"):
        instance_.reset(new Zeri);
        break;
      default:
        instance_.reset(new script);
        break;
      }
    });
  return *instance_;
}

void script::run(SpellCast *spell_cast, Object *obj) {
  if(spell_cast->is_attack()) last_attack_time = game_time;
  if(std::ranges::count(reset_attack_spells, spell_cast->name())) last_attack_time = -FLT_MAX;
  // PrintMessage(0xFFFFFF, std::format("{:x}", (uintptr_t)spell_cast));
  // PrintMessage(0xFFFFFF, std::format("{:x}", spell_cast->slot()));

  // PrintMessage(0xFFFFFF, std::format("{}", spell_cast->name()));
}
