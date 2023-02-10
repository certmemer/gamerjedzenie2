#include "Cheat.h"

DrawFogFn oDrawFog;
bool __fastcall Hooks::DrawFog(void* ecx, void*) { return false; }

DoPostScreenFn oDoPostScreen;
int __fastcall Hooks::hkDoPostScreenEffects(void* ecx, void*, int a1)
{
    if (v.esp.world_glow && g::local_player && i::Engine->IsInGame())
    {
        auto glow_manager = reinterpret_cast<CGlowObjectManager*>(offsets.GlowManager);

        auto weapon_clr = Color::FromFloat(k.world_esp);

        for (int i{}; i < glow_manager->size; ++i)
        {
            auto glow_entity = &glow_manager->m_GlowObjectDefinitions[i];
            if (glow_entity->IsEmpty()) continue;
            auto entity = glow_entity->getEntity();
            if (!entity) continue;

            switch (entity->get_client_class()->m_ClassID)
            {

            //weapons
            case CAK47:
            case CWeaponAug:
            case CWeaponAWP:
            case CWeaponBizon:
            case CWeaponP250:
            case CDEagle:
            case CWeaponElite:
            case CWeaponFiveSeven:
            case CWeaponFamas:
            case CWeaponGlock:
            case CWeaponGalilAR:
            case CWeaponG3SG1:
            case CWeaponHKP2000:
            case CWeaponMag7:
            case CWeaponM249:
            case CWeaponM4A1:
            case CWeaponMAC10:
            case CWeaponMP7:
            case CWeaponMP9:
            case CWeaponNOVA:
            case CWeaponNegev:
            case CWeaponP90:
            case CWeaponSawedoff:
            case CWeaponSCAR20:
            case CWeaponSG556:
            case CWeaponSSG08:
            case CWeaponTec9:
            case CWeaponUSP:
            case CWeaponUMP45:
            case CWeaponXM1014:
            case CWeaponTaser:
                if (v.esp.world_glow)
                    glow_entity->set2(weapon_clr); break;
                //nade
            case CBaseCSGrenadeProjectile:
            {
                if (v.esp.world_glow)
                {
                    auto name = i::ModelInfo->GetModelName(entity->get_model());
                    if (name[21] == 'r') glow_entity->set2(Color::Red());
                    else glow_entity->set2(Color::Blue());
                }
                break;
            }
            case CDecoyGrenade:
            case CDecoyProjectile: if (v.esp.world_glow) glow_entity->set2(Color::LightBlue()); break;
            case CFlashbang: if (v.esp.world_glow) glow_entity->set2(Color::Blue()); break;
            case CHEGrenade: if (v.esp.world_glow) glow_entity->set2(Color::Red()); break;
            case CIncendiaryGrenade:
            case CMolotovGrenade:
            case CMolotovProjectile: if (v.esp.world_glow) glow_entity->set2(Color::Orange()); break;
            case CSensorGrenade:
            case CSensorGrenadeProjectile: if (v.esp.world_glow) glow_entity->set2(Color::Purple()); break;
            case CSmokeGrenade:
            case CSmokeGrenadeProjectile: if (v.esp.world_glow) glow_entity->set2(Color::Green()); break;
                //bomb
            case CC4:
            case CPlantedC4: if (v.esp.world_glow) glow_entity->set2(Color::bomb_clr()); break;
            default: break;
            }
        }
    }

    return oDoPostScreen(ecx, a1);
}

