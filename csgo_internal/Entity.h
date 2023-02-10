#pragma once

enum MoveType_t
{
	MOVETYPE_NONE = 0,
	MOVETYPE_ISOMETRIC,
	MOVETYPE_WALK,
	MOVETYPE_STEP,
	MOVETYPE_FLY,
	MOVETYPE_FLYGRAVITY,
	MOVETYPE_VPHYSICS,
	MOVETYPE_PUSH,
	MOVETYPE_NOCLIP,
	MOVETYPE_LADDER,
	MOVETYPE_OBSERVER,
	MOVETYPE_CUSTOM,
	MOVETYPE_LAST = MOVETYPE_CUSTOM,
	MOVETYPE_MAX_BITS = 4
};

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

class CBaseCombatWeapon;
enum SolidType_t;
class CBaseHandle;
class CBaseEntity;
class IHandleEntity;
class IClientNetworkable;
class IClientRenderable;
class ICollideable;
class IClientEntity;
class IClientThinkable;
class IClientUnknown;
class IClientModelRenderable;
class IClientAlphaProperty;

class CBaseAnimating;
class C_BaseAnimatingOverlay;
struct Ray_t;
class CGameTrace;
typedef CGameTrace trace_t;
class CMouthInfo;
class IClientEntityInternal;
struct SpatializationInfo_t;

class ICollideable {
public:
	// Gets at the entity handle associated with the collideable
	virtual IHandleEntity*		GetEntityHandle() = 0;

	virtual const vector&		OBBMins() const = 0;
	virtual const vector&		OBBMaxs() const = 0;

	virtual void				WorldSpaceTriggerBounds(vector *pVecWorldMins, vector *pVecWorldMaxs) const = 0;
	virtual bool				TestCollision(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual bool				TestHitboxes(const Ray_t &ray, unsigned int fContentsMask, trace_t& tr) = 0;
	virtual int					GetCollisionModelIndex() = 0;
	virtual const model_t*		GetCollisionModel() = 0;

	virtual const vector&		GetCollisionOrigin() const = 0;
	virtual const QAngle&		GetCollisionAngles() const = 0;
	virtual const matrix3x4_t&	CollisionToWorldTransform() const = 0;

	virtual SolidType_t			GetSolid() const = 0;
	virtual int					GetSolidFlags() const = 0;
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual int					GetCollisionGroup() const = 0;
	virtual void				WorldSpaceSurroundingBounds(vector *pVecMins, vector *pVecMaxs) = 0;
	virtual bool				ShouldTouchTrigger(int triggerSolidFlags) const = 0;
	virtual const matrix3x4_t*	GetRootParentToWorldTransform() const = 0;
};

class IHandleEntity {
public:
	virtual ~IHandleEntity() {}
	virtual void				SetRefEHandle(const CBaseHandle &handle) = 0;
	virtual const CBaseHandle&	GetRefEHandle() const = 0;
};

class IClientRenderable {
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;

	virtual vector const&		GetRenderOrigin(void) = 0;
	virtual QAngle const&		GetRenderAngles(void) = 0;
	virtual bool ShouldDraw(void) = 0; // 3
	virtual int GetRenderFlags(void) = 0; // 4
	virtual void Unused(void) const {} // 5
	virtual void GetShadowHandle() const = 0; // 6
	virtual void* RenderHandle() = 0; // 7
	virtual const model_t* GetModel() const = 0; // 8
	virtual int DrawModel(int flags) = 0; // 9
	virtual int GetBody() = 0; // 10
	virtual void GetColorModulation(float* color) = 0; // 11
	virtual void Function12(); // 12
	virtual bool SetupBones(matrix3x4a_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0; // 13
	virtual void SetupWeights(const matrix3x4a_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0; // 14
	virtual void DoAnimationEvents(void) = 0; // 15
	virtual void* GetPVSNotifyInterface() = 0; // 16
	virtual void GetRenderBounds(vector& mins, vector& maxs) = 0; // 17
	virtual void GetRenderBoundsWorldspace(vector& mins, vector& maxs) = 0; // 18
};

class IClientNetworkable {
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass*	GetClientClass() = 0;
	virtual void			NotifyShouldTransmit(int state) = 0;
	virtual void			OnPreDataChanged(int updateType) = 0;
	virtual void			OnDataChanged(int updateType) = 0;
	virtual void			PreDataUpdate(int updateType) = 0;
	virtual void			PostDataUpdate(int updateType) = 0;
	virtual bool			IsDormant(void) = 0;
	virtual int				entindex(void) const = 0;
	virtual void			ReceiveMessage(int classID, byte& msg) = 0; //bf_read&
	virtual void*			GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;

	virtual void			OnDataUnchangedInPVS() = 0;
};

class IClientUnknown : public IHandleEntity {
public:
	virtual ICollideable*			GetCollideable() = 0;
	virtual IClientNetworkable*		GetClientNetworkable() = 0;
	virtual IClientRenderable*		GetClientRenderable() = 0;
	virtual IClientEntity*			GetIClientEntity() = 0;
	virtual CBaseEntity*			GetBaseEntity() = 0;
	virtual IClientThinkable*		GetClientThinkable() = 0;
	//virtual IClientModelRenderable*	GetClientModelRenderable() = 0;
	virtual IClientAlphaProperty*	GetClientAlphaProperty() = 0;
};

class IClientThinkable {
public:
	virtual IClientUnknown*		GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void*				GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
public:
	virtual void				Release(void) = 0;
	virtual const vector&		GetAbsOrigin(void) const = 0;
	virtual const QAngle&		GetAbsAngles(void) const = 0;
	virtual CMouthInfo*			GetMouth(void) = 0;
	virtual bool				GetSoundSpatialization(SpatializationInfo_t& info) = 0;
	virtual bool				IsBlurred(void) = 0;
};

class CBaseCombatWeapon;
class WeaponInfo_t;
class CBaseEntity : public IClientEntity
{
public:
	int					get_health();
	int					get_armor();
	bool				has_helmet();
	bool				is_alive();

	bool				is_player();
	int					get_team();
	bool				is_enemy();

	bool				is_dormant();
	bool				is_immune();

	int					get_flags();
	int					get_movetype();
	vector				get_velocity();

	CUtlVector < C_AnimationLayer >& GetAnimOverlays();
	C_AnimationLayer* GetAnimOverlay(int i);
	int GetNumAnimOverlays();
	int GetSequenceActivity(int sequence);

	int					get_index();
	CBaseCombatWeapon*	get_weapon();
	ClientClass*		get_client_class();

	float*				get_flash_alpha();

	bool				is_scoped();

	bool				has_bomb();

	bool				setup_bones(matrix3x4_t *pBoneToWorldOut);
	bool				setup_bones_pvs(matrix3x4_t *pBoneToWorldOut);
	ICollideable*		get_collideable();
	const matrix3x4a_t& get_matrix_transform();

	model_t*			get_model();
	int					get_hitbox_set();

	QAngle				get_aim_punch();
	QAngle				get_view_punch();

	float				bomb_timer();
	bool				bomb_ticking();

	////random crap////random crap////random crap////random crap////
	int					get_owner();
	vector				get_eye_pos();
	int					get_tickbase();
	float				get_next_attack();
	long			get_spec_target();
	int					get_shots_fired();
	float				get_simulation_time();
	////random crap////random crap////random crap////random crap////


	void				SetCurrentCommand(CUserCmd *cmd);
	int*				SetFlags();
};

class CEnvTonemapControllerd
{
public:
    bool& IsUseCustomAutoExposureMin()
    {
        return *(bool*)((uintptr_t)this + offsets.m_bUseCustomAutoExposureMax);
    }

    bool& IsUseCustomAutoExposureMax()
    {
        return *(bool*)((uintptr_t)this + offsets.m_bUseCustomAutoExposureMin);
    }

    float& GetCustomAutoExposureMin()
    {
        return *(float*)((uintptr_t)this + offsets.m_flCustomAutoExposureMin);
    }

    float& GetCustomAutoExposureMax()
    {
        return *(float*)((uintptr_t)this + offsets.m_flCustomAutoExposureMax);
    }
};

class CBaseCombatWeapon
{
public:
	int				get_weapon_index();
	WeaponInfo_t*	get_weapon_data();

	short			get_item_def_index();

	float			get_next_primary_attack();
	float			get_next_secondary_attack();
	float			get_next_revolver_attack();

	int				get_clip1();
	int				get_clip2();
	bool			is_empty();
	bool			is_reloading();

	void			update_accuracy_penalty();
	float			get_cone();
	float			get_spread();
	float			get_inaccuracy();

	const char*		get_weapon_name();
	wepgr			get_weapon_group(int id);

	bool			is_gun();
	bool			is_pistol();
	bool			is_pistol_semi();
	bool			is_smg();
	bool			is_rifle();
	bool			is_sniper();
	bool			is_other();
	bool			is_knife();
	bool			is_grenade();
	bool			is_c4();

	bool			is_gun_id(const int id);
	bool			is_pistol_id(const int id);
	bool			is_pistol_semi_id(const int id);
	bool			is_smg_id(const int id);
	bool			is_rifle_id(const int id);
	bool			is_sniper_id(const int id);
	bool			is_other_id(const int id);
	bool			is_knife_id(const int id);
	bool			is_grenade_id(const int id);
	bool			is_c4_id(const int id);

	bool			grenade_pin_pulled();
	float			grenade_throw_time();
	float			grenade_throw_strength();
};

class WeaponInfo_t {
public:
	char _0x0000[20];
	__int32 iMaxClip1;			//0x0014 
	char _0x0018[12];
	__int32 max_reserved_ammo;	//0x0024 
	char _0x0028[96];
	char* hud_name;				//0x0088 
	char* weapon_name;			//0x008C 
	char _0x0090[60];
	__int32 type;				//0x00CC 
	__int32 price;				//0x00D0 
	__int32 reward;				//0x00D4 
	char _0x00D8[20];
	BYTE full_auto;				//0x00EC 
	char _0x00ED[3];
	__int32 m_iDamage;				//0x00F0 
	float flArmorRatio;			//0x00F4 
	__int32 iBullets;			//0x00F8 
	float m_flPenetration;			//0x00FC 
	char _0x0100[8];
	float   m_flRange;
	float   m_flRangeModifier;
	float   flThrowVelocity;
	char _0x0110[12];
	BYTE silencer;				//0x0120 
	char _0x0121[15];
	float max_speed;			//0x0130 
	float max_speed_alt;		//0x0134 
	char _0x0138[76];
	__int32 recoil_seed;		//0x0184 
	char _0x0188[32];
};// Size=0x01A8
/*
class WeaponInfo_t
{
public:
    char pad_0000[4]; //0x0000
    char *ConsoleName; //0x0004
    char pad_0008[12]; //0x0008
    int iMaxClip1; //0x0014
    char pad_0018[12]; //0x0018
    int iMaxClip2; //0x0024
    char pad_0028[4]; //0x0028
    char *szWorldModel; //0x002C
    char *szViewModel; //0x0030
    char *szDropedModel; //0x0034
    char pad_0038[4]; //0x0038
    char *N00000984; //0x003C
    char pad_0040[56]; //0x0040
    char *szEmptySound; //0x0078
    char pad_007C[4]; //0x007C
    char *szBulletType; //0x0080
    char pad_0084[4]; //0x0084
    char *szHudName; //0x0088
    char *szWeaponName; //0x008C
    char pad_0090[60]; //0x0090
    int WeaponType; //0x00CC
    int iWeaponPrice; //0x00D0
    int iKillAward; //0x00D4
    char *szAnimationPrefex; //0x00D8
    float flCycleTime; //0x00DC
    float flCycleTimeAlt; //0x00E0
    float flTimeToIdle; //0x00E4
    float flIdleInterval; //0x00E8
    bool bFullAuto; //0x00EC
    char pad_00ED[3]; //0x00ED
    int m_iDamage; //0x00F0
    float flArmorRatio; //0x00F4
    int iBullets; //0x00F8
    float m_flPenetration; //0x00FC
    float flFlinchVelocityModifierLarge; //0x0100
    float flFlinchVelocityModifierSmall; //0x0104
    float m_flRange; //0x0108
    float m_flRangeModifier; //0x010C
    char pad_0110[28]; //0x0110
    int iCrosshairMinDistance; //0x012C
    float flMaxPlayerSpeed; //0x0130
    float flMaxPlayerSpeedAlt; //0x0134
    char pad_0138[4]; //0x0138
    float flSpread; //0x013C
    float flSpreadAlt; //0x0140
    float flInaccuracyCrouch; //0x0144
    float flInaccuracyCrouchAlt; //0x0148
    float flInaccuracyStand; //0x014C
    float flInaccuracyStandAlt; //0x0150
    float flInaccuracyJumpIntial; //0x0154
    float flInaccuracyJump; //0x0158
    float flInaccuracyJumpAlt; //0x015C
    float flInaccuracyLand; //0x0160
    float flInaccuracyLandAlt; //0x0164
    float flInaccuracyLadder; //0x0168
    float flInaccuracyLadderAlt; //0x016C
    float flInaccuracyFire; //0x0170
    float flInaccuracyFireAlt; //0x0174
    float flInaccuracyMove; //0x0178
    float flInaccuracyMoveAlt; //0x017C
    float flInaccuracyReload; //0x0180
    int iRecoilSeed; //0x0184
    float flRecoilAngle; //0x0188
    float flRecoilAngleAlt; //0x018C
    float flRecoilVariance; //0x0190
    float flRecoilAngleVarianceAlt; //0x0194
    float flRecoilMagnitude; //0x0198
    float flRecoilMagnitudeAlt; //0x019C
    float flRecoilMagnatiudeVeriance; //0x01A0
    float flRecoilMagnatiudeVerianceAlt; //0x01A4
    float flRecoveryTimeCrouch; //0x01A8
    float flRecoveryTimeStand; //0x01AC
    float flRecoveryTimeCrouchFinal; //0x01B0
    float flRecoveryTimeStandFinal; //0x01B4
    int iRecoveryTransititionStartBullet; //0x01B8
    int iRecoveryTransititionEndBullet; //0x01BC
    bool bUnzoomAfterShot; //0x01C0
    char pad_01C1[31]; //0x01C1
    char *szWeaponClass; //0x01E0
    char pad_01E4[56]; //0x01E4
    float flInaccuracyPitchShift; //0x021C
    float flInaccuracySoundThreshold; //0x0220
    float flBotAudibleRange; //0x0224
    char pad_0228[12]; //0x0228
    bool bHasBurstMode; //0x0234

}; //Size=0x0240*/