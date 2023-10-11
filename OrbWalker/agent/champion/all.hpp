#pragma once

#include "aphelios.hpp"
#include "ashe.hpp"
#include "cassiopeia.hpp"
#include "graves.hpp"
#include "kaisa.hpp"
#include "lucian.hpp"
#include "vayne.hpp"
#include "zeri.hpp"

constexpr Script *get_script(std::string_view name) {
  if(name == "Aphelios") return new Aphelios();
  else if(name == "Ashe") return new Ashe();
  else if(name == "Cassiopeia") return new Cassiopeia();
  else if(name == "Graves") return new Graves();
  else if(name == "Lucian") return new Lucian();
  else if(name == "Kaisa") return new Kaisa();
  else if(name == "Vayne") return new Vayne();
  else if(name == "Zeri") return new Zeri();
  else return new Script();
};