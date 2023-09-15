#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <Psapi.h>
#include <Windows.h>

#include <string_view>
#include <algorithm>
#include <cstddef>
#include <format>
#include <fstream>
#include <functional>
#include <map>
#include <ranges>
#include <set>
#include <span>
#include <sstream>
#include <string>
#include <vector>

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx11.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imgui_internal.h"
#include "../Kiero/kiero.h"

#include "agent/hooks.hpp"
#include "agent/script.hpp"
#include "agent/skinchanger.hpp"
#include "class/struct.hpp"
#include "config/config.hpp"
#include "draw/render.hpp"
#include "draw/ui.hpp"
#include "memory/function.hpp"
#include "memory/offset.hpp"
#include "memory/spoofcall.h"
#include "util/constant.hpp"
#include "util/fnvhash.hpp"
#include "util/json.hpp"
#include "util/util.hpp"

using json = nlohmann::json;
using namespace std::string_literals;