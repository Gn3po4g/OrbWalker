#include "pch.hpp"

#include <d3d11.h>

#include "agent/script.hpp"
#include "agent/ui.hpp"
#include "res/font.hpp"

class vmt_hook {
public:
  vmt_hook(void *base) : m_base((void ***)base) {
    m_old_vmt = *m_base;
    size_t size{};
    while (m_old_vmt[size] && !IsBadCodePtr((FARPROC)m_old_vmt[size])) { ++size; }
    m_new_vmt = (new void *[size + 1]) + 1;
    std::copy_n(m_old_vmt - 1, size + 1, m_new_vmt - 1);
    *m_base = m_new_vmt;
  }

  //~vmt_hook() {
  //  *m_base = m_old_vmt;
  //  delete[] (m_new_vmt - 1);
  //}

  template <typename T>
  void hook(size_t idx) {
    m_new_vmt[idx] = (void *)(&T::hooked);
    T::original    = reinterpret_cast<decltype(T::original)>(m_old_vmt[idx]);
  }

private:
  void ***m_base{};
  void **m_new_vmt{};
  void **m_old_vmt{};
};

HWND window{};
WNDPROC oWndProc{};
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

static LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
  return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

ID3D11Device *pDevice{};
ID3D11DeviceContext *pDeviceContext{};
ID3D11RenderTargetView *pRenderTargetView{};

static void init_all(IDXGISwapChain *pSwapChain) {
  pSwapChain->GetDevice(IID_PPV_ARGS(&pDevice));
  if (!pDevice) throw std::exception();
  pDevice->GetImmediateContext(&pDeviceContext);
  DXGI_SWAP_CHAIN_DESC sd;
  pSwapChain->GetDesc(&sd);
  window = sd.OutputWindow;
  ID3D11Texture2D *pBackBuffer;
  pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  if (!pBackBuffer) throw std::exception();
  pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
  pBackBuffer->Release();
  oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  auto &io       = ImGui::GetIO();
  io.IniFilename = nullptr;
  io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
  auto fonts     = io.Fonts;
  fonts->AddFontFromMemoryTTF((void *)font_data, font_data_size, 18, nullptr, fonts->GetGlyphRangesChineseFull());

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(pDevice, pDeviceContext);

  Chat::print_message(0x00FFFF, "Noroby's League of Legends script loaded");
}

static void do_in_present() {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  ui::inst().update();
  script::inst().update();

  ImGui::Render();

  pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

struct present {
  static HRESULT WINAPI hooked(IDXGISwapChain *p_swap_chain, UINT sync_interval, UINT flags) {
    static std::once_flag init;
    try {
      std::call_once(init, [&] { init_all(p_swap_chain); });
      do_in_present();
    } catch (...) {}
    return original(p_swap_chain, sync_interval, flags);
  }
  inline static decltype(&hooked) original{};
};

struct on_process_spell {
  static void __fastcall hooked(uptr thisptr, i32 arg, SpellCast *spell_cast, Object *obj) {
    if (arg == 0xC) script::inst().run(spell_cast, obj);
    return original(thisptr, arg, spell_cast, obj);
  }
  inline static decltype(&hooked) original{};
};

uptr base{};

void Hook() {
  base = (uptr)GetModuleHandle(nullptr);
  while (game_state() != Running) std::this_thread::sleep_for(std::chrono::milliseconds(500));
  if (!Object::self()) return;
  vmt_hook(swap_chain()).hook<present>(8);
  vmt_hook(Object::self()->ops_base()).hook<on_process_spell>(30);
}