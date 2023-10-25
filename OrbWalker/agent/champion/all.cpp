#include "pch.hpp"

#include "agent/script.hpp"
#include "memory/offset.hpp"

#include "aphelios.hpp"
#include "azir.hpp"
#include "caitlyn.hpp"
#include "cassiopeia.hpp"
#include "graves.hpp"
#include "kaisa.hpp"
#include "sett.hpp"
#include "zeri.hpp"

script &script::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] {
    switch (FNV(self->name())) {
    case "Aphelios"_FNV:
      return instance_.reset(new Aphelios);
    case "Azir"_FNV:
      return instance_.reset(new Azir);
    case "Caitlyn"_FNV:
      return instance_.reset(new Caitlyn);
    //case "Cassiopeia"_FNV:
    //  return instance_.reset(new Cassiopeia);
    case "Graves"_FNV:
      return instance_.reset(new Graves);
    case "Kaisa"_FNV:
      return instance_.reset(new Kaisa);
    case "Sett"_FNV:
      return instance_.reset(new Sett);
    //case "Zeri"_FNV:
    //  return instance_.reset(new Zeri);
    default:
      return instance_.reset(new script);
    }
  });
  return *instance_;
}

void script::run(SpellCast *spell_cast, Object *obj) {
  if (spell_cast->is_attack()) last_attack_time = game_time;
  if (spell_cast->is_attack_reset()) last_attack_time = -FLT_MAX;
  // auto addr = *(void **)(*(uintptr_t *)spell_cast + 0x60);
  //  if (spell_cast->name() == "SivirW")
  //  MessageBoxA(nullptr, std::format("{:x}", (uintptr_t)spell_cast).c_str(), "", MB_OK);
}
