#pragma once

 #include "memory/offset.hpp"

class Graves : public script {
public:
  bool is_reloading() override { return false; };
};