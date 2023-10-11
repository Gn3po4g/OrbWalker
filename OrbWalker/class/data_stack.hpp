#pragma once

class DataStack {
public:
  class Data {
  public:
    RiotString8 model;
    char pad0[0x10];
    int32_t skin;
    char pad1[0x60];
    int8_t gear;
    char pad2[0x7];
  };

  std::vector<Data> stack;
  Data baseSkin;

  void update(bool);
  void push(const char *, int32_t);
};