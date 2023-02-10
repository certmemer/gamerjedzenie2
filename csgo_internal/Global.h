#pragma once

#include "Entity.h"
#include "Cheat.h"
#include "Enhancements.h"

namespace g // Global Stuff
{

	extern CUserCmd*			cmd;
	extern CBaseEntity*			local_player;
	extern CBaseCombatWeapon*	weapon;

	extern char					gamerfoodsuper[20];

	extern HWND					Window;

	extern bool					PressedKeys[256];
	extern bool					d3dinit;


	extern int					screenx;
	extern int					screeny;

}

namespace H // Global Hooks
{
	extern VTHook*	vpanel;
	extern VTHook*	clientmode;
	extern VTHook*	studiorender;
	extern VTHook*	surface;
	extern VTHook*  d3d9;

}

namespace E
{
	extern c_esp*	esp;
	extern c_misc*	Misc;
}
