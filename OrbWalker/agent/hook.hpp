#pragma once

class hook {
public:
  static hook &inst();
  void install();

  inline static std::mutex mRun;
  //std::condition_variable cvRun;

private:
  hook() = default;
  inline static std::unique_ptr<hook> instance_;
};

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);