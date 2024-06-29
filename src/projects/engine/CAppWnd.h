#pragma once

#include <Windows.h>

class CAppWnd
{
public:
	CAppWnd();
	~CAppWnd();

	bool InitializeWindow(WNDPROC WndProc, HINSTANCE instance, const char* title, const char* wnd_class, POINTS position, POINTS size);
	void SetWindowState(int nCmdShow);
	void ShutdownWindow();

public:
	HWND GetWindow() { return m_hWnd; };
	WNDCLASSA GetWindowClass() { return m_WndClass; };

private:
	HWND m_hWnd;
	WNDCLASSA m_WndClass;
};
