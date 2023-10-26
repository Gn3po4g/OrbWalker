#include "pch.hpp"

#include "data_stack.hpp"

#include "memory/function.hpp"
#include "memory/offset.hpp"

void DataStack::update(bool change) { call_function<void>(RVA(oDataStackUpdate), this, change); }

void DataStack::push(std::string_view model, int32_t skin) {
  call_function<void>(
    RVA(oDataStackPush), this, model.data(), skin, 0, false, false, false, false, true, false, -1i8, "\x00", 0, "\x00",
    0, false, 1
  );
}