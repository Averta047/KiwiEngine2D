#pragma once

#include <d3d11.h>
#include "CGuiMgr.h"

class CGameUI
{
public:
	CGameUI();
	~CGameUI();

	bool Initialize(HWND hWnd, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
	void Shutdown();
	void Render();

	bool MsgProc(HWND, UINT, WPARAM, LPARAM);

private:
	CGuiMgr* m_pGuiMgr;

private:
	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

private:
	void BeginFrame();
	void EndFrame();
};
