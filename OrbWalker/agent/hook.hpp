#pragma once

class hook {
public:
  static hook &inst();
  void install();

  inline static std::mutex mRun;
  inline static int mMouseX{-1}, mMouseY{-1};

private:
  hook() = default;
  inline static std::unique_ptr<hook> instance_;
};

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);