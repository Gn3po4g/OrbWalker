#pragma once

#include <Windows.h>

#include <Psapi.h>
#include <d3d11.h>
#include <dxgi.h>

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <map>
#include <mutex>
#include <ranges>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_dx11.h"
#include "../Imgui/imgui_impl_win32.h"
#include "../Imgui/imgui_internal.h"
#include "../Kiero/kiero.h"

#include "util/constant.hpp"
#include "util/fnvhash.hpp"
#include "util/json.hpp"
#include "util/util.hpp"

using json = nlohmann::json;
using namespace std::string_literals;
using namespace std::string_view_literals;