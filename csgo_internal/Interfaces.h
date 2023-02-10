#pragma once

#include "IBaseClientDLL.h"
#include "IGameEvent.h"
#include "IVPanel.h"
#include "IClientEntityList.h"
#include "IClientModeShared.h"
#include "ICvar.h"
#include "IEngineClient.h"
#include "IEngineTrace.h"
#include "IGlobalVarsBase.h"
#include "IInputSystem.h"
#include "Interfaces.h"
#include "ISurface.h"
#include "IVModelInfo.h"
#include "IVModelRender.h"
#include "IMaterialSystem.h"
#include "IMaterial.h"
#include "IRenderView.h"
#include "IPrediction.h"
#include "fukyou.h"
#include "VPhysics.h"
#include "IVDebugOverlay.h"
#include "IStudioRender.h"
#include "IViewRenderBeams.h"
#include "IViewRender.h"

namespace i // Interfaces
{
	extern IBaseClientDll*			Client;
	extern IGameEventManager2*		Events;
	extern IClientModeShared*		ClientMode;
	extern IClientEntityList*		ClientEntList;
	extern ICVar*					Cvar;
	extern IInputSystem*			InputSystem;
	extern IEngineClient*			Engine;
	extern IEngineTrace*			trace;
	extern IGlobalVarsBase*			globals;
	extern IVEffects*				Effects;
	extern ISurface*				Surface;
	extern IVPanel*					VPanel;
	extern IVModelRender*			ModelRender;
	extern IVModelInfo*				ModelInfo;
	extern IMaterialSystem*			MaterialSystem;
	extern IMaterial*				Material;
	extern IVRenderView*			RenderView;
	extern IStudioRender*			StudioRender;
}
