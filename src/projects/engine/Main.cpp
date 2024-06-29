#include "CAppWnd.h"
#include "CDirectX.h"
#include "GameUI/CGameUI.h"
//#include "CTextures.h"

const bool VSYNC_ENABLED = false;
const POINTS WINDOW_SIZE = { 730, 500 };

CGameUI* g_pGameUI = nullptr;
UINT g_ResizeWidth = 0, g_ResizeHeight = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_pGameUI->MsgProc(hWnd, uMsg, wParam, lParam))
    {
        return true;
    }

    switch (uMsg)
    {
        case WM_SIZE:
        {
            if (wParam == SIZE_MINIMIZED)
                return 0;

            g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
            g_ResizeHeight = (UINT)HIWORD(lParam);

            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        default:
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	CAppWnd* pAppWnd = new CAppWnd();
    CDirectX* pDirectX = new CDirectX();
    //CTextures* pTextures = new CTextures();
    g_pGameUI = new CGameUI();

    if (!pAppWnd->InitializeWindow(WndProc, hInstance, "ImMagic", "Magic001", { 100, 100 }, WINDOW_SIZE))
    {
        MessageBox(NULL, "Could not create window", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    pDirectX->Initialize(VSYNC_ENABLED, pAppWnd->GetWindow());
    //pTextures->Initialize(pDirectX->GetDevice());
    g_pGameUI->Initialize(pAppWnd->GetWindow(), pDirectX->GetDevice(), pDirectX->GetDeviceContext());

    pAppWnd->SetWindowState(SW_SHOWNORMAL);

    bool done = false;
    while (!done)
    {
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        pDirectX->SetBuffersSize(g_ResizeWidth, g_ResizeHeight);
        pDirectX->BeginScene(0, 0, 0, 0);
        g_pGameUI->Render();
        pDirectX->EndScene();
    }

    g_pGameUI->Shutdown();
    //pTextures->Shutdown();
    pDirectX->Shutdown();

    pAppWnd->ShutdownWindow();

    delete pAppWnd;
    delete pDirectX;
    //delete pTextures;
    delete g_pGameUI;

	return 0;
}