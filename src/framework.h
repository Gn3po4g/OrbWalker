#pragma once

#define WIN32_LEAN_AND_MEAN

#include <directxmath.h>
#include <windows.h>
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <memory>
#include <ranges>
#include <sstream>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

using namespace std::chrono_literals;
using namespace DirectX;

#define CONCAT(a, b) a##b
#define PAD_NAME(n) CONCAT(pad, n)
#define PAD(size) std::byte PAD_NAME(__LINE__)[size];