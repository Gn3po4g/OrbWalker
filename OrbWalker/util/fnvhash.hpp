#pragma once

template <size_t basis = 0xcbf29ce484222325, size_t prime = 1099511628211>
struct fnv_hash {
  constexpr uint64_t operator()(std::string_view str) {
    auto result{basis};
    for (const char &i : str) {
      result ^= i;
      result *= prime;
    }
    return result;
  }
};

inline auto FNV = fnv_hash();

constexpr uint64_t operator""_FNV(const char *str, size_t size) { return FNV(std::string_view(str, size)); }