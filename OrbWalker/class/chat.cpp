#include "pch.hpp"

#include "chat.hpp"
#include "memory/offset.hpp"

Chat &Chat::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(Read<Chat *>(RVA(oChatClient))); });
  return *instance_;
}

bool Chat::is_open() { return MEMBER<bool>(0x660); }

void Chat::print_message(u32 color, std::string_view msg) {
  const auto wrapped = std::format("<font color=#{:0>6x}>{}</font>", color & 0xFFFFFF, msg);
  call_function<void>(RVA(oPrintChat), RVA(oChatClient), wrapped.data(), 1u);
}
