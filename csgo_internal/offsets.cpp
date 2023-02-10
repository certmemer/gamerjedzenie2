#pragma once

#include "SDK.h"

COffsets offsets;

void Offsets::GrabOffsets()
{
    offsets.m_bDormant = 0xED;
    offsets.m_nMoveType = 0x25C;


    offsets.m_flC4Blow = U::NetVars->GetOffset("DT_PlantedC4", "m_flC4Blow");
    offsets.m_bBombTicking = U::NetVars->GetOffset("DT_PlantedC4", "m_bBombTicking");



    offsets.m_lifeState = U::NetVars->GetOffset("DT_CSPlayer", "m_lifeState");

    offsets.m_flFlashMaxAlpha = U::NetVars->GetOffset("DT_CSPlayer", "m_flFlashMaxAlpha");
    offsets.m_iTeamNum = U::NetVars->GetOffset("DT_CSPlayer", "m_iTeamNum");
    offsets.m_ArmorValue = U::NetVars->GetOffset("DT_CSPlayer", "m_ArmorValue");
    offsets.m_vecVelocity = U::NetVars->GetOffset("DT_CSPlayer", "m_vecVelocity[0]");
    offsets.m_nTickBase = U::NetVars->GetOffset("DT_CSPlayer", "m_nTickBase");
    offsets.m_fFlags = U::NetVars->GetOffset("DT_CSPlayer", "m_fFlags");
    offsets.m_bIsScoped = U::NetVars->GetOffset("DT_CSPlayer", "m_bIsScoped");
    offsets.m_hActiveWeapon = U::NetVars->GetOffset("DT_CSPlayer", "m_hActiveWeapon");
    offsets.m_flNextAttack = U::NetVars->GetOffset("DT_CSPlayer", "m_flNextAttack");
    offsets.m_bGunGameImmunity = U::NetVars->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
    offsets.m_iHealth = U::NetVars->GetOffset("DT_CSPlayer", "m_iHealth");
    offsets.m_iShotsFired = U::NetVars->GetOffset("DT_CSPlayer", "m_iShotsFired");
    offsets.m_bHasHelmet = U::NetVars->GetOffset("DT_CSPlayer", "m_bHasHelmet");


    offsets.m_iWeaponID = U::NetVars->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty") + 0x30;
    offsets.m_flPostponeFireReadyTime = U::NetVars->GetOffset("DT_WeaponCSBase", "m_flPostponeFireReadyTime");
    offsets.m_iPrimaryReserveAmmoCount = U::NetVars->GetOffset("DT_WeaponCSBase", "m_iPrimaryReserveAmmoCount");


    offsets.m_Collision = U::NetVars->GetOffset("DT_BasePlayer", "m_Collision"); // zobacz czy to z clientunknown dziala tez :D
    offsets.m_nHitboxSet = U::NetVars->GetOffset("DT_BasePlayer", "m_nHitboxSet");
    offsets.m_hObserverTarget = U::NetVars->GetOffset("DT_BasePlayer", "m_hObserverTarget");
    offsets.m_aimPunchAngle = U::NetVars->GetOffset("DT_BasePlayer", "m_aimPunchAngle");

    offsets.m_hConstraintEntity = U::NetVars->GetOffset("DT_BasePlayer", "m_hConstraintEntity");


    offsets.m_flSimulationTime = U::NetVars->GetOffset("DT_BaseEntity", "m_flSimulationTime");
    offsets.m_hOwnerEntity = U::NetVars->GetOffset("DT_BaseEntity", "m_hOwnerEntity");



    offsets.m_flNextPrimaryAttack = U::NetVars->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
    offsets.m_flNextSecondaryAttack = U::NetVars->GetOffset("DT_BaseCombatWeapon", "m_flNextSecondaryAttack");
    offsets.m_iClip1 = U::NetVars->GetOffset("DT_BaseCombatWeapon", "m_iClip1");


    offsets.m_iItemDefinitionIndex = U::NetVars->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");


    offsets.m_bPinPulled = U::NetVars->GetOffset("DT_BaseCSGrenade", "m_bIsHeldByPlayer");
    offsets.m_fThrowTime = U::NetVars->GetOffset("DT_BaseCSGrenade", "m_fThrowTime");
    offsets.m_flThrowStrength = U::NetVars->GetOffset("DT_BaseCSGrenade", "m_flThrowStrength");



    offsets.d3d9Device = **(long**)(U::FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 1);

    offsets.s_bOverridePostProcessingDisable = *(long*)(U::FindPattern("client.dll", "80 3D ? ? ? ? ? 53 56 57 0F 85") + 2);



    offsets.GlowManager = *(long*)(U::FindPattern("client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);

    offsets.LineGoesThroughSmoke = U::FindPattern("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");


    offsets.ServerRankRevealAllEx = U::FindPattern("client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ?");
    offsets.LoadFromBufferEx = U::FindPattern("client.dll", "02 7E 4E") - 0x3F;
    offsets.InitKeyValuesEx = U::FindPattern("client.dll", "55 8B EC 51 33 C0 C7 45");


    offsets.m_nWritableBones = U::NetVars->GetOffset("DT_CSPlayer", "m_nForceBone") + 0x20;
    offsets.m_bDidCheckForOcclusion = *(long*)(U::FindPattern("client.dll", "A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8") + 0x7);
    offsets.m_dwOcclusionArray = *(long*)(U::FindPattern("client.dll", "A1 ? ? ? ? 8B B7 ? ? ? ? 89 75 F8") + 0x1); //^ to samo tylko +6
    offsets.InvalidateBoneCache = U::FindPattern("client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81");



    offsets.m_bUseCustomAutoExposureMin = U::NetVars->GetOffset("DT_EnvTonemapController", "m_bUseCustomAutoExposureMin");
    offsets.m_bUseCustomAutoExposureMax = U::NetVars->GetOffset("DT_EnvTonemapController", "m_bUseCustomAutoExposureMax");
    offsets.m_flCustomAutoExposureMin = U::NetVars->GetOffset("DT_EnvTonemapController", "m_flCustomAutoExposureMin");
    offsets.m_flCustomAutoExposureMax = U::NetVars->GetOffset("DT_EnvTonemapController", "m_flCustomAutoExposureMax");

}
