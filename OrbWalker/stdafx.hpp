#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <dxgi.h>
#include <d3d11.h>

#include <algorithm>
#include <cstddef>
#include <format>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <span>
#include <sstream>
#include <string_view>
#include <vector>

#include "../Kiero/kiero.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_internal.h"
#include "../Imgui/imgui_impl_dx11.h"
#include "../Imgui/imgui_impl_win32.h"

#include "memory/offset.hpp"
#include "memory/spoofcall.h"
#include "util/constant.hpp"
#include "util/util.hpp"
#include "util/function.hpp"
#include "class/object.hpp"
#include "draw/render.hpp"
#include "draw/ui.hpp"
#include "agent/script.hpp"
#include "agent/hooks.hpp"
#include "config/config.hpp"

using namespace std::string_literals;