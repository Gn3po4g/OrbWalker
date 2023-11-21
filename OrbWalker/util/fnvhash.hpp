#pragma once

using hash_type = u32;

template <hash_type basis = 0x811C9DC5, hash_type prime = 16777619>
struct fnv_hash {
  constexpr hash_type operator()(std::string_view str) {
    auto result{basis};
    for (const char &i : str) {
      result ^= to_lower(i);
      result *= prime;
    }
    return result;
  }

private:
  constexpr char to_lower(char c) { return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + 32) : c; }
};

inline auto FNV = fnv_hash();

constexpr hash_type operator""_FNV(const char *str, size_t size) { return FNV(std::string_view(str, size)); }