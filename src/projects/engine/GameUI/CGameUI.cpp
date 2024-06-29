#include "CGameUI.h"

// Gui
#include "imgui.h"
#include "imgui_internal.h"

// Gui Backends
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

// Gui Addons
#include "imgui_freetype.h"

CGameUI::CGameUI()
{
}

CGameUI::~CGameUI()
{
}

bool CGameUI::Initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
    bool result = true;

    m_hWnd = hWnd;
    m_pDevice = pDevice;
    m_pDeviceContext = pDeviceContext;
    m_pGuiMgr = new CGuiMgr();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiStyle& style = ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.IniFilename = nullptr;                               // Disable INI File  
    GImGui->NavDisableHighlight = true;                     // Disable Highlighting

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Custom styles
    style.WindowRounding    = 0;
    style.ChildRounding     = 0;
    style.FrameRounding     = 0;
    style.GrabRounding      = 0;
    style.PopupRounding     = 0;
    style.TabRounding       = 0;
    style.ScrollbarRounding = 0;

    style.ButtonTextAlign   = { 0.5f, 0.5f };
    style.WindowTitleAlign  = { 0.5f, 0.5f };
    style.FramePadding      = { 6.0f, 6.0f };
    style.WindowPadding     = { 12.0f, 12.0f };
    style.ItemSpacing       = style.WindowPadding;
    style.ItemInnerSpacing  = { style.FramePadding.x, 2 };

    style.WindowBorderSize  = 0;
    style.FrameBorderSize   = 0;
    style.PopupBorderSize   = 0;

    style.ScrollbarSize     = 12.f;
    style.GrabMinSize       = 8.f;
    
    /*
    ImFontConfig cfg;
    cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_ForceAutoHint;
    io.Fonts->AddFontFromMemoryCompressedTTF(Poppins_Medium_compressed_data, Poppins_Medium_compressed_size, 16, &cfg, io.Fonts->GetGlyphRangesDefault());
    */

    // Setup Platform/Renderer backends
    result &= ImGui_ImplWin32_Init(hWnd);
    result &= ImGui_ImplDX11_Init(pDevice, pDeviceContext);

    m_pGuiMgr->RegisterPanels();

	return result;
}

void CGameUI::Shutdown()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void CGameUI::Render()
{
    BeginFrame();
    {
        m_pGuiMgr->Render();
        ImGui::ShowDemoWindow(nullptr);
    }
    EndFrame();
}

void CGameUI::BeginFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void CGameUI::EndFrame()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool CGameUI::MsgProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    return ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam);
}
