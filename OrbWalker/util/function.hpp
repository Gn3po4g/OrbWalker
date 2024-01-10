#pragma once

template <typename T>
struct RiotArray {
  uptr unused;
  T *data;
  i32 size;
  i32 capacity;
};

struct RiotString8 {
  const char *m_str;
  i32 m_size;
  i32 m_capacity;

  std::string str() const { return std::string(m_str, m_size); }
};

struct RiotString16 {
  union {
    const char *p_str;
    const char m_str[16];
  };
  i64 m_size;
  i64 m_capacity;

  std::string str() const {
    if (m_size >= 16) return std::string(p_str, m_size);
    else return std::string((char*)this, m_size);
  }
};

class IMEMBER {
protected:
  template <typename Type>
  Type &MEMBER(auto offset) {
    return *std::bit_cast<Type *>(this + offset);
  }

  template <typename Type>
  Type *pMEMBER(auto offset) {
    return std::bit_cast<Type *>(this + offset);
  }
};

#include "agent/config.hpp"
#include "class/object.hpp"
#include "res/offset.hpp"

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmp_rbx_0[] = {0xff, 0x23}; // jmp qword ptr[rbx]

inline uptr RVA(uptr offset) {
  extern uptr base;
  return base + offset;
}

template <typename T>
T &Read(auto addr) {
  return *std::bit_cast<T *>(addr);
}

template <typename ReturnType>
ReturnType call_function(uintptr_t func, auto... args) {
  using func_t = ReturnType(__fastcall *)(decltype(args)...);
  return spoof_call((void *)jmp_rbx_0, (func_t)func, std::forward<decltype(args)>(args)...);
}

template <size_t Index, typename ReturnType>
ReturnType call_virtual(void *instance, auto... args) {
  using fn      = ReturnType(__fastcall *)(void *, decltype(args)...);
  auto function = (*std::bit_cast<fn **>(instance))[Index];
  return function(instance, std::forward<decltype(args)>(args)...);
}

class Chat : public IMEMBER {
public:
  static Chat &inst() {
    static std::once_flag singleton;
    std::call_once(singleton, [&] { instance_.reset(Read<Chat *>(RVA(oChatClient))); });
    return *instance_;
  }
  bool is_open() { return MEMBER<bool>(0x660); }
  static void print_message(u32 color, std::string_view msg) {
    const auto wrapped = std::format("<font color=#{:0>6x}>{}</font>", color & 0xFFFFFF, msg);
    call_function<void>(RVA(oPrintChat), RVA(oChatClient), wrapped.data(), 1u);
  }

private:
  Chat() = delete;
  inline static std::unique_ptr<Chat> instance_;
};

class HudMouse : public IMEMBER {
public:
  scrn &mouse_screen_pos() {
    const auto mouse = Read<uptr>(RVA(oMouseScreenPos));
    return Read<scrn>(mouse + 0xC);
  }
  vec3 &mouse_last_world() { return MEMBER<vec3>(0x38); }
};
class HudOrder {};
class HudCast {};

class Hud : public IMEMBER {
public:
  static Hud &inst() {
    static std::once_flag singleton;
    std::call_once(singleton, [&] { instance_.reset(Read<Hud *>(RVA(oHudInstance))); });
    return *instance_;
  }
  HudMouse *hud_mouse() { return MEMBER<HudMouse *>(0x28); }
  HudOrder *hud_order() { return MEMBER<HudOrder *>(0x48); }
  HudCast *hud_cast() { return MEMBER<HudCast *>(0x68); }
  bool is_background() { return MEMBER<bool>(0xB9); }
  bool &is_champion_only() { return Read<bool>(MEMBER<uptr>(0x60) + 0x30); }

private:
  Hud() = delete;
  inline static std::unique_ptr<Hud> instance_;
};

inline float distance(const vec3 &p1, const vec3 &p2) { return glm::distance(p1, p2); }

inline void *swap_chain() { return Read<void *>(call_function<uptr>(RVA(oMaterialRegistry)) + 0x1C0); }

inline float get_game_time() { return Read<float>(RVA(oGameTime)); }

inline float ping() { return call_function<u64>(RVA(oGetPing), Read<uptr>(RVA(oPingNet))) / 1000.f; }

inline std::optional<GameState> game_state() {
  auto addr = Read<uptr>(RVA(oGameState));
  return addr ? std::optional<GameState>(Read<GameState>(addr + 0xC)) : std::nullopt;
}

inline vec2 WorldToScreen(const vec3 &in) {
  const mat4 view_matrix      = Read<mat4>(RVA(oViewProjMatrix));
  const mat4 proj_matrix      = Read<mat4>(RVA(oViewProjMatrix) + 0x40);
  const glm::u32vec4 viewport = Read<glm::u32vec4>(RVA(oViewProjMatrix) + 0x8C);
  const mat4 adjust           = glm::scale(mat4(1.f), {1.f, -1.f, 1.f});
  vec3 projected              = glm::project(in, proj_matrix * view_matrix, adjust, viewport);
  return projected;
}

inline void AttackObject(Object *target) {
  const auto order = Hud::inst().hud_order();
  const auto pos   = scrn(WorldToScreen(target->position()));
  call_function<void>(RVA(oIssueOrder), order, 0, 2, 0, pos.x, pos.y, 2);
}

inline void Move2Mouse() {
  const auto mouse          = Hud::inst().hud_mouse();
  const scrn pos            = mouse->mouse_screen_pos();
  mouse->mouse_last_world() = {0.f, 0.f, 0.f};
  call_function<void>(RVA(oIssueMove), mouse, pos.x, pos.y, 0, 0, config::inst().show_click);
}

// void PressKeyAt(SpellSlot, const vec3 &);

inline void Draw(std::function<void()> draw_fun) {
  ImGuiIO &io{ImGui::GetIO()};

  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
  ImGui::PushStyleColor(ImGuiCol_WindowBg, {0.0f, 0.0f, 0.0f, 0.0f});
  ImGui::Begin("drawingwindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

  ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
  ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

  draw_fun();

  ImGui::GetWindowDrawList()->PushClipRectFullScreen();

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(2);
}

inline void Circle(const vec3 &center, float radius, u32 color, float thickness) {
  const size_t numPoints{314};
  ImVec2 points[numPoints]{};
  for (size_t i{0}; auto p : points) {
    const auto angle = 2 * IM_PI * i / numPoints;
    const auto v     = vec3(radius * cos(angle), 0, radius * sin(angle));
    const auto pos   = WorldToScreen(center + v);
    points[i++]      = {pos.x, pos.y};
  }
  ImGui::GetWindowDrawList()->AddPolyline(points, numPoints, color, true, thickness);
}