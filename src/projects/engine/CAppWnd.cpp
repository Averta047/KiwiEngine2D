#include "CAppWnd.h"
#include <dwmapi.h>

CAppWnd::CAppWnd()
{
    m_hWnd = 0;
}

CAppWnd::~CAppWnd()
{
}

bool CAppWnd::InitializeWindow(WNDPROC WndProc, HINSTANCE instance, const char* title, const char* wnd_class, POINTS position, POINTS size)
{
    m_WndClass = { 0 };
    m_WndClass.lpfnWndProc = WndProc;
    m_WndClass.hInstance = instance;
    m_WndClass.lpszClassName = wnd_class;
    RegisterClassA(&m_WndClass);

    m_hWnd = CreateWindowExA(0, m_WndClass.lpszClassName, title, WS_POPUP, position.x, position.y, size.x, size.y, NULL, NULL, m_WndClass.hInstance, NULL);
    if (m_hWnd == NULL)
    {
        return false;
    }

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(m_hWnd, &margins);

	return true;
}

void CAppWnd::SetWindowState(int nCmdShow)
{
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);
}

void CAppWnd::ShutdownWindow()
{
    ::DestroyWindow(m_hWnd);
    ::UnregisterClassA(m_WndClass.lpszClassName, m_WndClass.hInstance);
}