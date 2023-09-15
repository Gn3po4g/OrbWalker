#include "stdafx.hpp"

void DataStack::update(bool change) {
  using fnUpdate = int64_t(__fastcall *)(DataStack *, bool);
  ((fnUpdate)(offset::oDataStackUpdate))(this, change);
}

void DataStack::push(const char *model, int32_t skin) {
  using fnPush = int64_t(__fastcall *)(DataStack *, const char *, int32_t, int32_t, bool, bool, bool, bool, bool, bool, int8_t, const char *, int32_t, const char *, int32_t, bool, int32_t);
  ((fnPush)(offset::oDataStackPush))(this, model, skin, 0, false, false, false, false, true, false, -1, "\x00", 0, "\x00", 0, false, 1);
}