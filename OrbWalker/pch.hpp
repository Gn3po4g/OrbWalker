#pragma once

#define NOMINMAX

#include <DirectXMath.h>
#include <Windows.h>
using vec3 = DirectX::XMFLOAT3;
using matrix = DirectX::XMFLOAT4X4;

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <format>
#include <fstream>
#include <map>
#include <mutex>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>
using namespace std::string_literals;
using namespace std::string_view_literals;

#include <MinHook.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>

#include "util/encryption.hpp"
#include "util/enum.hpp"
#include "util/fnvhash.hpp"
#include "util/json.hpp"
#include "util/util.hpp"