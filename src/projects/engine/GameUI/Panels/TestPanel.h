#pragma once

#include "../CGuiPanel.h"
#include "../CGuiWidgets.h"

class TestPanel : public CGuiPanel, public CGuiWidgets {
public:
    TestPanel();
    ~TestPanel();

    void Render() override;
};
