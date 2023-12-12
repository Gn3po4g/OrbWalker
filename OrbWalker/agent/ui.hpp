#pragma once

inline std::map<ImGuiKey, std::string> keyMap = {
  {ImGuiKey_None,           "None"          },
  {ImGuiKey_Tab,            "Tab"           },
  {ImGuiKey_LeftArrow,      "LeftArrow"     },
  {ImGuiKey_RightArrow,     "RightArrow"    },
  {ImGuiKey_UpArrow,        "UpArrow"       },
  {ImGuiKey_DownArrow,      "DownArrow"     },
  {ImGuiKey_PageUp,         "PageUp"        },
  {ImGuiKey_PageDown,       "PageDown"      },
  {ImGuiKey_Home,           "Home"          },
  {ImGuiKey_End,            "End"           },
  {ImGuiKey_Insert,         "Insert"        },
  {ImGuiKey_Delete,         "Delete"        },
  {ImGuiKey_Backspace,      "Backspace"     },
  {ImGuiKey_Space,          "Space"         },
  {ImGuiKey_Enter,          "Enter"         },
  {ImGuiKey_LeftCtrl,       "LeftCtrl"      },
  {ImGuiKey_LeftShift,      "LeftShift"     },
  {ImGuiKey_LeftAlt,        "LeftAlt"       },
  {ImGuiKey_LeftSuper,      "LeftSuper"     },
  {ImGuiKey_RightCtrl,      "RightCtrl"     },
  {ImGuiKey_RightShift,     "RightShift"    },
  {ImGuiKey_RightAlt,       "RightAlt"      },
  {ImGuiKey_RightSuper,     "RightSuper"    },
  {ImGuiKey_Menu,           "Menu"          },
  {ImGuiKey_0,              "0"             },
  {ImGuiKey_1,              "1"             },
  {ImGuiKey_2,              "2"             },
  {ImGuiKey_3,              "3"             },
  {ImGuiKey_4,              "4"             },
  {ImGuiKey_5,              "5"             },
  {ImGuiKey_6,              "6"             },
  {ImGuiKey_7,              "7"             },
  {ImGuiKey_8,              "8"             },
  {ImGuiKey_9,              "9"             },
  {ImGuiKey_A,              "A"             },
  {ImGuiKey_B,              "B"             },
  {ImGuiKey_C,              "C"             },
  {ImGuiKey_D,              "D"             },
  {ImGuiKey_E,              "E"             },
  {ImGuiKey_F,              "F"             },
  {ImGuiKey_G,              "G"             },
  {ImGuiKey_H,              "H"             },
  {ImGuiKey_I,              "I"             },
  {ImGuiKey_J,              "J"             },
  {ImGuiKey_K,              "K"             },
  {ImGuiKey_L,              "L"             },
  {ImGuiKey_M,              "M"             },
  {ImGuiKey_N,              "N"             },
  {ImGuiKey_O,              "O"             },
  {ImGuiKey_P,              "P"             },
  {ImGuiKey_Q,              "Q"             },
  {ImGuiKey_R,              "R"             },
  {ImGuiKey_S,              "S"             },
  {ImGuiKey_T,              "T"             },
  {ImGuiKey_U,              "U"             },
  {ImGuiKey_V,              "V"             },
  {ImGuiKey_W,              "W"             },
  {ImGuiKey_X,              "X"             },
  {ImGuiKey_Y,              "Y"             },
  {ImGuiKey_Z,              "Z"             },
  {ImGuiKey_F1,             "F1"            },
  {ImGuiKey_F2,             "F2"            },
  {ImGuiKey_F3,             "F3"            },
  {ImGuiKey_F4,             "F4"            },
  {ImGuiKey_F5,             "F5"            },
  {ImGuiKey_F6,             "F6"            },
  {ImGuiKey_F7,             "F7"            },
  {ImGuiKey_F8,             "F8"            },
  {ImGuiKey_F9,             "F9"            },
  {ImGuiKey_F10,            "F10"           },
  {ImGuiKey_F11,            "F11"           },
  {ImGuiKey_F12,            "F12"           },
  {ImGuiKey_Apostrophe,     "'"             },
  {ImGuiKey_Comma,          ","             },
  {ImGuiKey_Minus,          "-"             },
  {ImGuiKey_Period,         "."             },
  {ImGuiKey_Slash,          "/"             },
  {ImGuiKey_Semicolon,      ";"             },
  {ImGuiKey_Equal,          "="             },
  {ImGuiKey_LeftBracket,    "["             },
  {ImGuiKey_Backslash,      "\\"            },
  {ImGuiKey_RightBracket,   "]"             },
  {ImGuiKey_GraveAccent,    "`"             },
  {ImGuiKey_CapsLock,       "CapsLock"      },
  {ImGuiKey_ScrollLock,     "ScrollLock"    },
  {ImGuiKey_NumLock,        "NumLock"       },
  {ImGuiKey_PrintScreen,    "PrintScreen"   },
  {ImGuiKey_Pause,          "Pause"         },
  {ImGuiKey_Keypad0,        "Keypad0"       },
  {ImGuiKey_Keypad1,        "Keypad1"       },
  {ImGuiKey_Keypad2,        "Keypad2"       },
  {ImGuiKey_Keypad3,        "Keypad3"       },
  {ImGuiKey_Keypad4,        "Keypad4"       },
  {ImGuiKey_Keypad5,        "Keypad5"       },
  {ImGuiKey_Keypad6,        "Keypad6"       },
  {ImGuiKey_Keypad7,        "Keypad7"       },
  {ImGuiKey_Keypad8,        "Keypad8"       },
  {ImGuiKey_Keypad9,        "Keypad9"       },
  {ImGuiKey_KeypadDecimal,  "KeypadDecimal" },
  {ImGuiKey_KeypadDivide,   "KeypadDivide"  },
  {ImGuiKey_KeypadMultiply, "KeypadMultiply"},
  {ImGuiKey_KeypadSubtract, "KeypadSubtract"},
  {ImGuiKey_KeypadAdd,      "KeypadAdd"     },
  {ImGuiKey_KeypadEnter,    "KeypadEnter"   },
  {ImGuiKey_KeypadEqual,    "KeypadEqual"   },
  {ImGuiKey_MouseX1,        "MouseX1"       },
  {ImGuiKey_MouseX2,        "MouseX2"       }
};

namespace ui {
using namespace ImGui;
void LoadTheme();

void Update();

class wrapper {
public:
  wrapper() = delete;
  wrapper(bool ok) : m_ok(ok) {}
  void operator()(std::function<void()> then) {
    if (m_ok) then();
  }

protected:
  const bool m_ok;
};

class window : public wrapper {
public:
  window(const char *name, bool *p_open = nullptr, ImGuiWindowFlags flags = 0) : wrapper(Begin(name, p_open, flags)) {}
  ~window() { End(); }
};

class tab_bar : public wrapper {
public:
  tab_bar(const char *str_id, ImGuiTabBarFlags flags = 0) : wrapper(BeginTabBar(str_id, flags)) {}
  ~tab_bar() {
    if (m_ok) EndTabBar();
  }
};

class tab_item : public wrapper {
public:
  tab_item(const char *label, bool *p_open = nullptr, ImGuiTabItemFlags flags = 0)
      : wrapper(BeginTabItem(label, p_open, flags)) {}
  ~tab_item() {
    if (m_ok) EndTabItem();
  }
};

static inline void text(std::string_view text) { ImGui::TextUnformatted(text.data(), text.data() + text.size()); }

static inline void separator(std::string_view text) {
  ImGui::SeparatorText(text.data());
}
static inline void separator() { ImGui::Separator(); }

static inline bool hot_key(const char *label, ImGuiKey &key, const ImVec2 &size = {100.0f, 25.f}) {
  static std::map<ImGuiID, bool> activeMap;
  auto SetToPressedKey = [](ImGuiKey &key) {
    if (IsKeyPressed(ImGuiKey_Escape)) {
      key = ImGuiKey_None;
      return true;
    }
    for (const auto &key_in_map : keyMap | std::views::keys) {
      if (IsKeyPressed(key_in_map)) {
        key = key_in_map;
        return true;
      }
    }
    return false;
  };
  const auto id = GetID(label);
  AlignTextToFramePadding();
  text(label);
  SameLine(GetColumnWidth() - size.x);
  if (activeMap[id]) {
    PushStyleColor(ImGuiCol_Button, GetColorU32(ImGuiCol_ButtonActive));
    Button("...", size);
    PopStyleColor();
    if ((!IsItemHovered() && GetIO().MouseClicked[0]) || SetToPressedKey(key)) {
      activeMap[id] = false;
      return true;
    }
  } else if (Button(keyMap[key].data(), size)) {
    activeMap[id] = true;
  }
  return false;
}
} // namespace ui