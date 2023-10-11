#include "pch.hpp"

#include "hook.hpp"

#include "agent/script.hpp"
#include "agent/skinchanger.hpp"
#include "agent/ui.hpp"
#include "config/config.hpp"
#include "memory/function.hpp"
#include "memory/global.hpp"

Hook *hook;

std::once_flag init;

HWND window{};
WNDPROC oWndProc{};

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if(ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ID3D11Device *pDevice{};
ID3D11DeviceContext *pDeviceContext{};
ID3D11RenderTargetView *pRenderTargetView{};

void init_all(IDXGISwapChain *pSwapChain) {
  pSwapChain->GetDevice(IID_PPV_ARGS(&pDevice));
  if(!pDevice) throw -1;
  pDevice->GetImmediateContext(&pDeviceContext);
  DXGI_SWAP_CHAIN_DESC sd{};
  pSwapChain->GetDesc(&sd);
  window = sd.OutputWindow;
  ID3D11Texture2D *pBackBuffer{};
  pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  if(!pBackBuffer) throw -1;
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

  config::Load();
  skin::Load();
  LoadScript();

  PrintMessage(0x00FFFF, "Noroby's League of Legends script loaded");
}

void do_in_present() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  script->update();
  ui::Update();
  skin::Update();

  ImGui::EndFrame();
  ImGui::Render();

  pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

struct present {
  static HRESULT WINAPI hooked(IDXGISwapChain *p_swap_chain, UINT sync_interval, UINT flags) {
    try {
      std::call_once(init, [&]() { init_all(p_swap_chain); });
      do_in_present();
    } catch(...) {}
    return original(p_swap_chain, sync_interval, flags);
  }
  inline static decltype(&hooked) original{};
};
vmt_hook *swap_chain_hook{};

struct on_process_spell {
  static void __fastcall hooked(__int64 thisptr, int arg, SpellCast *spell_cast, Object *obj) {
    if(arg == 0xc) script->run(spell_cast, obj);
    return original(thisptr, arg, spell_cast, obj);
  }
  inline static decltype(&hooked) original{};
};
vmt_hook *on_process_spell_hook{};

Hook::Hook() {
  swap_chain_hook = new vmt_hook(swap_chain);
  swap_chain_hook->hook<present>(8);
  on_process_spell_hook = new vmt_hook((void *)((uintptr_t)self + 0x1198));
  on_process_spell_hook->hook<on_process_spell>(30);
}