#pragma once

#define NOMINMAX
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <Windows.h>

#include <algorithm>
#include <cstddef>
#include <format>
#include <fstream>
#include <functional>
#include <map>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <thread>
#include <vector>
using namespace std::string_literals;
using namespace std::string_view_literals;

// #include <MinHook.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using mat4 = glm::mat4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using scrn = glm::i32vec2;

#include "spoof_call.h"

#include "util/encryption.hpp"
#include "util/enum.hpp"
#include "util/fnvhash.hpp"
#include "util/function.hpp"
#include "util/json.hpp"