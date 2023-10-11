#pragma once

class Hook {
public:
  std::mutex mRun;
  std::condition_variable cvRun;

  Hook();
};

extern Hook *hook;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);