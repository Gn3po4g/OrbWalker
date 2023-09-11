#include "stdafx.hpp"

namespace hooks {
  bool init = false;

  HRESULT(WINAPI *oPresent)
  (IDXGISwapChain *, UINT, UINT);

  HWND window{};
  ID3D11Device *pDevice{};
  ID3D11DeviceContext *pDeviceContext{};
  ID3D11RenderTargetView *pRenderTargetView{};

  HRESULT WINAPI Present(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags) {
    if(!init) {
      if(SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice))) {
        pDevice->GetImmediateContext(&pDeviceContext);
        DXGI_SWAP_CHAIN_DESC sd{};
        pSwapChain->GetDesc(&sd);
        window = sd.OutputWindow;
        ID3D11Texture2D *pBackBuffer{};
        pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
        if(!pBackBuffer) return oPresent(pSwapChain, SyncInterval, Flags);
        pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pRenderTargetView);
        pBackBuffer->Release();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = nullptr;//"window.ini";
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        //io.Fonts->AddFontFromFileTTF(SP_STRING("C:\\Windows\\Fonts\\Arial.ttf"), 14);

        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(pDevice, pDeviceContext);

        function::PrintMessage("#00FFFF", "Noroby's League of Legends script loaded");
        function::PrintMessage("#FF00FF", "Press DELETE to unload the script");

        init = true;
      } else {
        return oPresent(pSwapChain, SyncInterval, Flags);
      }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //ImGui::Begin("ImGui Window");
    //ImGui::End();

    render::Update();
    script::Update();

    ImGui::EndFrame();
    ImGui::Render();

    pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
  }

  void Init() {
    kiero::init(kiero::RenderType::D3D11);
    kiero::bind(8, (void **)&oPresent, Present);
  }

  void Shutdown() {
    kiero::unbind(8);
    kiero::shutdown();
    function::PrintMessage("#FF00FF", "Script unloaded");
  }
}// namespace hooks