#pragma once

class IHandleEntity;
struct Ray_t;
class CGameTrace;
typedef CGameTrace trace_t;
class ICollideable;
class ITraceListData;
class CPhysCollide;
struct cplane_t;
struct virtualmeshlist_t;

enum class TraceType
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class VectorAligned : public vector
{
public:
	VectorAligned()
	{}

	VectorAligned(const vector& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity *pEntity, int contentsMask) = 0;
	virtual TraceType GetTraceType() const = 0;
};


//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* pEntityHandle, int /*contentsMask*/)
	{
		return !(pEntityHandle == pSkip || pEntityHandle == pSkip2);
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}
	void* pSkip;
	void* pSkip2;
};

class CTraceFilterEntitiesOnly : public ITraceFilter
{
public:
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_ENTITIES_ONLY;
	}
};


//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class CTraceFilterWorldOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return false;
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_WORLD_ONLY;
	}
};

class CTraceFilterWorldAndPropsOnly : public ITraceFilter
{
public:
	bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return false;
	}
	virtual TraceType GetTraceType() const
	{
		return TraceType::TRACE_EVERYTHING;
	}
};

class CTraceFilterHitAll : public CTraceFilter
{
public:
	virtual bool ShouldHitEntity(IHandleEntity* /*pServerEntity*/, int /*contentsMask*/)
	{
		return true;
	}
};


enum class DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

//-----------------------------------------------------------------------------
// Enumeration interface for EnumerateLinkEntities
//-----------------------------------------------------------------------------
class IEntityEnumeratord
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(IHandleEntity *pHandleEntity) = 0;
};

class Vector4D
{
public:
	// Members
	float x, y, z, w;
};

struct BrushSideInfo_t
{
	Vector4D plane;               // The plane of the brush side
	unsigned short bevel;    // Bevel plane?
	unsigned short thin;     // Thin?
};

class CPhysCollide;

struct vcollide_t
{
	unsigned short solidCount : 15;
	unsigned short isPacked : 1;
	unsigned short descSize;
	// VPhysicsSolids
	CPhysCollide   **solids;
	char           *pKeyValues;
	void           *pUserData;
};

struct cmodel_t
{
	vector         mins, maxs;
	vector         origin;        // for sounds or lights
	int            headnode;
	vcollide_t     vcollisionData;
};

struct csurface_t
{
	const char     *name;
	short          surfaceProps;
	unsigned short flags;         // BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

struct cplane_t
{
	vector	normal;
	float	dist;
	byte	type;
	byte	signbits;
	byte	pad[2];
};

//-----------------------------------------------------------------------------
// A ray...
//-----------------------------------------------------------------------------
struct Ray_t
{
	VectorAligned  m_Start;  // starting point, centered within the extents
	VectorAligned  m_Delta;  // direction + length of the ray
	VectorAligned  m_StartOffset; // Add this to m_Start to get the actual ray start
	VectorAligned  m_Extents;     // Describes an axis aligned box extruded along a ray
	const matrix3x4_t *m_pWorldAxisTransform;
	bool m_IsRay;  // are the extents zero?
	bool m_IsSwept;     // is delta != 0?

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(vector const& start, vector const& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.Init();

		m_pWorldAxisTransform = NULL;
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		m_StartOffset.Init();
		VectorCopy(start, m_Start);
	}

	void Init(vector const& start, vector const& end, vector const& mins, vector const& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = NULL;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		// Offset m_Start to be in the center of the box...
		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
	vector InvDelta() const
	{
		vector vecInvDelta;
		for (int iAxis = 0; iAxis < 3; ++iAxis) {
			if (m_Delta[iAxis] != 0.0f) {
				vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
			}
			else {
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}

private:
};

class CBaseTrace
{
public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:

	// these members are aligned!!
	vector         startpos;                // start position
	vector         endpos;                  // final position
	cplane_t       plane;                   // surface normal at impact

	float          fraction;                // time completed, 1.0 = didn't hit anything

	int            contents;                // contents on other side of surface hit
	unsigned short dispFlags;               // displacement flags for marking surfaces with data

	bool           allsolid;                // if true, plane is not valid
	bool           startsolid;              // if true, the initial point was in a solid area

	CBaseTrace() {}

};

class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;
	bool DidHit() const;
	bool IsVisible() const;

public:

	float               fractionleftsolid;  // time we left a solid, only valid if we started in solid
	csurface_t          surface;            // surface hit (impact surface)
	int                 hitgroup;           // 0 == generic, non-zero is specific body part
	short               physicsbone;        // physics bone hit by trace in studio
	unsigned short      worldSurfaceIndex;  // Index of the msurface2_t, if applicable
	CBaseEntity*       entity;
	int                 hitbox;                       // box hit by trace in studio

	CGameTrace() {}

	//private:
	// No copy constructors allowed
	CGameTrace(const CGameTrace& other) :
		fractionleftsolid(other.fractionleftsolid),
		surface(other.surface),
		hitgroup(other.hitgroup),
		physicsbone(other.physicsbone),
		worldSurfaceIndex(other.worldSurfaceIndex),
		entity(other.entity),
		hitbox(other.hitbox)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
	}

	CGameTrace& CGameTrace::operator=(const CGameTrace& other)
	{
		startpos = other.startpos;
		endpos = other.endpos;
		plane = other.plane;
		fraction = other.fraction;
		contents = other.contents;
		dispFlags = other.dispFlags;
		allsolid = other.allsolid;
		startsolid = other.startsolid;
		fractionleftsolid = other.fractionleftsolid;
		surface = other.surface;
		hitgroup = other.hitgroup;
		physicsbone = other.physicsbone;
		worldSurfaceIndex = other.worldSurfaceIndex;
		entity = other.entity;
		hitbox = other.hitbox;
		return *this;
	}
};

inline bool CGameTrace::DidHit() const
{
	return fraction < 1 || allsolid || startsolid;
}

inline bool CGameTrace::IsVisible() const
{
	return fraction > 0.97f;
}





#include "IVModelInfo.h"
struct draw_model_info
{
	studiohdr_t* studio_hdr;
	void* hardware_data;
	void* kdk;
	int skin;
	int body;
	int hitbox_set;
	CBaseEntity* entity;
	int lod;
	void* colour_mesh;
	bool static_lighting;
	void* ckdk;
	void* cxkdk;

	//	PAD(0x8)
};










/*
#pragma once

class VectorAligned : public vector
{
public:
	VectorAligned()
	{}

	VectorAligned(const vector& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY, // NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY, // NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS, // NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
	Ray_t()
	{ }

	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;
	const matrix3x4_t* m_pWorldAxisTransform;
	bool m_IsRay;
	bool m_IsSwept;

	void Init(vector vecStart, vector vecEnd)
	{
		m_Delta = VectorAligned(vecEnd - vecStart);
		m_IsSwept = (m_Delta.LengthSqr() != 0);
		m_Extents.Zero();
		m_pWorldAxisTransform = nullptr;
		m_IsRay = true;
		m_StartOffset.Zero();
		m_Start = vecStart;
	}

	void Init2(vector const& start, vector const& end, vector const& mins, vector const& maxs) {
		m_Delta = end - start;

		m_pWorldAxisTransform = nullptr;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = static_cast<VectorAligned>(start) + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

struct cplane_t
{
	vector normal;
	float dist;
	byte type;
	byte signbits;
	byte pad[2];
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType()
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities(void* pPassEnt1, void* pPassEnt2)
	{
		pPassEntity1 = pPassEnt1;
		pPassEntity2 = pPassEnt2;
	}

	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pPassEntity1;
	void* pPassEntity2;
};

typedef bool(*ShouldHitFunc_t)(IHandleEntity* pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter
{
public:
	// It does have a base, but we'll never network anything below here..
	CTraceFilterSimple(const IHandleEntity* passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
	virtual bool ShouldHitEntity(IHandleEntity* pHandleEntity, int contentsMask);

	virtual void SetPassEntity(const IHandleEntity* pPassEntity)
	{
		m_pPassEnt = pPassEntity;
	}

	virtual void SetCollisionGroup(int iCollisionGroup)
	{
		m_collisionGroup = iCollisionGroup;
	}

	const IHandleEntity* GetPassEntity(void)
	{
		return m_pPassEnt;
	}

private:
	const IHandleEntity* m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;
};

class CBaseTrace
{
public:
	vector startpos;
	vector endpos;
	cplane_t plane;

	float fraction;

	int contents;
	unsigned short dispFlags;

	bool allsolid;
	bool startsolid;

	CBaseTrace()
	{}
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld() const;
	bool DidHitNonWorldEntity() const;
	int GetEntityIndex() const;
	bool DidHit() const;
	bool IsVisible() const;

public:

	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	unsigned short worldSurfaceIndex;
	CBaseEntity* entity;
	int hitbox;

	CGameTrace()
	{ }

private:
	CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;

enum DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*#pragma once

class VectorAligned : public vector
{
public:
	VectorAligned() {}

	VectorAligned(const vector &vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = 0.f;
	}

	float w = 0.f;
};

struct BrushSideInfo_t
{
	vector plane;			// The plane of the brush side
	float planec;
	unsigned short bevel;	// Bevel plane?
	unsigned short thin;	// Thin?
};

enum DebugTraceCounterBehavior_t
{
	kTRACE_COUNTER_SET = 0,
	kTRACE_COUNTER_INC,
};

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
	Ray_t() { }

	VectorAligned		m_Start;
	VectorAligned		m_Delta;
	VectorAligned		m_StartOffset;
	VectorAligned		m_Extents;
	const matrix3x4_t	*m_pWorldAxisTransform = nullptr;
	bool				m_IsRay;
	bool				m_IsSwept;

	void Init(vector vecStart, vector vecEnd)
	{
		m_Delta = VectorAligned(vecEnd - vecStart);
		m_IsSwept = (m_Delta.LengthSqr() != 0);
		m_Extents.Zero();
		m_pWorldAxisTransform = nullptr;
		m_IsRay = true;
		m_StartOffset.Zero();
		m_Start = vecStart;
	}

	void Init2(vector const& start, vector const& end, vector const& mins, vector const& maxs) {
		m_Delta = end - start;

		m_pWorldAxisTransform = nullptr;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = static_cast<VectorAligned>(start) + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

struct cplane_t
{
	vector	normal;
	float	dist;
	byte	type;
	byte	signbits;
	byte	pad[2];
};

///////////////////////////////////////////////////////////////////////////////

enum MoveCollide_t {
	MOVECOLLIDE_DEFAULT = 0,

	// These ones only work for MOVETYPE_FLY + MOVETYPE_FLYGRAVITY
	MOVECOLLIDE_FLY_BOUNCE,	// bounces, reflects, based on elasticity of surface and object - applies friction (adjust velocity)
	MOVECOLLIDE_FLY_CUSTOM,	// Touch() will modify the velocity however it likes
	MOVECOLLIDE_FLY_SLIDE,  // slides along surfaces (no bounce) - applies friciton (adjusts velocity)

	MOVECOLLIDE_COUNT,		// Number of different movecollides

							// When adding new movecollide types, make sure this is correct
							MOVECOLLIDE_MAX_BITS = 3
};

// edict->solid values
// NOTE: Some movetypes will cause collisions independent of SOLID_NOT/SOLID_TRIGGER when the entity moves
// SOLID only effects OTHER entities colliding with this one when they move - UGH!

// Solid type basically describes how the bounding volume of the object is represented
// NOTE: SOLID_BBOX MUST BE 2, and SOLID_VPHYSICS MUST BE 6
// NOTE: These numerical values are used in the FGD by the prop code (see prop_dynamic)
enum SolidType_t {
	SOLID_NONE = 0,	// no solid model
	SOLID_BSP = 1,	// a BSP tree
	SOLID_BBOX = 2,	// an AABB
	SOLID_OBB = 3,	// an OBB (not implemented yet)
	SOLID_OBB_YAW = 4,	// an OBB, constrained so that it can only yaw
	SOLID_CUSTOM = 5,	// Always call into the entity for tests
	SOLID_VPHYSICS = 6,	// solid vphysics object, get vcollide from the model and collide with that
	SOLID_LAST,
};

enum SolidFlags_t {
	FSOLID_CUSTOMRAYTEST = 0x0001,	// Ignore solid type + always call into the entity for ray tests
	FSOLID_CUSTOMBOXTEST = 0x0002,	// Ignore solid type + always call into the entity for swept box tests
	FSOLID_NOT_SOLID = 0x0004,	// Are we currently not solid?
	FSOLID_TRIGGER = 0x0008,	// This is something may be collideable but fires touch functions
								// even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
								FSOLID_NOT_STANDABLE = 0x0010,	// You can't stand on this
								FSOLID_VOLUME_CONTENTS = 0x0020,	// Contains volumetric contents (like water)
								FSOLID_FORCE_WORLD_ALIGNED = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
								FSOLID_USE_TRIGGER_BOUNDS = 0x0080,	// Uses a special trigger bounds separate from the normal OBB
								FSOLID_ROOT_PARENT_ALIGNED = 0x0100,	// Collisions are defined in root parent's local coordinate space
								FSOLID_TRIGGER_TOUCH_DEBRIS = 0x0200,	// This trigger will touch debris objects
								FSOLID_MAX_BITS = 10
};

enum modtype_t {
	mod_bad = 0,
	mod_brush,
	mod_sprite,
	mod_studio
};

inline bool IsSolid(SolidType_t solidType, int nSolidFlags) {
	return (solidType != SOLID_NONE) && ((nSolidFlags & FSOLID_NOT_SOLID) == 0);
}



bool StandardFilterRules(IHandleEntity* pHandleEntity, int fContentsMask, int collisionGroup);

bool PassServerEntityFilter(const IHandleEntity *pTouch, const IHandleEntity *pPass);

bool BaseShouldHitEntity(IHandleEntity* pSkip, IHandleEntity *pHandleEntity, int m_collisionGroup, int contentsMask);

bool GameRulesShouldCollide(int collisionGroup0, int collisionGroup1);

class IGameRules {

};

class ITraceFilter {
public:
	ITraceFilter(void* skip = nullptr, int col = COLLISION_GROUP_NONE) : pSkip(skip), m_iCollisionGroup(col) {}
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		return !(pEntityHandle == pSkip);
		return BaseShouldHitEntity(static_cast<IHandleEntity*>(pSkip), pEntityHandle, m_iCollisionGroup, contentsMask);
	}
	virtual TraceType_t	GetTraceType() {
		return TRACE_EVERYTHING;
	}

	int m_iCollisionGroup;
	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter(void* skip = nullptr, int col = COLLISION_GROUP_NONE) {
		pSkip = skip;
		m_iCollisionGroup = col;
	}
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities(IHandleEntity *pPassEnt1, IHandleEntity *pPassEnt2, int collisionGroup) {
		pSkip = pPassEnt1;
		pSkip2 = pPassEnt2;
		m_iCollisionGroup = collisionGroup;
	};

	virtual bool ShouldHitEntity(IHandleEntity *pEntityHandle, int contentsMask) {
		return !(pEntityHandle == pSkip || pEntityHandle == pSkip2);
		if (!PassServerEntityFilter(pEntityHandle, pSkip2))
			return false;
		return BaseShouldHitEntity(pEntityHandle, (IHandleEntity*)pSkip, m_iCollisionGroup, contentsMask);
	}

	//virtual void SetPassEntity2(const IHandleEntity *pPassEntity2) { pSkip2 = pPassEntity2; }

public:
	const IHandleEntity *pSkip2;
};

class CTraceFilterNoPlayers : public CTraceFilter {
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle)
			return false;
		if (reinterpret_cast<CBaseEntity*>(pEntityHandle)->is_player())
			return false;
		return true;
	}
};

class CTraceFilterPlayersOnly : public ITraceFilter {
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle)
			return false;
		if (pEntityHandle->is_player())
			return true;
		return false;
	}

	virtual TraceType_t	GetTraceType() {
		return TRACE_ENTITIES_ONLY;
	}
};

class CTraceFilterEntitiesOnly : public ITraceFilter {
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle)
			return false;
		return true;
	}

	virtual TraceType_t	GetTraceType() {
		return TRACE_ENTITIES_ONLY;
	}
};

class CTraceFilterIgnoreWorld : public CTraceFilter {
public:
	virtual bool ShouldHitEntity(IHandleEntity* pEntityHandle, int contentsMask) {
		if (!pEntityHandle)
			return false;
		return true;
	}

	virtual TraceType_t	GetTraceType() {
		return TRACE_ENTITIES_ONLY;
	}
};

typedef bool(*ShouldHitFunc_t)(IHandleEntity *pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter {
public:
	CTraceFilterSimple(const CBaseEntity*passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL) {
		m_pPassEnt = (IHandleEntity*)passentity;
		m_collisionGroup = collisionGroup;
		m_pExtraShouldHitCheckFunction = pExtraShouldHitCheckFn;
	}
	virtual bool ShouldHitEntity(CBaseEntity* pHandleEntity, int contentsMask) {
		return !((IHandleEntity*)pHandleEntity == m_pPassEnt);
	}

	virtual void SetPassEntity(const IHandleEntity *pPassEntity) { m_pPassEnt = pPassEntity; }
	virtual void SetCollisionGroup(int iCollisionGroup) { m_collisionGroup = iCollisionGroup; }

	const IHandleEntity* GetPassEntity(void) { return m_pPassEnt; }

private:
	const IHandleEntity* m_pPassEnt;
	int m_collisionGroup;
	ShouldHitFunc_t m_pExtraShouldHitCheckFunction;

};

class CAutowallFilter : public CTraceFilter {
public:
	bool ShouldHitEntity(IHandleEntity* ent, unsigned int mask) {
		return true;// (ent != me && ent->GetRefEHandle() != me->GetRefEHandle() && ent->GetRefEHandle() != reinterpret_cast<IHandleEntity*>(mywep)->GetRefEHandle());
	}

	CBaseEntity* me;
	CBaseCombatWeapon* mywep;
};

class CBaseTrace
{
public:
	vector			startpos;
	vector			endpos;
	cplane_t		plane;

	float			fraction;

	int				contents;
	unsigned short	dispFlags;

	bool			allsolid;
	bool			startsolid;

	CBaseTrace() {}
};

struct csurface_t
{
	const char*		name;
	short			surfaceProps;
	unsigned short	flags;
};

class CGameTrace : public CBaseTrace 
{
public:
	bool                    DidHitWorld() const;
	bool                    DidHitNonWorldEntity() const;
	int                     GetEntityIndex() const;
	bool                    DidHit() const {
		return fraction < 1.f || allsolid || startsolid;
	}
	bool					IsVisible() const;

public:

	float                   fractionleftsolid;
	csurface_t              surface;
	int                     hitgroup;
	short                   physicsbone;
	unsigned short          worldSurfaceIndex;
	CBaseEntity*			entity;
	int                     hitbox;

	CGameTrace() {}

private:
	CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;


*/