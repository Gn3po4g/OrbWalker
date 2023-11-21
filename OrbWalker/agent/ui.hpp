#pragma once

namespace ui {
inline void LoadTheme() {
  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
  colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
  colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
  colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

  ImGuiStyle &style = ImGui::GetStyle();
  style.WindowPadding = ImVec2(8.00f, 8.00f);
  style.FramePadding = ImVec2(5.00f, 2.00f);
  style.CellPadding = ImVec2(6.00f, 6.00f);
  style.ItemSpacing = ImVec2(6.00f, 6.00f);
  style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
  style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
  style.IndentSpacing = 25;
  style.ScrollbarSize = 15;
  style.GrabMinSize = 10;
  style.WindowBorderSize = 1;
  style.ChildBorderSize = 1;
  style.PopupBorderSize = 1;
  style.FrameBorderSize = 1;
  style.TabBorderSize = 1;
  style.WindowRounding = 7;
  style.ChildRounding = 4;
  style.FrameRounding = 3;
  style.PopupRounding = 4;
  style.ScrollbarRounding = 9;
  style.GrabRounding = 3;
  style.LogSliderDeadzone = 4;
  style.TabRounding = 4;
}
void Update();
} // namespace ui

namespace ImGui {

inline std::map<ImGuiKey, std::string_view> keyMap = {
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
  {ImGuiKey_Escape,         "Escape"        },
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

bool HotKey(const char *label, ImGuiKey &key, const ImVec2 &size = {100.0f, 0.0f});
} // namespace ImGui