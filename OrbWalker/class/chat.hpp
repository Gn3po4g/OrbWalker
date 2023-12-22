#pragma once

class Chat : public IMEMBER {
public:
  static Chat &inst();
  bool is_open();
  static void print_message(u32, std::string_view);

private:
  inline static std::unique_ptr<Chat> instance_;
};