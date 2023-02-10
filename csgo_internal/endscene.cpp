#include "Cheat.h"

#include "imgui\imgui.h"
#include "imgui\dx9\imgui_dx9.h"
kolorki k;
void GUI_Init(IDirect3DDevice9* pDevice);
EndSceneFn oEndScene;

void legit_tab();
void visuals_tab();
void misc_tab();

void menu()
{
    const char* tabs[] = { "aim", "esp", "misc", };
    static int page = 0;
    for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
    {
        int distance = i == page ? 0 : 5;
        ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
            0.2f - (distance * 0.035f),
            0.2f - (distance * 0.035f),
            0.2f - (distance * 0.035f),
            0.9f
        );

        if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 3, 0)))
            page = i;

        ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);

        if (i < IM_ARRAYSIZE(tabs) - 1)
            ImGui::SameLine(0.f, 0.f);
    }

    ImGui::Separator();

    switch (page) {
    case 0: legit_tab(); break;
    case 1: visuals_tab(); break;
    case 2: misc_tab(); break;
    }
}

long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice) 
{
    if (!g::d3dinit) GUI_Init(pDevice);
    static bool reset = false;

    if (v.misc.menu)
    {
        ImGui::GetIO().MouseDrawCursor = v.misc.menu;

        DWORD colorwrite, srgbwrite;
        pDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &colorwrite);
        pDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &srgbwrite);
        IDirect3DStateBlock9* state;
        pDevice->CreateStateBlock(D3DSBT_PIXELSTATE, &state);
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xFFFFFFFF);
        pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, false);

        if (reset)
        {
            //  i::InputSystem->ResetInputState(); zeby biegac z menu lol
            reset = false;
        }
        ImGui_ImplDX9_NewFrame();
        int pX, pY;
        i::InputSystem->GetCursorPosition(&pX, &pY);

        ImGuiIO& io = ImGui::GetIO();
        io.MousePos.x = (float)(pX);
        io.MousePos.y = (float)(pY);

       


        ImGui::Begin("x47d", &v.misc.menu, ImVec2(310, 143), 0.78f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
        {
            static int page = 0;
            const char* tabs[] = {
                "aim",
                "esp",
                "misc",
            };

            ImGui::BeginChild("##tabs", ImVec2(86, 0), true); //+16 
            {
                for (int i = 0; i < 3; i++)
                {
                    if (ImGui::Button(tabs[i], ImVec2(70, 20))) 
                        page = i;
                }


                ImGui::PushItemWidth(70.f);
                static int Ziolosztos = 0;
                const char* asasudasi[] = { "sfghsghf", "cbmncnbm", "kryiryk" };
                ImGui::Combo("##config", &Ziolosztos, asasudasi, ARRAYSIZE(asasudasi));

                if (ImGui::Button("save", ImVec2(30, 16)))
                    Config->Save(Ziolosztos);
                ImGui::SameLine(43.f);
                if (ImGui::Button("load", ImVec2(30, 16)))
                    Config->Load(Ziolosztos);

                ImGui::EndChild();
            }

            ImGui::SameLine(101.f); //+15
            ImGui::BeginChild("##memes", ImVec2(180, 0), true);
            {
                switch (page)
                {
                case 0: legit_tab(); break;
                case 1: visuals_tab(); break;
                case 2: misc_tab(); break;
                }
                ImGui::EndChild();
            }
        }





        ImGui::End();
        ImGui::Render();

        state->Apply();
        state->Release();
        pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, colorwrite);
        pDevice->SetRenderState(D3DRS_SRGBWRITEENABLE, srgbwrite);
    }
    else if (!reset)
    {
        i::InputSystem->EnableInput(true);
        reset = true;
    }

    return oEndScene(pDevice);
}

ResetFn oReset;
bool wtfXDdd = false;
long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    if (wtfXDdd)
    {
        wtfXDdd = false;

        ImGui_ImplDX9_InvalidateDeviceObjects();
        oReset(pDevice, pPresentationParameters);
        ImGui_ImplDX9_CreateDeviceObjects();
        return 5;
    }

    if (!g::d3dinit)
        return oReset(pDevice, pPresentationParameters);

    ImGui_ImplDX9_InvalidateDeviceObjects();

    auto hr = oReset(pDevice, pPresentationParameters);

    ImGui_ImplDX9_CreateDeviceObjects();

    return hr;
}

WNDPROC Hooks::oldWindowProc;
void OpenMenu();

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT __stdcall Hooks::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
        g::PressedKeys[VK_LBUTTON] = true;
        break;
    case WM_LBUTTONUP:
        g::PressedKeys[VK_LBUTTON] = false;
        break;
    case WM_RBUTTONDOWN:
        g::PressedKeys[VK_RBUTTON] = true;
        break;
    case WM_RBUTTONUP:
        g::PressedKeys[VK_RBUTTON] = false;
        break;
    case WM_MBUTTONDOWN:
        g::PressedKeys[VK_MBUTTON] = true;
        break;
    case WM_MBUTTONUP:
        g::PressedKeys[VK_MBUTTON] = false;
        break;
    case WM_XBUTTONDOWN:
    {
        UINT button = GET_XBUTTON_WPARAM(wParam);
        if (button == XBUTTON1)
        {
            g::PressedKeys[VK_XBUTTON1] = true;
        }
        else if (button == XBUTTON2)
        {
            g::PressedKeys[VK_XBUTTON2] = true;
        }
        break;
    }
    case WM_XBUTTONUP:
    {
        UINT button = GET_XBUTTON_WPARAM(wParam);
        if (button == XBUTTON1)
        {
            g::PressedKeys[VK_XBUTTON1] = false;
        }
        else if (button == XBUTTON2)
        {
            g::PressedKeys[VK_XBUTTON2] = false;
        }
        break;
    }
    case WM_KEYDOWN:
        g::PressedKeys[wParam] = true;
        break;
    case WM_KEYUP:
        g::PressedKeys[wParam] = false;
        break;
    case WM_SYSKEYDOWN:
        if (wParam == VK_MENU)
            g::PressedKeys[VK_MENU] = true;
        break;
    case WM_SYSKEYUP:
        if (wParam == VK_MENU)
            g::PressedKeys[VK_MENU] = false;
        break;
    case WM_ACTIVATEAPP:
    {
        if (g::d3dinit)
            wtfXDdd = true;
    } break;
    default: break;
    }

    OpenMenu();

    if (g::d3dinit && v.misc.menu && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    return CallWindowProc(oldWindowProc, hWnd, uMsg, wParam, lParam);
}

void OpenMenu()
{
    static bool is_down = false;
    static bool is_clicked = false;

    if (g::PressedKeys[VK_DELETE])
    {
        is_clicked = false;
        is_down = true;
    }
    else if (!g::PressedKeys[VK_DELETE] && is_down)
    {
        is_clicked = true;
        is_down = false;
    }
    else
    {
        is_clicked = false;
        is_down = false;
    }

    if (is_clicked)
    {
        v.misc.menu = !v.misc.menu;
    }
}

LockCursorFn oLockCursor;
void __fastcall Hooks::LockCursor(void* ecx, void* edx)
{
    if (v.misc.menu)
    {
        i::Surface->UnlockCursor();
        i::InputSystem->EnableInput(false);
        return;
    }
    oLockCursor(ecx);
}

void GUI_Init(IDirect3DDevice9* pDevice)
{
    ImGui_ImplDX9_Init(g::Window, pDevice);

    ImGuiStyle& style = ImGui::GetStyle();



    ImVec4 fontColor = ImVec4(1.f, 1.f, 1.f, 1.f);
    ImVec4 bodyColor = ImVec4(0.1f, 0.1f, 0.1f, 0.9f);
    ImVec4 mainColor = ImVec4(0.2f, 0.2f, 0.2f, 0.9f);

    ImVec4 mainColorHovered = ImVec4(mainColor.x + 0.1f, mainColor.y + 0.1f, mainColor.z + 0.1f, mainColor.w);
    ImVec4 mainColorActive = ImVec4(mainColor.x + 0.2f, mainColor.y + 0.2f, mainColor.z + 0.2f, mainColor.w);
    ImVec4 menubarColor = ImVec4(bodyColor.x, bodyColor.y, bodyColor.z, bodyColor.w - 0.8f);
    ImVec4 frameBgColor = ImVec4(bodyColor.x, bodyColor.y, bodyColor.z, bodyColor.w + .1f);
    ImVec4 tooltipBgColor = ImVec4(bodyColor.x, bodyColor.y, bodyColor.z, bodyColor.w + .05f);

    style.Alpha = 1.0f;
    style.WindowPadding = ImVec2(8, 8);
    style.WindowMinSize = ImVec2(32, 32);
    style.WindowRounding = 0.0f;
    //style.WindowTitleAlign = ImVec2(0.f, 0.5f);
    //	style.ChildWindowRounding = 0.0f;
    style.WindowTitleAlign = ImVec2(0.0f, 0.75f);
    style.FramePadding = ImVec2(4, 3);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(8, 4);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 3.0f;
    style.ScrollbarSize = 5.0f;
    style.ScrollbarRounding = 1.0f;
    style.GrabMinSize = 5.0f;
    style.GrabRounding = 0.0f;
    style.FrameBorderSize = 1.0f;

    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.DisplayWindowPadding = ImVec2(22, 22);
    style.DisplaySafeAreaPadding = ImVec2(4, 4);
    style.AntiAliasedLines = true;
    style.AntiAliasedShapes = true;
    style.CurveTessellationTol = 1.25f;

    style.Colors[ImGuiCol_Text] = fontColor;
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = bodyColor;
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(.0f, .0f, .0f, .0f);
    style.Colors[ImGuiCol_PopupBg] = tooltipBgColor;
    style.Colors[ImGuiCol_Border] = mainColor;
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = frameBgColor;
    style.Colors[ImGuiCol_FrameBgHovered] = mainColorHovered;
    style.Colors[ImGuiCol_FrameBgActive] = mainColorActive;
    style.Colors[ImGuiCol_TitleBg] = mainColor;
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = mainColor;
    style.Colors[ImGuiCol_MenuBarBg] = menubarColor;
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .05f, frameBgColor.y + .05f, frameBgColor.z + .05f, frameBgColor.w);
    style.Colors[ImGuiCol_ScrollbarGrab] = mainColor;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorHovered;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
    //style.Colors[ImGuiCol_ComboBg] = frameBgColor;
    style.Colors[ImGuiCol_CheckMark] = mainColor;
    style.Colors[ImGuiCol_SliderGrab] = mainColorHovered;
    style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
    style.Colors[ImGuiCol_Button] = mainColor;
    style.Colors[ImGuiCol_ButtonHovered] = mainColorHovered;
    style.Colors[ImGuiCol_ButtonActive] = mainColorActive;
    style.Colors[ImGuiCol_Header] = mainColor;
    style.Colors[ImGuiCol_HeaderHovered] = mainColorHovered;
    style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
    style.Colors[ImGuiCol_Column] = mainColor;
    style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
    style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
    style.Colors[ImGuiCol_ResizeGrip] = mainColor;
    style.Colors[ImGuiCol_ResizeGripHovered] = mainColorHovered;
    style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
    style.Colors[ImGuiCol_CloseButton] = mainColorHovered;
    style.Colors[ImGuiCol_CloseButtonHovered] = mainColorHovered;
    style.Colors[ImGuiCol_CloseButtonActive] = mainColorActive;
    style.Colors[ImGuiCol_PlotLines] = mainColor;
    style.Colors[ImGuiCol_PlotLinesHovered] = mainColorHovered;
    style.Colors[ImGuiCol_PlotHistogram] = mainColor;
    style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorHovered;
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);


    g::d3dinit = true;
}


void legit_tab()
{
    
        ImGui::Checkbox("enable##legit", &v.legitbot.enabled);

        ImGui::SliderInt("##bt", &v.legitbot.backtrack, 19, 200, (v.legitbot.backtrack < 20) ? "bt off" : "bt %.0fms");

        ImGui::Text("weapons");
        static int group = 0;
        const char* groups[] = { "pistols", "smg", "rifles", "shotguns" , "snipers", "autosnipers" };
        ImGui::SameLine(59.f);
        ImGui::PushItemWidth(63.f);
        ImGui::Combo("##gr", &group, groups, IM_ARRAYSIZE(groups));

        ImGui::PushItemWidth(55.f);
        ImGui::Text("hitbox");
        ImGui::SameLine(79.f);
        const char* hitscan[] = { "head", "neck", "chest", "stomach", "closest" };

        switch (group) { //si[er partia kurwo przerob
        case 0:
            ImGui::Combo("##ap", &v.legitbot.hitbox_pist, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(104.f);
            ImGui::SliderFloat("##bp", &v.legitbot.fov_pist, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##cp", &v.legitbot.smooth_pist, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##dp", &v.legitbot.rcs_pist, 0.f, 100.f, "rcs %.0f%%");
            break;
        case 1:
            ImGui::Combo("##as", &v.legitbot.hitbox_smg, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(124.f);
            ImGui::SliderFloat("##bs", &v.legitbot.fov_smg, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##cs", &v.legitbot.smooth_smg, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##ds", &v.legitbot.rcs_smg, 0.f, 100.f, "rcs %.0f%%");
            break;
        case 2:
            ImGui::Combo("##ar", &v.legitbot.hitbox_rifle, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(124.f);
            ImGui::SliderFloat("##br", &v.legitbot.fov_rifle, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##cr", &v.legitbot.smooth_rifle, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##dr", &v.legitbot.rcs_rifle, 0.f, 100.f, "rcs %.0f%%");
            break;
        case 3:
            ImGui::Combo("##ash", &v.legitbot.hitbox_shot, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(124.f);
            ImGui::SliderFloat("##bsh", &v.legitbot.fov_shot, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##csh", &v.legitbot.smooth_shot, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##dsh", &v.legitbot.rcs_shot, 0.f, 100.f, "rcs %.0f%%");
            break;
        case 4:
            ImGui::Combo("##asn", &v.legitbot.hitbox_snip, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(124.f);
            ImGui::SliderFloat("##bsn", &v.legitbot.fov_snip, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##csn", &v.legitbot.smooth_snip, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##dsn", &v.legitbot.rcs_snip, 0.f, 100.f, "rcs %.0f%%");
            break;
        case 5:
            ImGui::Combo("##aa", &v.legitbot.hitbox_auto, hitscan, IM_ARRAYSIZE(hitscan), IM_ARRAYSIZE(hitscan));
            ImGui::PushItemWidth(124.f);
            ImGui::SliderFloat("##ba", &v.legitbot.fov_auto, 0.f, 4.f, "fov %.2f");
            ImGui::SliderFloat("##ca", &v.legitbot.smooth_auto, 0.f, 100.f, "smooth %.2f");
            ImGui::SliderFloat("##da", &v.legitbot.rcs_auto, 0.f, 100.f, "rcs %.0f%%");
            break;
        }
   
}


#define picker_flags ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoSidePreview \
| ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoOptions 

void visuals_tab()
{
    ImGui::Checkbox("box     ", &v.esp.box);
    if (v.esp.box) {
        ImGui::SameLine();
        ImGui::ColorEdit3("##boxclr", k.esp_visible, picker_flags);
    }

    ImGui::Checkbox("visible  ", &v.esp.chams_players);
    if (v.esp.chams_players) {
        ImGui::SameLine();
        ImGui::ColorEdit3("##visible_color", k.chams_visible, picker_flags);
    }
    ImGui::Checkbox("ignorez  ", &v.esp.chams_players_xqz);
    if (v.esp.chams_players_xqz) {
        ImGui::SameLine();
        ImGui::ColorEdit3("##hidden_color", k.chams_hidden, picker_flags);
    }

    ImGui::Checkbox("text    ", &v.esp.world_text);
    ImGui::Checkbox("glow    ", &v.esp.world_glow);
    if (v.esp.world_glow) {
        ImGui::SameLine();
        ImGui::ColorEdit3("##world_esp_color", k.world_esp, picker_flags);
    }

    ImGui::Checkbox("sound    ", &v.esp.sound);

}

void misc_tab()
{
    ImGui::Checkbox("bhop", &v.misc.auto_jump);



    ImGui::Checkbox("night", &v.misc.nightmode);

    ImGui::Checkbox("getout", &v.misc.getout);

    ImGui::Separator();


    ImGui::Checkbox("clantag", &v.misc.clantag);
    ImGui::SameLine();
    ImGui::Checkbox("rotate", &v.misc.clantag_rotate);
    ImGui::SameLine();
    ImGui::PushItemWidth(85.f);
    ImGui::InputText("##cl", g::gamerfoodsuper, 16);
    ImGui::Separator();



}


