struct INT2 {
  int x, y;

  ImVec2 ToImVec() const {
    return ImVec2(static_cast<float>(x), static_cast<float>(y));
  }
};

struct FLOAT3 {
  float x, y, z;

  float operator-(const FLOAT3 &other) {
    const float dx = x - other.x;
    const float dy = y - other.y;
    const float dz = z - other.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
  }
};

struct ByteWithMask {
  ByteWithMask() = default;
  ByteWithMask(int _b, bool _m) : _b(std::byte(_b)), _m(_m) {}

  friend bool operator==(const ByteWithMask &bwm, const uint8_t val) {
    return !bwm._m || bwm._b == std::byte(val);
  }

private:
  std::byte _b;
  bool _m;
};