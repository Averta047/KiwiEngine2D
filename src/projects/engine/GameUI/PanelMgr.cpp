#include "CGuiMgr.h"

// Panels
#include "Panels/TestPanel.h"

void CGuiMgr::RegisterPanels()
{
	TestPanel* pTestPanel = new TestPanel();
	this->AddPanel(pTestPanel);
}