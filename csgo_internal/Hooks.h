#pragma once
#include "Trace.h"

using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
extern CreateMoveFn oCreateMove;

using DoPostScreenFn = int(__thiscall*)(void*, int);
extern DoPostScreenFn oDoPostScreen;

using LockCursorFn = void(__thiscall*)(void*);
extern LockCursorFn oLockCursor;

using PaintTraverseFn = void(__thiscall*)(void*, unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

using DrawModelFn = void(__thiscall*)(void*, void*, const draw_model_info&, matrix3x4_t*,
	float*, float*, const vector&, int);
extern DrawModelFn oDrawModel;

using EndSceneFn = long(__stdcall*)(IDirect3DDevice9* device);
extern EndSceneFn oEndScene;

using ResetFn = long(__stdcall*)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
extern ResetFn oReset;

using DrawFogFn = bool(__thiscall*)(void*);
extern DrawFogFn oDrawFog;


namespace Hooks
{
	extern bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd);
	extern int  __fastcall hkDoPostScreenEffects(void* ecx, void* edx, int a1);
	extern void __fastcall PaintTraverse(void* ecx, void* edx, unsigned int panel, bool forceRepaint, bool allowForce);
	extern bool __fastcall DrawFog(void* ecx, void*);
	extern void __fastcall LockCursor(void* ecx, void* edx);
	extern void __fastcall draw_model_hook(void* ecx, void*, void* results, const draw_model_info& info, matrix3x4_t* bone_to_world, float* flex_weights, float* flex_delayed_weights, const vector& model_origin, int flags);
	extern long __stdcall EndScene(IDirect3DDevice9* pDevice);
	extern long __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

	extern WNDPROC oldWindowProc;
	extern LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}