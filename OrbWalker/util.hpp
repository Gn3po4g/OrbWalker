struct INT2 {
  int x, y;
};

struct FLOAT3 {
  float x, y, z;
};

struct ByteWithMask {
  ByteWithMask() = default;
  ByteWithMask(int _b, bool _m) : _b(std::byte(_b)), _m(_m) {}

  bool operator==(int val) { return !_m || _b == std::byte(val); }

private:
  std::byte _b;
  bool _m;
};