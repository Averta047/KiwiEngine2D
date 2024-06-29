#pragma once

#include <vector>
#include "CGuiPanel.h"

class CGuiMgr
{
public:
    CGuiMgr();
    ~CGuiMgr();

    void RegisterPanels();
    void AddPanel(CGuiPanel* panel);
    void RemovePanel(CGuiPanel* panel);
    void Render();

private:
    std::vector<CGuiPanel*> m_Panels;
};