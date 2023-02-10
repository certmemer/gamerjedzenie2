#include "SDK.h"

IBaseClientDll*			i::Client;
IGameEventManager2*		i::Events;
IClientModeShared*		i::ClientMode;
IClientEntityList*		i::ClientEntList;
ICVar*					i::Cvar;
IInputSystem*			i::InputSystem;
IEngineClient*			i::Engine;
IEngineTrace*			i::trace;
IGlobalVarsBase*		i::globals;
ISurface*				i::Surface;
IVEffects*				i::Effects;
IVPanel*				i::VPanel;
IVModelRender*			i::ModelRender;
IVModelInfo*			i::ModelInfo;
IMaterialSystem*		i::MaterialSystem;
IMaterial*				i::Material;
IStudioRender*			i::StudioRender;

IMaterial* textured;
IMaterial* textured_xqz;