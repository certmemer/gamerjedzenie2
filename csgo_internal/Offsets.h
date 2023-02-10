#pragma once

#include "Common.h"

struct COffsets
{
	DWORD m_iHealth;
	DWORD m_flNextAttack;
	DWORD m_iTeamNum;
	DWORD m_bDormant;
	DWORD m_bGunGameImmunity;

	DWORD m_fFlags;
	DWORD m_nTickBase;
	DWORD m_bBombTicking;
	
	DWORD m_hObserverTarget;


	DWORD m_iPrimaryReserveAmmoCount;
	DWORD m_viewPunchAngle;
	DWORD m_aimPunchAngle;
	DWORD m_vecVelocity;

	DWORD m_flNextPrimaryAttack;
	DWORD m_flNextSecondaryAttack;
	DWORD m_flPostponeFireReadyTime;
	DWORD m_hActiveWeapon;
	DWORD m_Collision;
	DWORD m_iShotsFired;

	DWORD m_flSimulationTime;
	DWORD m_iWeaponID;
	DWORD m_nMoveType;
	DWORD m_nHitboxSet;
	DWORD m_bHasHelmet;
	DWORD m_bIsScoped;
	DWORD m_ArmorValue;
	DWORD m_hConstraintEntity;

	DWORD m_hOwnerEntity;
	DWORD m_flC4Blow;
	DWORD m_lifeState;
	DWORD m_flFlashMaxAlpha;


    DWORD m_fThrowTime;
    DWORD m_flThrowStrength;
    DWORD m_bPinPulled;

    DWORD m_bUseCustomAutoExposureMin;
    DWORD m_bUseCustomAutoExposureMax;
    DWORD m_flCustomAutoExposureMin;
    DWORD m_flCustomAutoExposureMax;




	DWORD m_iItemDefinitionIndex;
	DWORD m_iClip1;

	//sigs
	DWORD d3d9Device;
	DWORD playerresource;
	DWORD s_bOverridePostProcessingDisable;
	DWORD LineGoesThroughSmoke;
	DWORD SendPacket;
	DWORD GlowManager;
	DWORD LoadFromBufferEx;
	DWORD InitKeyValuesEx;
	DWORD ServerRankRevealAllEx;
	DWORD smokecount;
	DWORD m_nWritableBones;
	DWORD m_bDidCheckForOcclusion;
	DWORD InvalidateBoneCache;
	DWORD m_dwOcclusionArray;
}; 
extern COffsets offsets;

namespace Offsets
{
	extern void GrabOffsets( );
}