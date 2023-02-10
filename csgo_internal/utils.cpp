#include "sdk.h"
#include "enginepred.h"
#include "listener.h"

IGameMovement* g_pGameMovement;
IMoveHelper* g_pMoveHelper;
IPrediction2* g_pPrediction;
class ziolo;

void U::SetupInterfaces()
{
    i::Engine = U::CaptureInterface<IEngineClient>("engine.dll", "VEngineClient014");
    i::Client = U::CaptureInterface<IBaseClientDll>("client.dll", "VClient018");

    i::globals = **(IGlobalVarsBase***)((*(DWORD**)i::Client)[0] + 0x1E);
    i::ClientMode = **(IClientModeShared***)((*(DWORD**)i::Client)[10] + 0x5);

    i::Cvar = U::CaptureInterface<ICVar>("vstdlib.dll", "VEngineCvar007");
    i::InputSystem = U::CaptureInterface<IInputSystem>("inputsystem.dll", "InputSystemVersion001");
    i::ModelInfo = U::CaptureInterface<IVModelInfo>("engine.dll", "VModelInfoClient004");
    i::MaterialSystem = U::CaptureInterface<IMaterialSystem>("materialsystem.dll", "VMaterialSystem080");
    i::Surface = U::CaptureInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface031");
    i::StudioRender = U::CaptureInterface<IStudioRender>("studiorender.dll", "VStudioRender026");
    i::Events = U::CaptureInterface<IGameEventManager2>("engine.dll", "GAMEEVENTSMANAGER002");
    i::ClientEntList = U::CaptureInterface<IClientEntityList>("client.dll", "VClientEntityList003");
    i::trace = U::CaptureInterface<IEngineTrace>("engine.dll", "EngineTraceClient004");
    i::Effects = U::CaptureInterface<IVEffects>("engine.dll", "VEngineEffects001");
    i::ModelRender = U::CaptureInterface<IVModelRender>("engine.dll", "VEngineModel016");
    i::VPanel = U::CaptureInterface<IVPanel>("vgui2.dll", "VGUI_Panel009");

    g_pPrediction = U::CaptureInterface<IPrediction2>("client.dll", "VClientPrediction001");
    g_pMoveHelper = **(IMoveHelper***)(U::FindPattern("client.dll", "8B 0D ? ? ? ? 8B 46 08 68") + 0x2);
    g_pGameMovement = U::CaptureInterface<IGameMovement>("client.dll", "GameMovement001");
}

void U::SetupHooks()
{
    H::studiorender = new VTHook(reinterpret_cast<DWORD**> (i::StudioRender));
    H::surface = new VTHook(reinterpret_cast<DWORD**> (i::Surface));
    H::vpanel = new VTHook(reinterpret_cast<DWORD**> (i::VPanel));
    H::clientmode = new VTHook(reinterpret_cast<DWORD**> (i::ClientMode));
    H::d3d9 = new VTHook(reinterpret_cast<DWORD**> (offsets.d3d9Device));

    oLockCursor = (LockCursorFn)H::surface->HookFunction(reinterpret_cast<uintptr_t> (Hooks::LockCursor), 67);
    oDrawModel = (DrawModelFn)H::studiorender->HookFunction(reinterpret_cast<uintptr_t> (Hooks::draw_model_hook), 29);
    oDrawFog = (DrawFogFn)H::clientmode->HookFunction(reinterpret_cast<uintptr_t> (Hooks::DrawFog), 17);
    oPaintTraverse = (PaintTraverseFn)H::vpanel->HookFunction(reinterpret_cast<uintptr_t> (Hooks::PaintTraverse), 41);
    oCreateMove = (CreateMoveFn)H::clientmode->HookFunction(reinterpret_cast<uintptr_t> (Hooks::CreateMove), 24);
    oDoPostScreen = (DoPostScreenFn)H::clientmode->HookFunction(reinterpret_cast<uintptr_t>(Hooks::hkDoPostScreenEffects), 44);
    oEndScene = (EndSceneFn)H::d3d9->HookFunction(reinterpret_cast<uintptr_t> (Hooks::EndScene), 42);
    oReset = (ResetFn)H::d3d9->HookFunction(reinterpret_cast<uintptr_t> (Hooks::Reset), 16);
}

#include <Psapi.h> //MODULEINFO w patternsearch lol

DWORD U::FindPattern(const char* moduleName, const char* pattern)
{
    const char* pat = pattern;
    DWORD firstMatch = 0;
    DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName);
    MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
    DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
    for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
    {
        if (!*pat)
            return firstMatch;

        if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
        {
            if (!firstMatch)
                firstMatch = pCur;

            if (!pat[2])
                return firstMatch;

            if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                pat += 3;

            else
                pat += 2;    //one ?
        }
        else
        {
            pat = pattern;
            firstMatch = 0;
        }
    }
    return NULL;
}

float U::random_float(float min, float max)
{
    if (min == max) return max;

    float value = min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));

    if (value >= min && value <= max) return value;
    return max;
}

CNetVarManager* U::NetVars = new CNetVarManager;
void U::SetupOffsets()
{
    U::NetVars->Initialize();
    Offsets::GrabOffsets();
}

void U::SetupTextures()
{
    textured = i::MaterialSystem->CreateMaterial(false, false, false, 2);
    textured_xqz = i::MaterialSystem->CreateMaterial(false, true, false, 2);
}

void U::Setup()
{
    U::SetupInterfaces();

    U::SetupOffsets();

    U::SetupTextures();

    draw::SetupFonts();

    U::SetupHooks();

    hitmarker::singleton()->initialize();
}
