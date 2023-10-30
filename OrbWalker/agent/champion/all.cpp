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
    case "Cassiopeia"_FNV:
      return instance_.reset(new Cassiopeia);
    case "Graves"_FNV:
      return instance_.reset(new Graves);
    case "Kaisa"_FNV:
      return instance_.reset(new Kaisa);
    case "Sett"_FNV:
      return instance_.reset(new Sett);
    case "Zeri"_FNV:
      return instance_.reset(new Zeri);
    default:
      return instance_.reset(new script);
    }
  });
  return *instance_;
}