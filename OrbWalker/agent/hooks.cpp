#include "pch.hpp"

#include "hooks.hpp"

#include "agent/orb.hpp"
#include "agent/script.hpp"
#include "agent/skinchanger.hpp"
#include "config/config.hpp"
#include "draw/render.hpp"
#include "draw/ui.hpp"
#include "memory/function.hpp"

Hooks *hooks;

bool init = false;

HWND window{};
WNDPROC oWndProc{};

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if(ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ID3D11Device *pDevice{};
ID3D11DeviceContext *pDeviceContext{};
ID3D11RenderTargetView *pRenderTargetView{};
HRESULT(WINAPI *oPresent)(IDXGISwapChain *, UINT, UINT);

HRESULT WINAPI Present(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags) {
  if(!init) {
    if(SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice))) {
      pDevice->GetImmediateContext(&pDeviceContext);
      DXGI_SWAP_CHAIN_DESC sd{};
      pSwapChain->GetDesc(&sd);
      window = sd.OutputWindow;
      ID3D11Texture2D *pBackBuffer{};
      pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
      if(!pBackBuffer) { return oPresent(pSwapChain, SyncInterval, Flags); }
      pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
      pBackBuffer->Release();
      oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO &io = ImGui::GetIO();
      io.IniFilename = nullptr;
      io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
      io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\HarmonyOS_Sans_SC_Regular.ttf", 16, nullptr, io.Fonts->GetGlyphRangesChineseFull()
      );

      ImGui_ImplWin32_Init(window);
      ImGui_ImplDX11_Init(pDevice, pDeviceContext);

      function::PrintMessage("#00FFFF", "Noroby's League of Legends script loaded");
      function::PrintMessage("#FF00FF", "Press DELETE to unload the script");

      init = true;
    }
    return oPresent(pSwapChain, SyncInterval, Flags);
  }

  if(!function::IsChatOpen() && !function::IsLeagueInBackground()) {
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)) {
      SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)oWndProc);
      ImGui_ImplDX11_Shutdown();
      ImGui_ImplWin32_Shutdown();
      ImGui::DestroyContext();

      HRESULT result = oPresent(pSwapChain, SyncInterval, Flags);

      kiero::unbind(8);
      kiero::shutdown();
      pDevice->Release();
      function::PrintMessage("#FF00FF", "Script unloaded");
      hooks->cvRun.notify_all();

      return result;
    }
  }

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  orb->update();
  render::Update();
  ui::Update();
  skin::Update();

  ImGui::EndFrame();
  ImGui::Render();

  pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  return oPresent(pSwapChain, SyncInterval, Flags);
}

Hooks::Hooks() {
  config::Load();
  skin::Load();
  kiero::init(kiero::RenderType::D3D11);
  kiero::bind(8, (void **)&oPresent, Present);
}