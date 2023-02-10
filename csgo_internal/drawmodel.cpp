#include "Cheat.h"
#include "listener.h"


void IVModelRender::ForcedMaterialOverride(IMaterial* mat)
{
    typedef void(__thiscall *OrigFn)(void*, IMaterial*, int, int);
    U::GetVFunc<OrigFn>(this, 1)(this, mat, 0, 0);
}
void IStudioRender::ForcedMaterialOverridez(IMaterial* mat)
{
    typedef void(__thiscall *OrigFn)(void*, IMaterial*, int, int);
    U::GetVFunc<OrigFn>(this, 33)(this, mat, 0, 0);
}

bool IVModelRender::IsForcedMaterialOverride()
{
    typedef bool(__thiscall *OrigFn)(void*);
    return U::GetVFunc<OrigFn>(this, 2)(this);
}

__forceinline void ForceMaterialz(IMaterial* material, float* color)
{
    if (material)
    {
        material->ColorModulate(color[0], color[1], color[2]);
        i::StudioRender->ForcedMaterialOverridez(material);
    }
}

void nightmode(bool ingame) //nightmode na ten wiesniacki external metode  
{
    static bool nm_done = false;
    static bool nosky_done = false;
    static bool nosmoke_done = false;

    static auto draw_prop = i::Cvar->FindVar("r_drawspecificstaticprop");

    auto newmap = hitmarker::singleton()->newmap;

    if (!ingame || newmap)
    {
        nm_done = false;
        nosky_done = false;
        nosmoke_done = false;
    }

    if (!nosky_done && ingame)
    {
        static auto sky = U::FindPattern("engine.dll", "55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45");
        static auto set_sky = reinterpret_cast<void(__fastcall*)(const char*)>(sky);
        set_sky("sky_csgo_night02b");

        for (auto i = i::MaterialSystem->FirstMaterial(); i != i::MaterialSystem->InvalidMaterial(); i = i::MaterialSystem->NextMaterial(i))
        {
            auto mat = i::MaterialSystem->GetMaterial(i);
            if (!mat || mat->IsErrorMaterial()) continue;

           
            if (mat->GetTextureGroupName()[0] == 'S')
                mat->ColorModulate(0.f, 0.539f, 0.614f);
        }
        //molotov smoke :D
        i::MaterialSystem->FindMaterial("dev/blurfilterx_nohdr", TEXTURE_GROUP_OTHER)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
        i::MaterialSystem->FindMaterial("dev/blurfiltery_nohdr", TEXTURE_GROUP_OTHER)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
        i::MaterialSystem->FindMaterial("dev/scope_bluroverlay", TEXTURE_GROUP_OTHER)->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
        nosky_done = true;
    }

    if (v.misc.nightmode)
    {
        if (!nm_done && ingame)
        {
            draw_prop->SetValue(0);
            for (auto i{ i::MaterialSystem->FirstMaterial() }; i != i::MaterialSystem->InvalidMaterial(); i = i::MaterialSystem->NextMaterial(i))
            {
                auto mat = i::MaterialSystem->GetMaterial(i);
                if (!mat || mat->IsErrorMaterial()) continue;

                if (mat->GetTextureGroupName()[0] == 'W')
                    mat->ColorModulate(0.308f, 0.308f, 0.333f);
                else if (mat->GetTextureGroupName()[0] == 'S')
                    mat->ColorModulate(0.474f, 0.474f, 0.50f);
            }
            nm_done = true;
        }
    }
    else
    {
        if (nm_done && ingame)
        {
            draw_prop->SetValue(-1);
            for (auto i{ i::MaterialSystem->FirstMaterial() }; i != i::MaterialSystem->InvalidMaterial(); i = i::MaterialSystem->NextMaterial(i))
            {
                auto mat = i::MaterialSystem->GetMaterial(i);
                if (!mat || mat->IsErrorMaterial()) continue;

                if (mat->GetTextureGroupName()[0] == 'W')
                    mat->ColorModulate(1.f, 1.f, 1.f);
                else if (mat->GetTextureGroupName()[0] == 'S')
                    mat->ColorModulate(1.f, 1.f, 1.f);
            }
            nm_done = false;
        }
    }

    if (hitmarker::singleton()->newmap && ingame && nosky_done)
        hitmarker::singleton()->newmap = false;
}


#include "IStudioRender.h"
DrawModelFn oDrawModel;
void __fastcall Hooks::draw_model_hook(void* ecx, void*, void* results,
    const draw_model_info& info, matrix3x4_t* bone_to_world, float* flex_weights,
    float* flex_delayed_weights, const vector& model_origin, int flags)
{
    if (i::ModelRender->IsForcedMaterialOverride()) {
        oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);
        return;
    }

    bool ingame = true;
    if (!i::Engine->IsInGame() || !g::local_player) ingame = false;
    nightmode(ingame);

    if (v.esp.chams_players && ingame)
    {
        if (info.entity && *(int*)((long)info.entity + offsets.m_lifeState) == 0)
        {
            auto model_name = info.studio_hdr->name;
            if (model_name[0] == 'p' && model_name[3] == 'y' && model_name[6] == '/')
            {

                if (info.entity->is_enemy())
                {
                    if (v.esp.chams_players_xqz)
                    {
                        ForceMaterialz(textured_xqz, k.chams_hidden);
                        oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);
                    }
                    ForceMaterialz(textured, k.chams_visible);
                }
                // else if (v.esp.chams_players_noteammates) return;
            }
        }
    }

    oDrawModel(ecx, results, info, bone_to_world, flex_weights, flex_delayed_weights, model_origin, flags);
    i::ModelRender->ForcedMaterialOverride(nullptr);
}