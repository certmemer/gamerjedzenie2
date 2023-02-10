#include "SDK.h"

//////////////////////////////////////////////////////////////////////////////////////////////

int	CBaseEntity::get_health()
{
    return *(int*)((long)this + offsets.m_iHealth);
}

int CBaseEntity::get_armor()
{
    return *(int*)((long)this + offsets.m_ArmorValue);
}

bool CBaseEntity::has_helmet()
{
    return *(bool*)((long)this + offsets.m_bHasHelmet);
}

bool CBaseEntity::is_alive()
{
    return (*(int*)((long)this + offsets.m_lifeState) == 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool CBaseEntity::is_player()
{
    return U::GetVFunc<bool(__thiscall*)(void*)>(this, 157)(this);
}

int CBaseEntity::get_team()
{
    return *(int*)((long)this + offsets.m_iTeamNum);
}

bool CBaseEntity::is_enemy()
{
    return this->get_team() ^ g::local_player->get_team();
}

bool CBaseEntity::is_dormant()
{
    return *(bool*)((long)this + offsets.m_bDormant);
}

bool CBaseEntity::is_immune()
{
    if (!this) return true;
    return *(bool*)((long)this + offsets.m_bGunGameImmunity);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int CBaseEntity::get_flags()
{
    return *(int*)((long)this + offsets.m_fFlags);
}

int CBaseEntity::get_movetype()
{
    return *(int*)((long)this + offsets.m_nMoveType);
}

vector CBaseEntity::get_velocity()
{
    return *(vector*)((long)this + offsets.m_vecVelocity);
}

//////////////////////////////////////////////////////////////////////////////////////////////

CUtlVector<C_AnimationLayer>& CBaseEntity::GetAnimOverlays()
{
    return (*reinterpret_cast<CUtlVector<C_AnimationLayer>*>(reinterpret_cast<long>(this) + 0x2970));
}

C_AnimationLayer * CBaseEntity::GetAnimOverlay(int i)
{
    return &GetAnimOverlays()[i];
}

int CBaseEntity::GetNumAnimOverlays()
{
    return GetAnimOverlays().Count();
}

int CBaseEntity::GetSequenceActivity(int sequence)
{
    auto hdr = i::ModelInfo->GetStudioModel(this->get_model());
    if (!hdr) return -1;

    static auto GetSequenceActivity = reinterpret_cast<int(__fastcall*)(void*, studiohdr_t*, int)>((long)U::FindPattern("client.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D"));

    return GetSequenceActivity(this, hdr, sequence);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int CBaseEntity::get_index()
{
    __asm
    {
        MOV EDI, this
        LEA ECX, DWORD PTR DS : [EDI + 0x8]
        MOV EDX, DWORD PTR DS : [ECX]
        CALL DWORD PTR DS : [EDX + 0x28]
    }
}

CBaseCombatWeapon* CBaseEntity::get_weapon()
{
    long weaponData = *(long*)((long)this + offsets.m_hActiveWeapon);
    return (CBaseCombatWeapon*)i::ClientEntList->GetClientEntityFromHandle(weaponData);
}

ClientClass* CBaseEntity::get_client_class()
{
    void* pNetworkable = (void*)((long)(this) + 0x8);
    typedef ClientClass*(__thiscall* OriginalFn)(void*);
    return U::GetVFunc<OriginalFn>(pNetworkable, 2)(pNetworkable);
}

//////////////////////////////////////////////////////////////////////////////////////////////

float* CBaseEntity::get_flash_alpha()
{
    return (float*)((long)this + offsets.m_flFlashMaxAlpha);
}


//////////////////////////////////////////////////////////////////////////////////////////////

bool CBaseEntity::is_scoped()
{
    return *(bool*)((long)this + offsets.m_bIsScoped);
}



bool CBaseEntity::has_bomb()
{
    static auto fnHasC4 = reinterpret_cast<bool(__thiscall*)(void*)>(U::FindPattern("client.dll", "56 8B F1 85 F6 74 31"));

    return fnHasC4(this);
    //auto PlayerCompetitiveRank = *reinterpret_cast<int*>(uintptr_t(offsets.playerresource) + offsets.m_iPlayerC4 + this->index);
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool CBaseEntity::setup_bones(matrix3x4_t *pBoneToWorldOut)
{
    __asm
    {
        mov edi, this
        lea ecx, dword ptr ds : [edi + 0x4]
        mov edx, dword ptr ds : [ecx]
        push 0
        push 0x100
        push 128
        push pBoneToWorldOut
        call dword ptr ds : [edx + 0x34]
    }
}

bool CBaseEntity::setup_bones_pvs(matrix3x4_t *pBoneToWorldOut)
{

    *(int*)((long)this + offsets.m_nWritableBones) = 0;
    *(int*)((long)this + offsets.m_bDidCheckForOcclusion) = reinterpret_cast<int*>(offsets.m_dwOcclusionArray)[1];
    reinterpret_cast<void(__fastcall*)(void*)>(offsets.InvalidateBoneCache)(this);

    auto xd = i::globals->curtime; //corrected ;)

   // if (!i::Engine->IsTakingScreenshot())
      //  *(int*)(this + 0xA28) |= 0xA;

    __asm
    {
        mov edi, this
        lea ecx, dword ptr ds : [edi + 0x4]
        mov edx, dword ptr ds : [ecx]
        push xd
        push 0x100
        push 128
        push pBoneToWorldOut
        call dword ptr ds : [edx + 0x34]
    }
}

ICollideable* CBaseEntity::get_collideable()
{
    return (ICollideable*)((long)this + offsets.m_Collision);
}

const matrix3x4a_t& CBaseEntity::get_matrix_transform()
{
    return *(matrix3x4a_t*)((long)this + 0x444);// offsets::entity::m_rgflCoordinateFrame);
}

//////////////////////////////////////////////////////////////////////////////////////////////

model_t* CBaseEntity::get_model()
{
    return *(model_t**)((long)this + 0x6C);
}

int CBaseEntity::get_hitbox_set()
{
    return *(int*)((long)this + offsets.m_nHitboxSet);
}

//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////

QAngle CBaseEntity::get_aim_punch()
{
    return *(QAngle*)((long)this + offsets.m_aimPunchAngle);
}

QAngle CBaseEntity::get_view_punch()
{
    return *(QAngle*)((long)this + offsets.m_viewPunchAngle);
}

//////////////////////////////////////////////////////////////////////////////////////////////

float CBaseEntity::bomb_timer()
{
    float explode_time = *(float*)((long)this + offsets.m_flC4Blow);
    return explode_time - i::globals->curtime;
    //float returnValue = explode_time - i::globals->curtime;
    //return (returnValue < 0) ? 0.f : returnValue;
}



bool CBaseEntity::bomb_ticking()
{
    return *(bool*)((long)this + offsets.m_bBombTicking);
}

//////////////////////////////////////////////////////////////////////////////////////////////

////random gonweo
int CBaseEntity::get_owner()
{
    return *(int*)((long)this + offsets.m_hOwnerEntity);
}

vector CBaseEntity::get_eye_pos()
{
    /*vector origin = this->get_origin();
    vector offset = *(vector*)((uintptr_t)this + offsets.m_vecViewOffset);

    return(origin + offset);*/
    vector pos;
    U::GetVFunc<void(__thiscall*)(CBaseEntity*, vector&)>(this, 284)(this, pos);
    return pos;
}

int CBaseEntity::get_tickbase()
{
    return *(int*)((long)this + offsets.m_nTickBase);
}

float CBaseEntity::get_next_attack()
{
    return *(float*)((long)this + offsets.m_flNextAttack);
}

long CBaseEntity::get_spec_target()
{
    return *(long*)((long)this + offsets.m_hObserverTarget);
}

int CBaseEntity::get_shots_fired()
{
    return *(int*)((long)this + offsets.m_iShotsFired);
}

float CBaseEntity::get_simulation_time()
{
    return *(float*)((long)this + offsets.m_flSimulationTime);
}






//////////////////////////////////////////////////////////////////////////////////////////////



void CBaseEntity::SetCurrentCommand(CUserCmd *cmd)
{
    *(CUserCmd**)((DWORD)this + offsets.m_hConstraintEntity - 0xC) = cmd;
}

int* CBaseEntity::SetFlags()
{
    return (int*)((long)this + offsets.m_fFlags);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int CBaseCombatWeapon::get_weapon_index()
{
    __asm
    {
        MOV EDI, this
        LEA ECX, DWORD PTR DS : [EDI + 0x8]
        MOV EDX, DWORD PTR DS : [ECX]
        CALL DWORD PTR DS : [EDX + 0x28]
    }
}

WeaponInfo_t* CBaseCombatWeapon::get_weapon_data()
{
    typedef WeaponInfo_t*(__thiscall* OriginalFn)(void*);
    return U::GetVFunc<OriginalFn>(this, 460)(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////

short CBaseCombatWeapon::get_item_def_index()
{
    return *(short*)((long)this + offsets.m_iItemDefinitionIndex);
}

//////////////////////////////////////////////////////////////////////////////////////////////

float CBaseCombatWeapon::get_next_primary_attack()
{
    return *(float*)((long)this + offsets.m_flNextPrimaryAttack);
}

float CBaseCombatWeapon::get_next_secondary_attack()
{
    return *(float*)((long)this + offsets.m_flNextSecondaryAttack);
}

float CBaseCombatWeapon::get_next_revolver_attack()
{
    return *(float*)((long)this + offsets.m_flPostponeFireReadyTime);
}

//////////////////////////////////////////////////////////////////////////////////////////////

int CBaseCombatWeapon::get_clip1()
{
    return *(int*)((long)this + offsets.m_iClip1); //0x3204
}

int CBaseCombatWeapon::get_clip2()
{
    return *(int*)((long)this + offsets.m_iPrimaryReserveAmmoCount);
}

bool CBaseCombatWeapon::is_empty()
{
    return (this->get_clip1() == 0);
}

bool CBaseCombatWeapon::is_reloading()
{
    return *(bool*)((long)this + 0x3285);
}

//////////////////////////////////////////////////////////////////////////////////////////////

void CBaseCombatWeapon::update_accuracy_penalty()
{
    //	typedef void(__thiscall *FunctionFn)(void*);
        //reinterpret_cast<FunctionFn>(*reinterpret_cast<uintptr_t*>(*reinterpret_cast<uintptr_t*>(this) + 0x748))((void*)this);

    typedef void(__thiscall* OriginalFn)(void*);
    U::GetVFunc<OriginalFn>(this, 483)(this);
}

float CBaseCombatWeapon::get_cone()
{
    typedef float(__thiscall* OriginalFn)(void*);
    return U::GetVFunc<OriginalFn>(this, 481)(this);
}

float CBaseCombatWeapon::get_spread()
{
    typedef float(__thiscall* OriginalFn)(void*);
    return U::GetVFunc<OriginalFn>(this, 452)(this);
}

float CBaseCombatWeapon::get_inaccuracy()
{
    typedef float(__thiscall* OriginalFn)(void*);
    return U::GetVFunc<OriginalFn>(this, 482)(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////

const char* CBaseCombatWeapon::get_weapon_name()
{
    auto id = this->get_item_def_index();

    switch (id)
    {
    case weapon_ak47: return		"ak47";
    case weapon_aug: return			"aug";
    case weapon_awp: return			"awp";
    case weapon_bizon: return		"bizon";
    case weapon_cz75: return		"cz75";
    case weapon_deagle: return		"deagle";
    case weapon_elite: return		"elite";
    case weapon_fiveseven: return	"five seven";
    case weapon_glock: return		"glock";
    case weapon_famas: return		"famas";
    case weapon_g3sg1: return		"g3sg1";
    case weapon_galilar: return		"galil";
    case weapon_hkp2000: return		"p2000";
    case weapon_mag7: return		"mag7";
    case weapon_m249: return		"m249";
    case weapon_m4a4: return		"m4a4";
    case weapon_m4a1_silencer: return "m4a1";
    case weapon_mac10: return		"mac10";
    case weapon_mp5: return "mp5";

    case weapon_mp7: return			"mp7";
    case weapon_mp9: return			"mp9";
    case weapon_nova: return		"nova";
    case weapon_negev: return		"negev";
    case weapon_p90: return			"p90";
    case weapon_p250: return		"p250";
    case weapon_revolver: return	"revolver";
    case weapon_sawedoff: return	"sawed off";
    case weapon_scar20: return		"scar20";
    case weapon_sg553: return		"sg553";
    case weapon_ssg08: return		"scout";
    case weapon_tec9: return		"tec9";
    case weapon_ump45: return		"ump";
    case weapon_usp: return			"usp";
    case weapon_xm1014: return		"xm1014";

    case weapon_taser: return		"zeus";
    case weapon_flashbang: return	"flash";
    case weapon_hegrenade: return	"nade";
    case weapon_smokegrenade: return "smoke";
    case weapon_molotov: return		"molotov";
    case weapon_decoy: return		"decoy";
    case weapon_incgrenade: return  "incendiary";
    case weapon_tagrenade: return	"tactical";
    case weapon_c4: return			"c4";

    case WEAPON_HEALTHSHOT: return "health shot";
    case WEAPON_FISTS: return "fists";
    case WEAPON_BREACHCHARGE: return "satchel";
    case WEAPON_TABLET: return "tablet";
    case WEAPON_MELEE: return "melee";
    case WEAPON_AXE: return "axe";
    case WEAPON_HAMMER: return "hammer";
    case WEAPON_SPANNER: return "wrench";
    case WEAPON_KNIFE_GHOST: return "ghost";
    case WEAPON_FIREBOMB: return "molotov";
    case WEAPON_DIVERSION: return "decoy";
    case WEAPON_FRAG_GRENADE: return "hegrenade";

    default: return  "knife";
    }
}


wepgr CBaseCombatWeapon::get_weapon_group(int id)
{
    switch (id)
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_tec9: 
    case weapon_hkp2000: 
    case weapon_p250: 
    case weapon_cz75: 
    case weapon_revolver: 
    case weapon_usp: return wepgr::pistols;

    case weapon_mac10: 
    case weapon_p90: 
    case weapon_ump45: 
    case weapon_bizon: 
    case weapon_mp7: 
    case weapon_mp9: 
    case weapon_mp5: return wepgr::smgs;

    case weapon_ak47: 
    case weapon_aug: 
    case weapon_famas: 
    case weapon_galilar: 
    case weapon_m249: 
    case weapon_m4a1_silencer: 
    case weapon_m4a4: 
    case weapon_negev: 
    case weapon_sg553: return wepgr::rifles;

    case weapon_xm1014: 
    case weapon_mag7: 
    case weapon_sawedoff: 
    case weapon_nova: return wepgr::shotguns;

    case weapon_awp: 
    case weapon_ssg08: return wepgr::snipers;

    case weapon_scar20: 
    case weapon_g3sg1: return wepgr::autosnipers;

    default: return wepgr::knives;
    }
}



bool CBaseCombatWeapon::is_gun()
{
    switch (this->get_item_def_index())
    {
    case weapon_ak47: 
    case weapon_aug: 
    case weapon_awp: 
    case weapon_bizon: 
    case weapon_cz75: 
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_famas: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_g3sg1: 
    case weapon_galilar: 
    case weapon_hkp2000: 
    case weapon_m249: 
    case weapon_m4a1_silencer: 
    case weapon_m4a4: 
    case weapon_mac10: 
    case weapon_mag7: 
    case weapon_negev: 
    case weapon_mp5: 
    case weapon_mp7: 
    case weapon_mp9: 
    case weapon_nova: 
    case weapon_p250: 
    case weapon_p90: 
    case weapon_revolver: 
    case weapon_sawedoff: 
    case weapon_scar20: 
    case weapon_sg553: 
    case weapon_ssg08: 
    case weapon_tec9: 
    case weapon_ump45: 
    case weapon_usp: 
    case weapon_xm1014: return true;

    default: return false;
    }
}

bool CBaseCombatWeapon::is_pistol()
{
    switch (this->get_item_def_index())
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_tec9: 
    case weapon_hkp2000: 
    case weapon_p250: 
    case weapon_cz75: 
    case weapon_revolver: 
    case weapon_usp: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_pistol_semi()
{
    switch (this->get_item_def_index())
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_tec9: 
    case weapon_hkp2000: 
    case weapon_p250: 
    case weapon_usp: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_smg()
{
    switch (this->get_item_def_index())
    {
    case weapon_mac10: 
    case weapon_p90: 
    case weapon_ump45: 
    case weapon_bizon: 
    case weapon_mp5: 
    case weapon_mp7: 
    case weapon_mp9: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_rifle()
{
    switch (this->get_item_def_index())
    {
    case weapon_ak47: 
    case weapon_aug: 
    case weapon_famas: 
    case weapon_galilar: 
    case weapon_m4a1_silencer: 
    case weapon_m4a4: 
    case weapon_sg553: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_sniper()
{
    switch (this->get_item_def_index())
    {
    case weapon_awp: return true;
    case weapon_ssg08: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_other()
{
    switch (this->get_item_def_index())
    {
    case weapon_m249: 
    case weapon_xm1014: 
    case weapon_mag7: 
    case weapon_sawedoff: 
    case weapon_nova: 
    case weapon_negev: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_knife()
{
    switch (this->get_item_def_index())
    {
    case weapon_knife_ct: 
    case weapon_knife_t: 
    case weapon_bayonet: 
    case weapon_flip: 
    case weapon_gut: 
    case weapon_karambit: 
    case weapon_m9bayonet: 
    case weapon_huntsman: 
    case weapon_falchion: 
    case weapon_bowie: 
    case weapon_butterfly: 
    case weapon_daggers: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_grenade()
{
    switch (this->get_item_def_index())
    {
    case weapon_decoy: 
    case weapon_flashbang: 
    case weapon_hegrenade: 
    case weapon_smokegrenade: 
    case weapon_incgrenade: 
    case weapon_molotov: 
    case weapon_tagrenade: 
    case WEAPON_FIREBOMB: 
    case WEAPON_DIVERSION: 
    case WEAPON_FRAG_GRENADE: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_c4()
{
    auto id = this->get_item_def_index();
    return (this->get_item_def_index() == weapon_c4);
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool CBaseCombatWeapon::is_gun_id(const int id)
{
    switch (id)
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_ak47: 
    case weapon_aug: 
    case weapon_awp: 
    case weapon_famas: 
    case weapon_g3sg1: 
    case weapon_galilar: 
    case weapon_m249: 
    case weapon_m4a4: 
    case weapon_mac10: 
    case weapon_p90: 
    case weapon_ump45: 
    case weapon_xm1014: 
    case weapon_bizon: 
    case weapon_mag7: 
    case weapon_negev: 
    case weapon_sawedoff: 
    case weapon_tec9: 
    case weapon_m4a1_silencer: 
    case weapon_usp: 
    case weapon_cz75: 
    case weapon_revolver: 
    case weapon_hkp2000: 
    case weapon_mp5: 
    case weapon_mp7: 
    case weapon_mp9: 
    case weapon_nova: 
    case weapon_p250: 
    case weapon_scar20: 
    case weapon_sg553: 
    case weapon_ssg08: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_pistol_id(const int id)
{
    switch (id)
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_tec9: 
    case weapon_hkp2000: 
    case weapon_p250: 
    case weapon_cz75: 
    case weapon_revolver: 
    case weapon_usp: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_pistol_semi_id(const int id)
{
    switch (id)
    {
    case weapon_deagle: 
    case weapon_elite: 
    case weapon_fiveseven: 
    case weapon_glock: 
    case weapon_tec9: 
    case weapon_hkp2000: 
    case weapon_p250: 
    case weapon_usp: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_smg_id(const int id)
{
    switch (id)
    {
    case weapon_mac10: 
    case weapon_p90: 
    case weapon_ump45: 
    case weapon_bizon: 
    case weapon_mp5: 
    case weapon_mp7: 
    case weapon_mp9: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_rifle_id(const int id)
{
    switch (id)
    {
    case weapon_ak47: 
    case weapon_aug: 
    case weapon_famas: 
    case weapon_galilar: 
    case weapon_m4a4: 
    case weapon_sg553: 
    case weapon_m4a1_silencer: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_sniper_id(const int id)
{
    switch (id)
    {
    case weapon_awp: 
    case weapon_ssg08: 
    case weapon_scar20: 
    case weapon_g3sg1: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_other_id(const int id)
{
    switch (id)
    {
    case weapon_m249: 
    case weapon_xm1014: 
    case weapon_mag7: 
    case weapon_sawedoff: 
    case weapon_nova: 
    case weapon_negev: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_knife_id(const int id)
{
    switch (id)
    {
    case weapon_knife_ct: 
    case weapon_knife_t: 
    case weapon_bayonet: 
    case weapon_flip: 
    case weapon_gut: 
    case weapon_karambit: 
    case weapon_m9bayonet: 
    case weapon_huntsman: 
    case weapon_falchion: 
    case weapon_bowie: 
    case weapon_butterfly: 
    case weapon_daggers: 
    case weapon_ursus: 
    case weapon_navaja: 
    case weapon_stiletto: 
    case weapon_talon: 
    case WEAPON_FISTS: 
    case WEAPON_MELEE: 
    case WEAPON_AXE: 
    case WEAPON_HAMMER: 
    case WEAPON_SPANNER: 
    case WEAPON_KNIFE_GHOST: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_grenade_id(const int id)
{
    switch (id)
    {
    case weapon_decoy: 
    case weapon_flashbang: 
    case weapon_hegrenade: 
    case weapon_smokegrenade: 
    case weapon_incgrenade: 
    case weapon_molotov: 
    case weapon_tagrenade: 
    case WEAPON_FIREBOMB: 
    case WEAPON_DIVERSION: 
    case WEAPON_FRAG_GRENADE: return true;
    default: return false;
    }
}

bool CBaseCombatWeapon::is_c4_id(const int id)
{
    return (id == weapon_c4);
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool CBaseCombatWeapon::grenade_pin_pulled()
{
    return *(bool*)((long)this + offsets.m_bPinPulled);
}

float CBaseCombatWeapon::grenade_throw_time()
{
    return *(float*)((long)this + offsets.m_fThrowTime);
}

float CBaseCombatWeapon::grenade_throw_strength()
{
    return *(float*)((long)this + offsets.m_flThrowStrength);
}

//////////////////////////////////////////////////////////////////////////////////////////////