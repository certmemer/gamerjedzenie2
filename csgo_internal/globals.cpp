#include "SDK.h"



CUserCmd*			g::cmd;
CBaseEntity*		g::local_player;
CBaseCombatWeapon*  g::weapon;

char				g::gamerfoodsuper[20] = "";

HWND				g::Window;

bool				g::PressedKeys[256] = {};
bool				g::d3dinit = false;


int					g::screenx = -1;
int					g::screeny = -1;

VTHook*				H::vpanel;
VTHook*				H::clientmode;
VTHook*				H::studiorender;
VTHook*				H::surface;
VTHook*				H::d3d9;



c_esp*			E::esp = new c_esp();
c_misc*		    E::Misc = new c_misc();
