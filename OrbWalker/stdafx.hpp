#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <dxgi.h>
#include <d3d11.h>

#include <algorithm>
#include <cstddef>
#include <ranges>
#include <span>
#include <sstream>
#include <vector>

#include "../Kiero/kiero.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_internal.h"
#include "../Imgui/imgui_impl_dx11.h"
#include "../Imgui/imgui_impl_win32.h"

#include "util.hpp"
#include "object.hpp"
#include "function.hpp"
#include "offset.hpp"
#include "script.hpp"
#include "hooks.hpp"
#include "render.hpp"