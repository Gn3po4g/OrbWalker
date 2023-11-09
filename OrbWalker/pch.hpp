#pragma once

#define NOMINMAX

#include <Windows.h>

#include <algorithm>
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

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <MinHook.h>

#include "util/enum.hpp"
#include "util/fnvhash.hpp"
#include "util/json.hpp"
#include "util/util.hpp"
#include "util/encryption.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;