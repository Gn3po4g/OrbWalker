#include "pch.hpp"

#include "agent/script.hpp"
#include "memory/global.hpp"

#include "aphelios.hpp"
#include "azir.hpp"
#include "caitlyn.hpp"
#include "cassiopeia.hpp"
#include "graves.hpp"
#include "kaisa.hpp"
#include "sett.hpp"
#include "zeri.hpp"

constexpr auto reset_attack_spells = std::to_array<std::string_view>(
  {"ApheliosCrescendumAttack", "AsheQ", "DariusNoxianTacticsONH", "LucianE", "SivirW", "JaxW", "VayneTumble"}
);

script &script::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] {
    switch (FNV(self->name())) {
    case "Aphelios"_FNV:
      instance_.reset(new Aphelios);
      break;
    case "Azir"_FNV:
      instance_.reset(new Azir);
      break;
    case "Caitlyn"_FNV:
      instance_.reset(new Caitlyn);
      break;
    case "Cassiopeia"_FNV:
      instance_.reset(new Cassiopeia);
      break;
    case "Graves"_FNV:
      instance_.reset(new Graves);
      break;
    case "Kaisa"_FNV:
      instance_.reset(new Kaisa);
      break;
    case "Sett"_FNV:
      instance_.reset(new Sett);
      break;
    case "Zeri"_FNV:
      instance_.reset(new Zeri);
      break;
    default:
      instance_.reset(new script);
    }
  });
  return *instance_;
}

void script::run(SpellCast *spell_cast, Object *obj) {
  if (spell_cast->is_attack()) last_attack_time = game_time;
  if (std::ranges::count(reset_attack_spells, spell_cast->name())) last_attack_time = -FLT_MAX;
  // PrintMessage(0xFFFFFF, std::format("{:x}", (uintptr_t)spell_cast));
  // PrintMessage(0xFFFFFF, std::format("{:x}", spell_cast->slot()));
  // PrintMessage(0xFFFFFF, std::format("{}", spell_cast->name()));
}
