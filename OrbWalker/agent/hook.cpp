#include "pch.hpp"

#include <d3d11.h>

#include "hook.hpp"

#include "agent/script.hpp"
#include "agent/skinchanger.hpp"
#include "agent/ui.hpp"
#include "memory/function.hpp"
#include "memory/offset.hpp"

hook &hook::inst() {
  static std::once_flag singleton;
  std::call_once(singleton, [&] { instance_.reset(new hook); });
  return *instance_;
}

std::once_flag init;

HWND window{};
WNDPROC oWndProc{};

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) { return true; }
  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ID3D11Device *pDevice{};
ID3D11DeviceContext *pDeviceContext{};
ID3D11RenderTargetView *pRenderTargetView{};

void init_all(IDXGISwapChain *pSwapChain) {
  pSwapChain->GetDevice(IID_PPV_ARGS(&pDevice));
  if (!pDevice) throw std::exception();
  pDevice->GetImmediateContext(&pDeviceContext);
  DXGI_SWAP_CHAIN_DESC sd{};
  pSwapChain->GetDesc(&sd);
  window = sd.OutputWindow;
  ID3D11Texture2D *pBackBuffer{};
  pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  if (!pBackBuffer) throw std::exception();
  pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
  pBackBuffer->Release();
  oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io    = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
  io.Fonts->AddFontFromFileTTF(
    R"(C:\Windows\Fonts\HarmonyOS_Sans_SC_Regular.ttf)", 18, nullptr, io.Fonts->GetGlyphRangesChineseFull()
  );
  ui::LoadTheme();

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(pDevice, pDeviceContext);

  PrintMessage<0x00FFFF>("Noroby's League of Legends script loaded");
}

void do_in_present() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  ui::Update();

  script::inst().update();
  skin::inst().update();

  ImGui::EndFrame();
  ImGui::Render();

  pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

struct present {
  static HRESULT WINAPI hooked(IDXGISwapChain *p_swap_chain, UINT sync_interval, UINT flags) {
    try {
      std::call_once(init, [&] { init_all(p_swap_chain); });
      do_in_present();
    } catch (...) {}
    return original(p_swap_chain, sync_interval, flags);
  }
  inline static decltype(&hooked) original{};
};

struct on_process_spell {
  static void __fastcall hooked(uintptr_t thisptr, int arg, SpellCast *spell_cast, Object *obj) {
    if (arg == 0xC) script::inst().run(spell_cast, obj);
    return original(thisptr, arg, spell_cast, obj);
  }
  inline static decltype(&hooked) original{};
};

struct get_cursor_pos {
  static BOOL WINAPI hooked(LPPOINT lpPoint) {
    auto org = original(lpPoint);
    if (hook::mMouseX != -1 && hook::mMouseY != -1) {
      lpPoint->x    = hook::mMouseX;
      lpPoint->y    = hook::mMouseY;
      hook::mMouseX = -1;
      hook::mMouseY = -1;
    }
    return org;
  }
  inline static decltype(&hooked) original{};
};

bool hook::install() {
  while (game_state() != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  if (!Object::self()) return false;
  static auto swap_chain_hook = new vmt_hook(swap_chain());
  swap_chain_hook->hook<present>(8);
  static auto on_process_spell_hook = new vmt_hook(Object::self()->ops_base());
  on_process_spell_hook->hook<on_process_spell>(30);
  static auto get_cursor_pos_hook = new mh_hook(GetCursorPos);
  get_cursor_pos_hook->hook<get_cursor_pos>();
  return true;
}