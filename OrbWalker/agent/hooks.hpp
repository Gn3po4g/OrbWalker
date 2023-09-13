namespace hooks {
  extern bool running;
  
  void Init();
}// namespace hook

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);