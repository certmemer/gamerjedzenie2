#include "Cheat.h"
#include "listener.h"


HMODULE sss;
void run()
{
    while (!(g::Window = FindWindowA("Valve001", NULL))) Sleep(101);
    while (!GetModuleHandleA("serverbrowser.dll")) Sleep(101);

    Hooks::oldWindowProc = (WNDPROC)SetWindowLongPtr(g::Window, GWL_WNDPROC, (LONG_PTR)Hooks::WndProc);


    U::Setup();

    i::Engine->GetScreenSize(g::screenx, g::screeny);
    // sway broni> lub bob sam
    //auto xd = i::Cvar->FindVar("cl_wpn_sway_scale");

        //	std::string Topkek = std::to_string((int)&xd);

    //	U::ConColorMsg(Color::Purple(), "%s" ,Topkek.c_str());

   

    while (!g::PressedKeys[VK_END])
        Sleep(101);


    hitmarker::singleton()->remove();

    H::d3d9->UnHook();
    H::studiorender->UnHook();
    H::vpanel->UnHook();
    H::clientmode->UnHook();
    H::surface->UnHook();
    i::InputSystem->EnableInput(true);


    SetWindowLongPtr(g::Window, GWL_WNDPROC, (LONG_PTR)Hooks::oldWindowProc);
    Sleep(99);

    FreeLibraryAndExitThread(sss, 0);


}


int __stdcall DllMain(void* m, long r, void*)
{
    if (r == 1)
    {
        sss = (HMODULE)m;

        auto h = CreateThread(0, 0, (PTHREAD_START_ROUTINE)run, 0, 0, 0);
        CloseHandle(h);
    }
     
    return 1;
}