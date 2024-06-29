#include "CGuiMgr.h"

CGuiMgr::CGuiMgr() 
{
}

CGuiMgr::~CGuiMgr() 
{
    if (!m_Panels.empty())
    {
        for (CGuiPanel* panel : m_Panels)
        {
            delete panel;
        }

        m_Panels.clear();
    }
}

void CGuiMgr::AddPanel(CGuiPanel* panel) 
{
    m_Panels.push_back(panel);
}

void CGuiMgr::RemovePanel(CGuiPanel* panel) 
{
    if (!m_Panels.empty())
    {
        auto it = std::find(m_Panels.begin(), m_Panels.end(), panel);
        if (it != m_Panels.end())
        {
            m_Panels.erase(it);
            delete panel;
        }
    }
}

void CGuiMgr::Render() 
{
    if (!m_Panels.empty())
    {
        for (CGuiPanel* panel : m_Panels)
        {
            panel->Render();
        }
    }
}