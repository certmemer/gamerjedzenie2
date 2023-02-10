#include "Cheat.h"

PaintTraverseFn oPaintTraverse;
void __fastcall Hooks::PaintTraverse(void* ecx, void* edx, unsigned int panel, bool forceRepaint, bool allowForce)
{
    static bool got_panels = false;
    static unsigned int draw_panel = 0;

    oPaintTraverse(ecx, panel, forceRepaint, allowForce);

    if (!got_panels)
    {
        auto cpanel = i::VPanel->GetName(panel);

        if (!draw_panel && cpanel[0] == 'M' && cpanel[2] == 't' && cpanel[1] == 'a') draw_panel = panel;
        if (draw_panel) got_panels = true;
    }

    if (panel == draw_panel) E::esp->Run();
}