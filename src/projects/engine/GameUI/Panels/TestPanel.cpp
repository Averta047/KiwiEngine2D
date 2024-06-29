#include "TestPanel.h"

#include <string>

TestPanel::TestPanel()
{
}

TestPanel::~TestPanel() 
{
}

void TestPanel::Render() {
    if (Begin("Test Panel"))
    {
        Label("Window Pos (x: %.0f, y: %.0f)", GetCurrentWindowPos().x, GetCurrentWindowPos().y);
        Label("Window Size (x: %.0f, y: %.0f)", GetCurrentWindowSize().x, GetCurrentWindowSize().y);

        if (Button("Re Pos")) {
            SetCurrentWindowPos({ 10 , 10 });
        }

        // End.
        End();
    }
}
