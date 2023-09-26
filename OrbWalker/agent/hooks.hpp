#pragma once

class Hooks {
public:
  std::mutex mRun;
  std::condition_variable cvRun;

  Hooks();
};

extern Hooks *hooks;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);