#pragma once

#include "SDK.h"

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

typedef __int16					int16;
typedef unsigned __int16		uint16;
typedef __int32					int32;
typedef unsigned __int32		uint32;
typedef __int64					int64;
typedef unsigned __int64		uint64;
typedef unsigned short MaterialHandle_t;

// intp is an integer that can accomodate a pointer
// (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)
typedef intptr_t				intp;
typedef uintptr_t				uintp;

inline float BitsToFloat(uint32 i)
{
	union Convertor_t
	{
		float f;
		unsigned long ul;
	}tmp;
	tmp.ul = i;
	return tmp.f;
}

#define FLOAT32_NAN_BITS     (uint32)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define VEC_T_NAN FLOAT32_NAN

#define DECL_ALIGN(x)			__declspec( align( x ) )

#define ALIGN4 DECL_ALIGN(4)
#define ALIGN8 DECL_ALIGN(8)
#define ALIGN16 DECL_ALIGN(16)
#define ALIGN32 DECL_ALIGN(32)
#define ALIGN128 DECL_ALIGN(128)

//extern float( *pfSqrt )( float x );

//#define FastSqrt(x)			(*pfSqrt)(x)


#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

#define IN_ATTACK				(1 << 0)
#define IN_JUMP					(1 << 1)
#define IN_DUCK					(1 << 2)
#define IN_FORWARD				(1 << 3)
#define IN_BACK					(1 << 4)
#define IN_USE					(1 << 5)
#define IN_CANCEL				(1 << 6)
#define IN_LEFT					(1 << 7)
#define IN_RIGHT				(1 << 8)
#define IN_MOVELEFT				(1 << 9)
#define IN_MOVERIGHT			(1 << 10)
#define IN_ATTACK2				(1 << 11)
#define IN_RUN					(1 << 12)
#define IN_RELOAD				(1 << 13)
#define IN_ALT1					(1 << 14)
#define IN_ALT2					(1 << 15)
#define IN_SCORE				(1 << 16)
#define IN_SPEED				(1 << 17)
#define IN_WALK					(1 << 18)
#define IN_ZOOM					(1 << 19)
#define IN_WEAPON1				(1 << 20)
#define IN_WEAPON2				(1 << 21)
#define IN_BULLRUSH				(1 << 22)

#define	FL_ONGROUND				(1 << 0)	
#define FL_DUCKING				(1 << 1)	
#define	FL_WATERJUMP			(1 << 3)	
#define FL_ONTRAIN				(1 << 4) 
#define FL_INRAIN				(1 << 5)	
#define FL_FROZEN				(1 << 6) 
#define FL_ATCONTROLS			(1 << 7) 
#define	FL_CLIENT				(1 << 8)	
#define FL_FAKECLIENT			(1 << 9)	
#define	FL_INWATER				(1 << 10)

#define HIDEHUD_SCOPE			(1 << 11)

#define MAX_AREA_STATE_BYTES		32
#define MAX_AREA_PORTAL_STATE_BYTES 24

#define  Assert( _exp )										((void)0)
#define  AssertAligned( ptr )								((void)0)
#define  AssertOnce( _exp )									((void)0)
#define  AssertMsg( _exp, _msg )							((void)0)
#define  AssertMsgOnce( _exp, _msg )						((void)0)
#define  AssertFunc( _exp, _f )								((void)0)
#define  AssertEquals( _exp, _expectedValue )				((void)0)
#define  AssertFloatEquals( _exp, _expectedValue, _tol )	((void)0)
#define  Verify( _exp )										(_exp)
#define  VerifyEquals( _exp, _expectedValue )           	(_exp)

#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define TICK_INTERVAL			(i::globals->interval_per_tick)


#define TIME_TO_TICKS( dt ) ( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )

#define   DISPSURF_FLAG_SURFACE           (1<<0)
#define   DISPSURF_FLAG_WALKABLE          (1<<1)
#define   DISPSURF_FLAG_BUILDABLE         (1<<2)
#define   DISPSURF_FLAG_SURFPROP1         (1<<3)
#define   DISPSURF_FLAG_SURFPROP2         (1<<4)

#define   CONTENTS_EMPTY                0

#define   CONTENTS_SOLID                0x1       
#define   CONTENTS_WINDOW               0x2
#define   CONTENTS_AUX                  0x4
#define   CONTENTS_GRATE                0x8
#define   CONTENTS_SLIME                0x10
#define   CONTENTS_WATER                0x20
#define   CONTENTS_BLOCKLOS             0x40 
#define   CONTENTS_OPAQUE               0x80 
#define   LAST_VISIBLE_CONTENTS         CONTENTS_OPAQUE

#define   ALL_VISIBLE_CONTENTS            (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define   CONTENTS_TESTFOGVOLUME        0x100
#define   CONTENTS_UNUSED               0x200     
#define   CONTENTS_BLOCKLIGHT           0x400
#define   CONTENTS_TEAM1                0x800 
#define   CONTENTS_TEAM2                0x1000 
#define   CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000
#define   CONTENTS_MOVEABLE             0x4000
#define   CONTENTS_AREAPORTAL           0x8000
#define   CONTENTS_PLAYERCLIP           0x10000
#define   CONTENTS_MONSTERCLIP          0x20000
#define   CONTENTS_CURRENT_0            0x40000
#define   CONTENTS_CURRENT_90           0x80000
#define   CONTENTS_CURRENT_180          0x100000
#define   CONTENTS_CURRENT_270          0x200000
#define   CONTENTS_CURRENT_UP           0x400000
#define   CONTENTS_CURRENT_DOWN         0x800000

#define   CONTENTS_ORIGIN               0x1000000 

#define   CONTENTS_MONSTER              0x2000000 
#define   CONTENTS_DEBRIS               0x4000000
#define   CONTENTS_DETAIL               0x8000000 
#define   CONTENTS_TRANSLUCENT          0x10000000
#define   CONTENTS_LADDER               0x20000000
#define   CONTENTS_HITBOX               0x40000000

#define   SURF_LIGHT                    0x0001 
#define   SURF_SKY2D                    0x0002 
#define   SURF_SKY                      0x0004 
#define   SURF_WARP                     0x0008 
#define   SURF_TRANS                    0x0010
#define   SURF_NOPORTAL                 0x0020 
#define   SURF_TRIGGER                  0x0040 
#define   SURF_NODRAW                   0x0080 

#define   SURF_HINT                     0x0100 

#define   SURF_SKIP                     0x0200   
#define   SURF_NOLIGHT                  0x0400   
#define   SURF_BUMPLIGHT                0x0800   
#define   SURF_NOSHADOWS                0x1000   
#define   SURF_NODECALS                 0x2000   
#define   SURF_NOPAINT                  SURF_NODECALS
#define   SURF_NOCHOP                   0x4000   
#define   SURF_HITBOX                   0x8000   

#define   MASK_ALL                      (0xFFFFFFFF)
#define   MASK_SOLID                    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCSOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define   MASK_NPCFLUID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_WATER                    (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define   MASK_OPAQUE                   (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define   MASK_OPAQUE_AND_NPCS          (MASK_OPAQUE|CONTENTS_MONSTER)
#define   MASK_BLOCKLOS                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define   MASK_BLOCKLOS_AND_NPCS        (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define   MASK_VISIBLE                  (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_VISIBLE_AND_NPCS         (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define   MASK_SHOT                     (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define   MASK_SHOT_BRUSHONLY           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define   MASK_SHOT_HULL                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define   MASK_SHOT_PORTAL              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define   MASK_SOLID_BRUSHONLY          (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define   MASK_PLAYERSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define   MASK_NPCSOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC           (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define   MASK_NPCWORLDSTATIC_FLUID     (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define   MASK_SPLITAREAPORTAL          (CONTENTS_WATER|CONTENTS_SLIME)
#define   MASK_CURRENT                  (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define   MASK_DEADSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

struct colorVec
{
	unsigned r, g, b, a;
};

enum
{
	PITCH = 0,	// up / down
	YAW,		// left / right
	ROLL		// fall over
};

enum FontRenderFlag_t
{
	FONT_LEFT = 0,
	FONT_RIGHT = 1,
	FONT_CENTER = 2
};

enum ItemDefinitionIndex : short {
    weapon_none,
    weapon_deagle,
    weapon_elite,
    weapon_fiveseven,
    weapon_glock,
    weapon_ak47 = 7,
    weapon_aug,
    weapon_awp,
    weapon_famas,
    weapon_g3sg1,
    weapon_galilar = 13,
    weapon_m249,
    weapon_m4a4 = 16,
    weapon_mac10,
    weapon_p90 = 19,
    weapon_mp5 = 23,
    weapon_ump45 = 24,
    weapon_xm1014,
    weapon_bizon,
    weapon_mag7,
    weapon_negev,
    weapon_sawedoff,
    weapon_tec9,
    weapon_taser,
    weapon_hkp2000,
    weapon_mp7,
    weapon_mp9,
    weapon_nova,
    weapon_p250,
    weapon_scar20 = 38,
    weapon_sg553,
    weapon_ssg08,
    weapon_knife_gg,
    weapon_knife_ct,
    weapon_flashbang,
    weapon_hegrenade,
    weapon_smokegrenade,
    weapon_molotov,
    weapon_decoy,
    weapon_incgrenade,
    weapon_c4,
    WEAPON_HEALTHSHOT = 57,
    weapon_knife_t = 59,
    weapon_m4a1_silencer,
    weapon_usp,
    weapon_cz75 = 63,
    weapon_revolver,
    weapon_tagrenade = 68,
    WEAPON_FISTS,
    WEAPON_BREACHCHARGE,
    WEAPON_TABLET = 72,
    WEAPON_MELEE = 74,
    WEAPON_AXE,
    WEAPON_HAMMER,
    WEAPON_SPANNER = 78,
    WEAPON_KNIFE_GHOST = 80,
    WEAPON_FIREBOMB,
    WEAPON_DIVERSION,
    WEAPON_FRAG_GRENADE,
    weapon_bayonet = 500,
    weapon_flip = 505,
    weapon_gut = 506,
    weapon_karambit,
    weapon_m9bayonet,
    weapon_huntsman,
    weapon_falchion = 512,
    weapon_bowie = 514,
    weapon_butterfly,
    weapon_daggers,
    weapon_ursus = 519,
    weapon_navaja = 520,
    weapon_stiletto = 522,
    weapon_talon = 523,
    bloodhound_gloves = 5027,
    sporty_gloves = 5030,
    slick_gloves,
    leather_handwraps,
    motorcycle_gloves,
    specialist_gloves
};

enum class wepgr : int {
	pistols,
	smgs,
	rifles,
	shotguns,
	snipers,
	autosnipers,
	knives,
};

struct player_info_t
{
	__int64         unknown;            //0x0000 
	union
	{
		__int64       steamID64;          //0x0008 - SteamID64
		struct
		{
			__int32     xuid_low;
			__int32     xuid_high;
		};
	};
	char            szName[128];        //0x0010 - Player Name
	int             userId;             //0x0090 - Unique Server Identifier
	char            szSteamID[20];      //0x0094 - STEAM_X:Y:Z
	char            pad_0x00A8[0x10];   //0x00A8
	unsigned long   iSteamID;           //0x00B8 - SteamID 
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customfiles[4];
	unsigned char filesdownloaded;
};

class vector
{
public:
	float x, y, z;
	vector(void);
	vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const vector& v) const;
	bool operator!=(const vector& v) const;
	__forceinline vector&	operator+=(const vector &v);
	__forceinline vector&	operator-=(const vector &v);
	__forceinline vector&	operator*=(const vector &v);
	__forceinline vector&	operator*=(float s);
	__forceinline vector&	operator/=(const vector &v);
	__forceinline vector&	operator/=(float s);
	__forceinline vector&	operator+=(float fl);
	__forceinline vector&	operator-=(float fl);
	inline float	Length() const;
	__forceinline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (this->x*this->x + this->y*this->y + this->z*this->z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	float	NormalizeInPlace();
	vector	Normalize();
	__forceinline float	DistToSqr(const vector &vOther) const;
	__forceinline float	Dist(const vector &vOther) const;
	float	Dot(const vector& vOther) const;
	float	Dot(const float* fOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	vector& operator=(const vector &vOther);
	vector	operator-(const vector& v) const;
	vector	operator+(const vector& v) const;
	vector	operator*(const vector& v) const;
	vector	operator/(const vector& v) const;
	vector	operator*(float fl) const;
	vector	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline vector::vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline vector::vector(void) { }
//===============================================
inline void vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline vector& vector::operator=(const vector &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool vector::operator==(const vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool vector::operator!=(const vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
__forceinline void VectorCopy(const vector& src, vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
__forceinline  vector& vector::operator+=(const vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
__forceinline  vector& vector::operator-=(const vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
__forceinline  vector& vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector& vector::operator*=(const vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline vector&	vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline vector&	vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector& vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector& vector::operator/=(const vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float vector::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	__asm sqrtss xmm0, sqsr
	__asm movss root, xmm0

	return root;
}
//===============================================
inline float vector::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x * x + y * y;

	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}

	return root;
}
//===============================================
inline float vector::Length2DSqr(void) const
{
	return (x*x + y * y);
}
//===============================================
inline vector CrossProduct(const vector& a, const vector& b)
{
	return vector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}
//===============================================
float vector::DistToSqr(const vector &vOther) const
{
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}

float vector::Dist(const vector &vOther) const
{
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}

inline vector vector::Normalize()
{
	vector vector;
	float length = this->Length();

	if (length != 0) {
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
		vector.x = vector.y = 0.0f; vector.z = 1.0f;

	return vector;
}

//===============================================
inline float vector::NormalizeInPlace()
{
	vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
}
//===============================================
inline float VectorNormalize(vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
FORCEINLINE float VectorNormalize(float * v)
{
	return VectorNormalize(*(reinterpret_cast<vector *>(v)));
}
//===============================================
inline vector vector::operator+(const vector& v) const
{
	vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline vector vector::operator-(const vector& v) const
{
	vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline vector vector::operator*(float fl) const
{
	vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline vector vector::operator*(const vector& v) const
{
	vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline vector vector::operator/(float fl) const
{
	vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline vector vector::operator/(const vector& v) const
{
	vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float vector::Dot(const vector& vOther) const
{
	const vector& a = *this;

	return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
}

inline float vector::Dot(const float* fOther) const
{
	const vector& a = *this;

	return(a.x*fOther[0] + a.y*fOther[1] + a.z*fOther[2]);
}

inline float* vector::Base()
{
	return (float*)this;
}

inline float const* vector::Base() const
{
	return (float const*)this;
}

class QAngleByValue;
class QAngle
{
public:
	float x, y, z;

	QAngle(void);
	QAngle(float X, float Y, float Z);

	operator QAngleByValue &() { return *((QAngleByValue *)(this)); }
	operator const QAngleByValue &() const { return *((const QAngleByValue *)(this)); }

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	bool IsValid() const;
	void Invalidate();

	bool IsZero()
	{
		CHECK_VALID(*this);
		if (this->x == 0.f && this->y == 0.f && this->z == 0.f)
			return true;

		return false;
	}

	float operator[](int i) const;
	float& operator[](int i);

	float* Base();
	float const* Base() const;

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle& operator+=(const QAngle &v);
	QAngle& operator-=(const QAngle &v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	float   Length() const;
	float   LengthSqr() const;

	QAngle& operator=(const QAngle& src);

	QAngle  operator-(void) const;

	QAngle  operator+(const QAngle& v) const;
	QAngle  operator-(const QAngle& v) const;
	QAngle  operator*(float fl) const;
	QAngle  operator/(float fl) const;

	QAngle Clamp();
	QAngle Mod(float N);

	inline QAngle QAngle::Normalize()
	{
		QAngle vector;
		float length = this->Length();

		if (length != 0) {
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
			vector.x = vector.y = 0.0f; vector.z = 1.0f;

		return vector;
	}

	QAngle Normalized()
	{
		if (this->x != this->x)
			this->x = 0;
		if (this->y != this->y)
			this->y = 0;
		if (this->z != this->z)
			this->z = 0;

		if (this->x > 89.f)
			this->x = 89.f;
		if (this->x < -89.f)
			this->x = -89.f;

		while (this->y > 180)
			this->y -= 360;
		while (this->y <= -180)
			this->y += 360;

		if (this->y > 180.f)
			this->y = 180.f;
		if (this->y < -180.f)
			this->y = -180.f;

		this->z = 0;

		return *this;
	}

	QAngle normalize17()
	{
		if (!std::isfinite(this->x)) this->x = 0.f;
		if (!std::isfinite(this->y)) this->y = 0.f;

		this->x = std::clamp(this->x, -89.f, 89.f);
		this->y = std::clamp(std::remainderf(this->y, 360.f), -180.f, 180.f);
		this->z = 0.f;

		return *this;
	}
	QAngle clamp17()
	{
		if (!std::isfinite(this->x)) this->x = 0.f;
		if (!std::isfinite(this->y)) this->y = 0.f;

		this->x = std::clamp(this->x, -89.f, 89.f);
		this->y = std::clamp(std::remainder(this->y, 360.f), -180.f, 180.f);
		this->z = 0.f;

		return *this;
	}
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = float_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	CHECK_VALID(*this);
	return (float)sqrt(LengthSqr()); //todo replace with fastsqrt
}


inline float QAngle::LengthSqr() const
{
	CHECK_VALID(*this);
	return x * x + y * y;
}

inline QAngle QAngle::operator-(void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle QAngle::Clamp()
{
	CHECK_VALID(*this);

	if (this->x < -89.0f)
		this->x = -89.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;

	return *this;
}

inline QAngle QAngle::Mod(float N)
{
	CHECK_VALID(*this);
	this->x = fmod(x, N);
	this->y = fmod(y, N);
	this->z = fmod(z, N);

	return *this;
}

class IRecipientFilter;


class CUserCmd
{
public:
	virtual ~CUserCmd() { };
	int		command_number;
	int		tick_count;
	QAngle	viewangles;
	vector	aimdirection;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	byte    impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousedx;
	short	mousedy;
	bool	hasbeenpredicted;
	char	pad_0x4C[0x18];
};

struct VMatrix
{
	float m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};

struct matrix3x3_t
{
	float m_flMatVal[3][3];
};

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector &vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector &vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void SetOrigin(vector const & p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = VEC_T_NAN;
			}
		}
	}

	//	float *operator[](int i) { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	//	const float *operator[](int i) const { Assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float *operator[](int i) { return m_flMatVal[i]; }
	const float *operator[](int i) const { return m_flMatVal[i]; }
	float *Base() { return &m_flMatVal[0][0]; }
	const float *Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

class ALIGN16 matrix3x4a_t : public matrix3x4_t
{
public:
	/*
	matrix3x4a_t() { if (((size_t)Base()) % 16 != 0) { Error( "matrix3x4a_t missaligned" ); } }
	*/
	matrix3x4a_t& operator=(const matrix3x4_t& src) { memcpy(Base(), src.Base(), sizeof(float) * 3 * 4); return *this; };
};



struct mstudiobbox_t
{
	int		bone;
	int		group; // intersection group
	vector	bbmin; // bounding box 
	vector	bbmax;
	int		hitboxnameindex; // offset to the name of the hitbox.
	int		pad[3];
	float	radius;
	int		pad2[4];

	char* getHitboxName()
	{
		if (hitboxnameindex == 0)
			return "";

		return ((char*)this) + hitboxnameindex;
	}
};

enum ClassID_t {
    CTestTraceline = 223,
    CTEWorldDecal = 224,
    CTESpriteSpray = 221,
    CTESprite = 220,
    CTESparks = 219,
    CTESmoke = 218,
    CTEShowLine = 216,
    CTEProjectedDecal = 213,
    CFEPlayerDecal = 71,
    CTEPlayerDecal = 212,
    CTEPhysicsProp = 209,
    CTEParticleSystem = 208,
    CTEMuzzleFlash = 207,
    CTELargeFunnel = 205,
    CTEKillPlayerAttachments = 204,
    CTEImpact = 203,
    CTEGlowSprite = 202,
    CTEShatterSurface = 215,
    CTEFootprintDecal = 199,
    CTEFizz = 198,
    CTEExplosion = 196,
    CTEEnergySplash = 195,
    CTEEffectDispatch = 194,
    CTEDynamicLight = 193,
    CTEDecal = 191,
    CTEClientProjectile = 190,
    CTEBubbleTrail = 189,
    CTEBubbles = 188,
    CTEBSPDecal = 187,
    CTEBreakModel = 186,
    CTEBloodStream = 185,
    CTEBloodSprite = 184,
    CTEBeamSpline = 183,
    CTEBeamRingPoint = 182,
    CTEBeamRing = 181,
    CTEBeamPoints = 180,
    CTEBeamLaser = 179,
    CTEBeamFollow = 178,
    CTEBeamEnts = 177,
    CTEBeamEntPoint = 176,
    CTEBaseBeam = 175,
    CTEArmorRicochet = 174,
    CTEMetalSparks = 206,
    CSteamJet = 167,
    CSmokeStack = 157,
    DustTrail = 275,
    CFireTrail = 74,
    SporeTrail = 281,
    SporeExplosion = 280,
    RocketTrail = 278,
    SmokeTrail = 279,
    CPropVehicleDriveable = 144,
    ParticleSmokeGrenade = 277,
    CParticleFire = 116,
    MovieExplosion = 276,
    CTEGaussExplosion = 201,
    CEnvQuadraticBeam = 66,
    CEmbers = 55,
    CEnvWind = 70,
    CPrecipitation = 137,
    CPrecipitationBlocker = 138,
    CBaseTempEntity = 18,
    NextBotCombatCharacter = 0,
    CEconWearable = 54,
    CBaseAttributableItem = 4,
    CEconEntity = 53,
    CWeaponXM1014 = 272,
    CWeaponTaser = 267,
    CTablet = 171,
    CSnowball = 158,
    CSmokeGrenade = 155,
    CWeaponShield = 265,
    CWeaponSG552 = 263,
    CSensorGrenade = 151,
    CWeaponSawedoff = 259,
    CWeaponNOVA = 255,
    CIncendiaryGrenade = 99,
    CMolotovGrenade = 112,
    CMelee = 111,
    CWeaponM3 = 247,
    CKnifeGG = 108,
    CKnife = 107,
    CHEGrenade = 96,
    CFlashbang = 77,
    CFists = 76,
    CWeaponElite = 238,
    CDecoyGrenade = 47,
    CDEagle = 46,
    CWeaponUSP = 271,
    CWeaponM249 = 246,
    CWeaponUMP45 = 270,
    CWeaponTMP = 269,
    CWeaponTec9 = 268,
    CWeaponSSG08 = 266,
    CWeaponSG556 = 264,
    CWeaponSG550 = 262,
    CWeaponScout = 261,
    CWeaponSCAR20 = 260,
    CSCAR17 = 149,
    CWeaponP90 = 258,
    CWeaponP250 = 257,
    CWeaponP228 = 256,
    CWeaponNegev = 254,
    CWeaponMP9 = 253,
    CWeaponMP7 = 252,
    CWeaponMP5Navy = 251,
    CWeaponMag7 = 250,
    CWeaponMAC10 = 249,
    CWeaponM4A1 = 248,
    CWeaponHKP2000 = 245,
    CWeaponGlock = 244,
    CWeaponGalilAR = 243,
    CWeaponGalil = 242,
    CWeaponG3SG1 = 241,
    CWeaponFiveSeven = 240,
    CWeaponFamas = 239,
    CWeaponBizon = 234,
    CWeaponAWP = 232,
    CWeaponAug = 231,
    CAK47 = 1,
    CWeaponCSBaseGun = 236,
    CWeaponCSBase = 235,
    CC4 = 34,
    CBumpMine = 32,
    CBumpMineProjectile = 33,
    CBreachCharge = 28,
    CBreachChargeProjectile = 29,
    CWeaponBaseItem = 233,
    CBaseCSGrenade = 8,
    CSnowballProjectile = 160,
    CSnowballPile = 159,
    CSmokeGrenadeProjectile = 156,
    CSensorGrenadeProjectile = 152,
    CMolotovProjectile = 113,
    CItem_Healthshot = 104,
    CItemDogtags = 106,
    CDecoyProjectile = 48,
    CPhysPropRadarJammer = 126,
    CPhysPropWeaponUpgrade = 127,
    CPhysPropAmmoBox = 124,
    CPhysPropLootCrate = 125,
    CItemCash = 105,
    CEnvGasCanister = 63,
    CDronegun = 50,
    CParadropChopper = 115,
    CSurvivalSpawnChopper = 170,
    CBRC4Target = 27,
    CInfoMapRegion = 102,
    CFireCrackerBlast = 72,
    CInferno = 100,
    CChicken = 36,
    CDrone = 49,
    CFootstepControl = 79,
    CCSGameRulesProxy = 39,
    CWeaponCubemap = 0,
    CWeaponCycler = 237,
    CTEPlantBomb = 210,
    CTEFireBullets = 197,
    CTERadioIcon = 214,
    CPlantedC4 = 128,
    CCSTeam = 43,
    CCSPlayerResource = 41,
    CCSPlayer = 40,
    CPlayerPing = 130,
    CCSRagdoll = 42,
    CTEPlayerAnimEvent = 211,
    CHostage = 97,
    CHostageCarriableProp = 98,
    CBaseCSGrenadeProjectile = 9,
    CHandleTest = 95,
    CTeamplayRoundBasedRulesProxy = 173,
    CSpriteTrail = 165,
    CSpriteOriented = 164,
    CSprite = 163,
    CRagdollPropAttached = 147,
    CRagdollProp = 146,
    CPropCounter = 141,
    CPredictedViewModel = 139,
    CPoseController = 135,
    CGrassBurn = 94,
    CGameRulesProxy = 93,
    CInfoLadderDismount = 101,
    CFuncLadder = 85,
    CTEFoundryHelpers = 200,
    CEnvDetailController = 61,
    CDangerZone = 44,
    CDangerZoneController = 45,
    CWorldVguiText = 274,
    CWorld = 273,
    CWaterLODControl = 230,
    CWaterBullet = 229,
    CVoteController = 228,
    CVGuiScreen = 227,
    CPropJeep = 143,
    CPropVehicleChoreoGeneric = 0,
    CTriggerSoundOperator = 226,
    CBaseVPhysicsTrigger = 22,
    CTriggerPlayerMovement = 225,
    CBaseTrigger = 20,
    CTest_ProxyToggle_Networkable = 222,
    CTesla = 217,
    CBaseTeamObjectiveResource = 17,
    CTeam = 172,
    CSunlightShadowControl = 169,
    CSun = 168,
    CParticlePerformanceMonitor = 117,
    CSpotlightEnd = 162,
    CSpatialEntity = 161,
    CSlideshowDisplay = 154,
    CShadowControl = 153,
    CSceneEntity = 150,
    CRopeKeyframe = 148,
    CRagdollManager = 145,
    CPhysicsPropMultiplayer = 122,
    CPhysBoxMultiplayer = 120,
    CPropDoorRotating = 142,
    CBasePropDoor = 16,
    CDynamicProp = 52,
    CProp_Hallucination = 140,
    CPostProcessController = 136,
    CPointWorldText = 134,
    CPointCommentaryNode = 133,
    CPointCamera = 132,
    CPlayerResource = 131,
    CPlasma = 129,
    CPhysMagnet = 123,
    CPhysicsProp = 121,
    CStatueProp = 166,
    CPhysBox = 119,
    CParticleSystem = 118,
    CMovieDisplay = 114,
    CMaterialModifyControl = 110,
    CLightGlow = 109,
    CItemAssaultSuitUseable = 0,
    CItem = 0,
    CInfoOverlayAccessor = 103,
    CFuncTrackTrain = 92,
    CFuncSmokeVolume = 91,
    CFuncRotating = 90,
    CFuncReflectiveGlass = 89,
    CFuncOccluder = 88,
    CFuncMoveLinear = 87,
    CFuncMonitor = 86,
    CFunc_LOD = 81,
    CTEDust = 192,
    CFunc_Dust = 80,
    CFuncConveyor = 84,
    CFuncBrush = 83,
    CBreakableSurface = 31,
    CFuncAreaPortalWindow = 82,
    CFish = 75,
    CFireSmoke = 73,
    CEnvTonemapController = 69,
    CEnvScreenEffect = 67,
    CEnvScreenOverlay = 68,
    CEnvProjectedTexture = 65,
    CEnvParticleScript = 64,
    CFogController = 78,
    CEnvDOFController = 62,
    CCascadeLight = 35,
    CEnvAmbientLight = 60,
    CEntityParticleTrail = 59,
    CEntityFreezing = 58,
    CEntityFlame = 57,
    CEntityDissolve = 56,
    CDynamicLight = 51,
    CColorCorrectionVolume = 38,
    CColorCorrection = 37,
    CBreakableProp = 30,
    CBeamSpotlight = 25,
    CBaseButton = 5,
    CBaseToggle = 19,
    CBasePlayer = 15,
    CBaseFlex = 12,
    CBaseEntityd = 11,
    CBaseDoor = 10,
    CBaseCombatCharacter = 6,
    CBaseAnimatingOverlay = 3,
    CBoneFollower = 26,
    CBaseAnimating = 2,
    CAI_BaseNPC = 0,
    CBeam = 24,
    CBaseViewModel = 21,
    CBaseParticleEntity = 14,
    CBaseGrenade = 13,
    CBaseCombatWeapond = 7,
    CBaseWeaponWorldModel = 23,
};

class Color
{
public:
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int color32)
	{
		*((int *)this) = color32;
	}
	Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}
	Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}

	void SetAlpha(int _a = 255)
	{
		_color[3] = (unsigned char)_a;
	}

	int GetRawColor() const
	{
		return *((int*)this);
	}

	int GetD3DColor() const
	{
		return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	inline float rBase() const { return _color[0] / 255.0f; }
	inline float gBase() const { return _color[1] / 255.0f; }
	inline float bBase() const { return _color[2] / 255.0f; }
	inline float aBase() const { return _color[3] / 255.0f; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[4];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;
		clr[3] = _color[3] / 255.0f;

		return &clr[0];
	}

	static Color FromFloat(float* color)
	{
		return Color(
			(int)(color[0] * 255),
			(int)(color[1] * 255),
			(int)(color[2] * 255),
			255
		);
	}


	static Color Red() { return Color(255, 0, 0); }
	static Color Green() { return Color(0, 255, 0); }
	static Color Blue() { return Color(0, 80, 255); }
	static Color LightBlue() { return Color(100, 100, 255); }
	static Color Grey() { return Color(128, 128, 128); }
	static Color Black() { return Color(0, 0, 0); }
	static Color White() { return Color(255, 255, 255); }
	static Color Purple() { return Color(190, 0, 220); }
	static Color Orange() { return Color(255, 50, 0); }

	static Color text_clr() { return Color(200, 200, 200, 255); }
	static Color bomb_clr() { return Color(226, 33, 38, 255); }
	static Color defuser_clr() { return Color(33, 173, 255, 255); }


private:
	unsigned char _color[4];
};

class CViewSetup
{
public:
	int			x, x_old;
	int			y, y_old;
	int			width, width_old;
	int			height, height_old;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix;
	matrix3x4_t	m_matCustomViewMatrix;
	char		pad_0x68[0x48];
	float		fov;
	float		fovViewmodel;
	vector		origin;
	QAngle		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	float		m_flAspectRatio;
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	int			m_nMotionBlurMode;
	float		m_flShutterTime;
	vector		m_vShutterOpenPosition;
	QAngle		m_shutterOpenAngles;
	vector		m_vShutterClosePosition;
	QAngle		m_shutterCloseAngles;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	int			m_EdgeBlur;
};

enum FontDrawType_t
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

typedef unsigned long HFont;

struct Vector2D
{
public:
	float x, y;

	Vector2D() {}
	Vector2D(float x_, float y_) { x = x_; y = y_; }
};

struct FontVertex_t
{
	Vector2D m_Position;
	Vector2D m_TexCoord;

	FontVertex_t() {}
	FontVertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
};

typedef FontVertex_t Vertex_t;

struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float audioReflectivity;
	float audioHardnessFactor;
	float audioRoughnessFactor;
	float scrapeRoughThreshold;
	float impactHardThreshold;
	float audioHardMinVelocity;
	float highPitchOcclusion;
	float midPitchOcclusion;
	float lowPitchOcclusion;
};

struct surfacesoundnames_t
{
	short walkLeft;
	short walkRight;
	short runLeft;
	short runRight;
	short impactsoft;
	short impacthard;
	short scrapesmooth;
	short scraperough;
	short bulletimpact;
	short rolling;
	short breakSound; // named "break" in vphysics.dll but since break is also a type rename it to breakSound
	short strain;
};

struct surfacegameprops_t
{
	float flMaxSpeedFactor;
	float flJumpFactor;
	float flPenetrationModifier;
	float flDamageModifier;
	uint16_t material;
	uint8_t climbable;
};

struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
	char pad[48];
}; // size = 0x94

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

struct MaterialVideoMode_t
{
	int m_Width;
	int m_Height;
	int m_Format;
	int m_RefreshRate;
};

struct MaterialSystem_Config_t
{
	MaterialVideoMode_t m_VideoMode;
	float m_fMonitorGamma;
	float m_fGammaTVRangeMin;
	float m_fGammaTVRangeMax;
	float m_fGammaTVExponent;
	bool m_bGammaTVEnabled;
	bool m_bTripleBuffered;
	int m_nAASamples;
	int m_nForceAnisotropicLevel;
	int m_nSkipMipLevels;
	int m_nDxSupportLevel;
	int m_nFlags;
	bool m_bEditMode;
	char m_nProxiesTestMode;
	bool m_bCompressedTextures;
	bool m_bFilterLightmaps;
	bool m_bFilterTextures;
	bool m_bReverseDepth;
	bool m_bBufferPrimitives;
	bool m_bDrawFlat;
	bool m_bMeasureFillRate;
	bool m_bVisualizeFillRate;
	bool m_bNoTransparency;
	bool m_bSoftwareLighting;
	bool m_bAllowCheats;
	char m_nShowMipLevels;
	bool m_bShowLowResImage;
	bool m_bShowNormalMap;
	bool m_bMipMapTextures;
	char m_nFullbright;
	bool m_bFastNoBump;
	bool m_bSuppressRendering;
	bool m_bDrawGray;
	bool m_bShowSpecular;
	bool m_bShowDiffuse;
	int m_nWindowedSizeLimitWidth;
	int m_nWindowedSizeLimitHeight;
	int m_nAAQuality;
	bool m_bShadowDepthTexture;
	bool m_bMotionBlur;
	bool m_bSupportFlashlight;
	bool m_bPaintEnabled;
	char pad[0xC];
};

#define MAX_SPLITSCREEN_CLIENT_BITS 2
// this should == MAX_JOYSTICKS in InputEnums.h
#define MAX_SPLITSCREEN_CLIENTS	( 1 << MAX_SPLITSCREEN_CLIENT_BITS ) // 4

enum
{
	MAX_JOYSTICKS = MAX_SPLITSCREEN_CLIENTS,
	MOUSE_BUTTON_COUNT = 5,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

	// Joystick
	JOYSTICK_FIRST = MOUSE_LAST + 1,

	JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
	JOYSTICK_LAST_BUTTON = JOYSTICK_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_MAX_BUTTON_COUNT - 1),
	JOYSTICK_FIRST_POV_BUTTON,
	JOYSTICK_LAST_POV_BUTTON = JOYSTICK_POV_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_POV_BUTTON_COUNT - 1),
	JOYSTICK_FIRST_AXIS_BUTTON,
	JOYSTICK_LAST_AXIS_BUTTON = JOYSTICK_AXIS_BUTTON_INTERNAL(MAX_JOYSTICKS - 1, JOYSTICK_AXIS_BUTTON_COUNT - 1),

	JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

	BUTTON_CODE_LAST,
	BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

	// Helpers for XBox 360
	KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON,	// POV buttons
	KEY_XBUTTON_RIGHT,
	KEY_XBUTTON_DOWN,
	KEY_XBUTTON_LEFT,

	KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON,		// Buttons
	KEY_XBUTTON_B,
	KEY_XBUTTON_X,
	KEY_XBUTTON_Y,
	KEY_XBUTTON_LEFT_SHOULDER,
	KEY_XBUTTON_RIGHT_SHOULDER,
	KEY_XBUTTON_BACK,
	KEY_XBUTTON_START,
	KEY_XBUTTON_STICK1,
	KEY_XBUTTON_STICK2,
	KEY_XBUTTON_INACTIVE_START,

	KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON,	// XAXIS POSITIVE
	KEY_XSTICK1_LEFT,							// XAXIS NEGATIVE
	KEY_XSTICK1_DOWN,							// YAXIS POSITIVE
	KEY_XSTICK1_UP,								// YAXIS NEGATIVE
	KEY_XBUTTON_LTRIGGER,						// ZAXIS POSITIVE
	KEY_XBUTTON_RTRIGGER,						// ZAXIS NEGATIVE
	KEY_XSTICK2_RIGHT,							// UAXIS POSITIVE
	KEY_XSTICK2_LEFT,							// UAXIS NEGATIVE
	KEY_XSTICK2_DOWN,							// VAXIS POSITIVE
	KEY_XSTICK2_UP,								// VAXIS NEGATIVE
};

#define MAXSTUDIOSKINS		32		// total textures
#define MAXSTUDIOBONES		128		// total bones actually used
#define MAXSTUDIOFLEXDESC	1024	// maximum number of low level flexes (actual morph targets)
#define MAXSTUDIOFLEXCTRL	96		// maximum number of flexcontrollers (input sliders)
#define MAXSTUDIOPOSEPARAM	24
#define MAXSTUDIOBONECTRLS	4
#define MAXSTUDIOANIMBLOCKS 256

#define BONE_CALCULATE_MASK			0x1F
#define BONE_PHYSICALLY_SIMULATED	0x01	// bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL		0x02	// procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL		0x04	// bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE	0x08	// bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER	0x10	// bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800	
#define BONE_USED_BY_VERTEX_LOD2	0x00001000  
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

#define BONE_USED_BY_VERTEX_AT_LOD(lod) ( BONE_USED_BY_VERTEX_LOD0 << (lod) )
#define BONE_USED_BY_ANYTHING_AT_LOD(lod) ( ( BONE_USED_BY_ANYTHING & ~BONE_USED_BY_VERTEX_MASK ) | BONE_USED_BY_VERTEX_AT_LOD(lod) )

#define MAX_NUM_LODS 8

#define BONE_TYPE_MASK				0x00F00000
#define BONE_FIXED_ALIGNMENT		0x00100000	// bone can't spin 360 degrees, all interpolation is normalized around a fixed orientation

#define BONE_HAS_SAVEFRAME_POS		0x00200000	// Vector48
#define BONE_HAS_SAVEFRAME_ROT64	0x00400000	// Quaternion64
#define BONE_HAS_SAVEFRAME_ROT32	0x00800000	// Quaternion32

#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4	
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10			// alerts NPC, but doesn't do damage or bleed (1/100th damage)

struct model_t
{
	char        name[255];
};
typedef unsigned short ModelInstanceHandle_t;

struct ModelRenderInfo_t
{
	vector origin;
	QAngle angles;
	void *huj;
	void *pRenderable;
	const model_t *pModel;
	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};




enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};

enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,	// NOTE: D3D9 does not have this format
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,

	IMAGE_FORMAT_NULL,			// Dummy format which takes no video memory

								// Compressed normal map formats
								IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
								IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

								IMAGE_FORMAT_RGBA1010102,	// 10 bit-per component render targets
								IMAGE_FORMAT_BGRA1010102,
								IMAGE_FORMAT_R16F,			// 16 bit FP format

															// Depth-stencil texture formats
															IMAGE_FORMAT_D16,
															IMAGE_FORMAT_D15S1,
															IMAGE_FORMAT_D32,
															IMAGE_FORMAT_D24S8,
															IMAGE_FORMAT_LINEAR_D24S8,
															IMAGE_FORMAT_D24X8,
															IMAGE_FORMAT_D24X4S4,
															IMAGE_FORMAT_D24FS8,
															IMAGE_FORMAT_D16_SHADOW,	// Specific formats for shadow mapping
															IMAGE_FORMAT_D24X8_SHADOW,	// Specific formats for shadow mapping

																						// supporting these specific formats as non-tiled for procedural cpu access (360-specific)
																						IMAGE_FORMAT_LINEAR_BGRX8888,
																						IMAGE_FORMAT_LINEAR_RGBA8888,
																						IMAGE_FORMAT_LINEAR_ABGR8888,
																						IMAGE_FORMAT_LINEAR_ARGB8888,
																						IMAGE_FORMAT_LINEAR_BGRA8888,
																						IMAGE_FORMAT_LINEAR_RGB888,
																						IMAGE_FORMAT_LINEAR_BGR888,
																						IMAGE_FORMAT_LINEAR_BGRX5551,
																						IMAGE_FORMAT_LINEAR_I8,
																						IMAGE_FORMAT_LINEAR_RGBA16161616,

																						IMAGE_FORMAT_LE_BGRX8888,
																						IMAGE_FORMAT_LE_BGRA8888,

																						NUM_IMAGE_FORMATS
};

template <class T, class I = int> class CUtlMemory
{
public:
	T & operator[](I i)
	{
		return m_pMemory[i];
	}
	T *Base()
	{
		return m_pMemory;
	}
protected:
	T * m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <class T>
inline void Destruct(T *pMemory)
{
	pMemory->~T();
}

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;

	typedef T *iterator;
	typedef const T *const_iterator;
public:
	T & operator[](int i)
	{
		return m_Memory[i];
	}

	T& Element(int i)
	{
		return m_Memory[i];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int Count() const
	{
		return m_Size;
	}

	void RemoveAll()
	{
		for (int i = m_Size; --i >= 0; )
			Destruct(&Element(i));

		m_Size = 0;
	}

	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + Count(); }
	const_iterator end() const { return Base() + Count(); }

protected:
	CAllocator m_Memory;
	int m_Size;
	T *m_pElements;
};

enum Collision_Group_t
{
	COLLISION_GROUP_NONE = 0,
	COLLISION_GROUP_DEBRIS,			// Collides with nothing but world and static stuff
	COLLISION_GROUP_DEBRIS_TRIGGER, // Same as debris, but hits triggers
	COLLISION_GROUP_INTERACTIVE_DEBRIS,	// Collides with everything except other interactive debris or debris
	COLLISION_GROUP_INTERACTIVE,	// Collides with everything except interactive debris or debris
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,  // For HL2, same as Collision_Group_Player, for
									  // TF2, this filters out other players and CBaseObjects
									  COLLISION_GROUP_NPC,			// Generic NPC group
									  COLLISION_GROUP_IN_VEHICLE,		// for any entity inside a vehicle
									  COLLISION_GROUP_WEAPON,			// for any weapons that need collision detection
									  COLLISION_GROUP_VEHICLE_CLIP,	// vehicle clip brush to restrict vehicle movement
									  COLLISION_GROUP_PROJECTILE,		// Projectiles!
									  COLLISION_GROUP_DOOR_BLOCKER,	// Blocks entities not permitted to get near moving doors
									  COLLISION_GROUP_PASSABLE_DOOR,	// Doors that the player shouldn't collide with
									  COLLISION_GROUP_DISSOLVING,		// Things that are dissolving are in this group
									  COLLISION_GROUP_PUSHAWAY,		// Nonsolid on client and server, pushaway in player code

									  COLLISION_GROUP_NPC_ACTOR,		// Used so NPCs in scripts ignore the player.
									  COLLISION_GROUP_NPC_SCRIPTED,	// USed for NPCs in scripts that should not collide with each other
									  COLLISION_GROUP_PZ_CLIP,



									  COLLISION_GROUP_DEBRIS_BLOCK_PROJECTILE, // Only collides with bullets

									  LAST_SHARED_COLLISION_GROUP
};

struct string_t
{
public:
	bool operator!() const { return (pszValue == NULL); }
	bool operator==(const string_t &rhs) const { return (pszValue == rhs.pszValue); }
	bool operator!=(const string_t &rhs) const { return (pszValue != rhs.pszValue); }
	bool operator<(const string_t &rhs) const { return ((void *)pszValue < (void *)rhs.pszValue); }

	const char *ToCStr() const { return (pszValue) ? pszValue : ""; }

protected:
	const char *pszValue;
};

#define PHYSICS_MULTIPLAYER_AUTODETECT	0	// use multiplayer physics mode as defined in model prop data
#define PHYSICS_MULTIPLAYER_SOLID		1	// soild, pushes player away 
#define PHYSICS_MULTIPLAYER_NON_SOLID	2	// nonsolid, but pushed by player
#define PHYSICS_MULTIPLAYER_CLIENTSIDE	3	// Clientside only, nonsolid 	

class IMultiplayerPhysics
{
public:
	virtual int		GetMultiplayerPhysicsMode() = 0;
	virtual float	GetMass() = 0;
	virtual bool	IsAsleep() = 0;
};

enum propdata_interactions_t
{
	PROPINTER_PHYSGUN_WORLD_STICK,		// "onworldimpact"	"stick"
	PROPINTER_PHYSGUN_FIRST_BREAK,		// "onfirstimpact"	"break"
	PROPINTER_PHYSGUN_FIRST_PAINT,		// "onfirstimpact"	"paintsplat"
	PROPINTER_PHYSGUN_FIRST_IMPALE,		// "onfirstimpact"	"impale"
	PROPINTER_PHYSGUN_LAUNCH_SPIN_NONE,	// "onlaunch"		"spin_none"
	PROPINTER_PHYSGUN_LAUNCH_SPIN_Z,	// "onlaunch"		"spin_zaxis"
	PROPINTER_PHYSGUN_BREAK_EXPLODE,	// "onbreak"		"explode_fire"
	PROPINTER_PHYSGUN_BREAK_EXPLODE_ICE,	// "onbreak"	"explode_ice"
	PROPINTER_PHYSGUN_DAMAGE_NONE,		// "damage"			"none"

	PROPINTER_FIRE_FLAMMABLE,			// "flammable"			"yes"
	PROPINTER_FIRE_EXPLOSIVE_RESIST,	// "explosive_resist"	"yes"
	PROPINTER_FIRE_IGNITE_HALFHEALTH,	// "ignite"				"halfhealth"

	PROPINTER_PHYSGUN_CREATE_FLARE,		// "onpickup"		"create_flare"

	PROPINTER_PHYSGUN_ALLOW_OVERHEAD,	// "allow_overhead"	"yes"

	PROPINTER_WORLD_BLOODSPLAT,			// "onworldimpact", "bloodsplat"

	PROPINTER_PHYSGUN_NOTIFY_CHILDREN,	// "onfirstimpact" cause attached flechettes to explode
	PROPINTER_MELEE_IMMUNE,				// "melee_immune"	"yes"

										// If we get more than 32 of these, we'll need a different system

										PROPINTER_NUM_INTERACTIONS,
};

enum mp_break_t
{
	MULTIPLAYER_BREAK_DEFAULT,
	MULTIPLAYER_BREAK_SERVERSIDE,
	MULTIPLAYER_BREAK_CLIENTSIDE,
	MULTIPLAYER_BREAK_BOTH
};

class IBreakableWithPropData
{
public:
	// Damage modifiers
	virtual void		SetDmgModBullet(float flDmgMod) = 0;
	virtual void		SetDmgModClub(float flDmgMod) = 0;
	virtual void		SetDmgModExplosive(float flDmgMod) = 0;
	virtual float		GetDmgModBullet(void) = 0;
	virtual float		GetDmgModClub(void) = 0;
	virtual float		GetDmgModExplosive(void) = 0;
	virtual float		GetDmgModFire(void) = 0;

	// Explosive
	virtual void		SetExplosiveRadius(float flRadius) = 0;
	virtual void		SetExplosiveDamage(float flDamage) = 0;
	virtual float		GetExplosiveRadius(void) = 0;
	virtual float		GetExplosiveDamage(void) = 0;

	// Physics damage tables
	virtual void		SetPhysicsDamageTable(string_t iszTableName) = 0;
	virtual string_t	GetPhysicsDamageTable(void) = 0;

	// Breakable chunks
	virtual void		SetBreakableModel(string_t iszModel) = 0;
	virtual string_t 	GetBreakableModel(void) = 0;
	virtual void		SetBreakableSkin(int iSkin) = 0;
	virtual int			GetBreakableSkin(void) = 0;
	virtual void		SetBreakableCount(int iCount) = 0;
	virtual int			GetBreakableCount(void) = 0;
	virtual void		SetMaxBreakableSize(int iSize) = 0;
	virtual int			GetMaxBreakableSize(void) = 0;

	// LOS blocking
	virtual void		SetPropDataBlocksLOS(bool bBlocksLOS) = 0;
	virtual void		SetPropDataIsAIWalkable(bool bBlocksLOS) = 0;

	// Interactions
	virtual void		SetInteraction(propdata_interactions_t Interaction) = 0;
	virtual bool		HasInteraction(propdata_interactions_t Interaction) = 0;

	// Multiplayer physics mode
	virtual void		SetPhysicsMode(int iMode) = 0;
	virtual int			GetPhysicsMode() = 0;

	// Multiplayer breakable spawn behavior
	virtual void		SetMultiplayerBreakMode(mp_break_t mode) = 0;
	virtual mp_break_t	GetMultiplayerBreakMode(void) const = 0;

	// Used for debugging
	virtual void		SetBasePropData(string_t iszBase) = 0;
	virtual string_t	GetBasePropData(void) = 0;
};

#define FCVAR_NONE				0 

// Command to ConVars and ConCommands
// ConVar Systems
#define FCVAR_UNREGISTERED		(1<<0)	// If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY	(1<<1)	// Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined.
#define FCVAR_GAMEDLL			(1<<2)	// defined by the game DLL
#define FCVAR_CLIENTDLL			(1<<3)  // defined by the client DLL
#define FCVAR_HIDDEN			(1<<4)	// Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.

// ConVar only
#define FCVAR_PROTECTED			(1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY			(1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define	FCVAR_ARCHIVE			(1<<7)	// set to cause it to be saved to vars.rc
#define	FCVAR_NOTIFY			(1<<8)	// notifies players when changed
#define	FCVAR_USERINFO			(1<<9)	// changes the client's info string
#define FCVAR_CHEAT				(1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats

#define FCVAR_PRINTABLEONLY		(1<<10)  // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED			(1<<11)  // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING	(1<<12)  // never try to print that cvar

// It's a ConVar that's shared between the client and the server.
// At signon, the values of all such ConVars are sent from the server to the client (skipped for local
//  client, of course )
// If a change is requested it must come from the console (i.e., no remote client changes)
// If a value is changed while a server is active, it's replicated to all connected clients
#define FCVAR_REPLICATED		(1<<13)	// server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_DEMO				(1<<16)  // record this cvar when starting a demo file
#define FCVAR_DONTRECORD		(1<<17)  // don't record these command in demofiles
#define FCVAR_RELOAD_MATERIALS	(1<<20)	// If this cvar changes, it forces a material reload
#define FCVAR_RELOAD_TEXTURES	(1<<21)	// If this cvar changes, if forces a texture reload

#define FCVAR_NOT_CONNECTED		(1<<22)	// cvar cannot be changed by a client that is connected to a server
#define FCVAR_MATERIAL_SYSTEM_THREAD (1<<23)	// Indicates this cvar is read from the material system thread
#define FCVAR_ARCHIVE_XBOX		(1<<24) // cvar written to config.cfg on the Xbox

#define FCVAR_ACCESSIBLE_FROM_THREADS	(1<<25)	// used as a debugging tool necessary to check material system thread convars

#define FCVAR_SERVER_CAN_EXECUTE	(1<<28)// the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY	(1<<29)// If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE	(1<<30)	// IVEngineClient::ClientCmd is allowed to execute this command. 
// Note: IVEngineClient::ClientCmd_Unrestricted can run any client command.

// #define FCVAR_AVAILABLE			(1<<15)
// #define FCVAR_AVAILABLE			(1<<18)
// #define FCVAR_AVAILABLE			(1<<19)
// #define FCVAR_AVAILABLE			(1<<20)
// #define FCVAR_AVAILABLE			(1<<21)
// #define FCVAR_AVAILABLE			(1<<23)
// #define FCVAR_AVAILABLE			(1<<26)
// #define FCVAR_AVAILABLE			(1<<27)
// #define FCVAR_AVAILABLE			(1<<31)

#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )	

struct FileHandle_t;

class KeyValues
{
public:
	//	By default, the KeyValues class uses a string table for the key names that is
	//	limited to 4MB. The game will exit in error if this space is exhausted. In
	//	general this is preferable for game code for performance and memory fragmentation
	//	reasons.
	//
	//	If this is not acceptable, you can use this call to switch to a table that can grow
	//	arbitrarily. This call must be made before any KeyValues objects are allocated or it
	//	will result in undefined behavior. If you use the growable string table, you cannot
	//	share KeyValues pointers directly with any other module. You can serialize them across
	//	module boundaries. These limitations are acceptable in the Steam backend code 
	//	this option was written for, but may not be in other situations. Make sure to
	//	understand the implications before using this.
	static void SetUseGrowableStringTable(bool bUseGrowableTable);

	KeyValues(const char *setName) {}

	//
	// AutoDelete class to automatically free the keyvalues.
	// Simply construct it with the keyvalues you allocated and it will free them when falls out of scope.
	// When you decide that keyvalues shouldn't be deleted call Assign(NULL) on it.
	// If you constructed AutoDelete(NULL) you can later assign the keyvalues to be deleted with Assign(pKeyValues).
	// You can also pass temporary KeyValues object as an argument to a function by wrapping it into KeyValues::AutoDelete
	// instance:   call_my_function( KeyValues::AutoDelete( new KeyValues( "test" ) ) )
	//
	class AutoDelete
	{
	public:
		explicit inline AutoDelete(KeyValues *pKeyValues) : m_pKeyValues(pKeyValues) {}
		explicit inline AutoDelete(const char *pchKVName) : m_pKeyValues(new KeyValues(pchKVName)) {}
		inline ~AutoDelete(void) { if (m_pKeyValues) m_pKeyValues->deleteThis(); }
		inline void Assign(KeyValues *pKeyValues) { m_pKeyValues = pKeyValues; }
		KeyValues *operator->() { return m_pKeyValues; }
		operator KeyValues *() { return m_pKeyValues; }
	private:
		AutoDelete(AutoDelete const &x); // forbid
		AutoDelete & operator= (AutoDelete const &x); // forbid
		KeyValues *m_pKeyValues;
	};

	// Quick setup constructors
	KeyValues(const char *setName, const char *firstKey, const char *firstValue);
	KeyValues(const char *setName, const char *firstKey, const wchar_t *firstValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue);
	KeyValues(const char *setName, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue, const char *secondKey, int secondValue);

	// Section name
	const char *GetName() const;
	void SetName(const char *setName);

	// gets the name as a unique int
	int GetNameSymbol() const { return m_iKeyName; }

	// File access. Set UsesEscapeSequences true, if resource file/buffer uses Escape Sequences (eg \n, \t)
	void UsesEscapeSequences(bool state); // default false
	void UsesConditionals(bool state); // default true
	bool LoadFromFile(void *filesystem, const char *resourceName, const char *pathID = NULL);
	bool SaveToFile(void *filesystem, const char *resourceName, const char *pathID = NULL, bool sortKeys = false, bool bAllowEmptyString = false);

	// Read from a buffer...  Note that the buffer must be null terminated
	bool LoadFromBuffer(char const *resourceName, const char *pBuffer, void* pFileSystem = NULL, const char *pPathID = NULL);

	// Read from a utlbuffer...
	bool LoadFromBuffer(char const *resourceName, void*buf, void* pFileSystem = NULL, const char *pPathID = NULL);

	// Find a keyValue, create it if it is not found.
	// Set bCreate to true to create the key if it doesn't already exist (which ensures a valid pointer will be returned)
	KeyValues *FindKey(const char *keyName, bool bCreate = false);
	KeyValues *FindKey(int keySymbol) const;
	KeyValues *CreateNewKey();		// creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
	void AddSubKey(KeyValues *pSubkey);	// Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
	void RemoveSubKey(KeyValues *subKey);	// removes a subkey from the list, DOES NOT DELETE IT

											// Key iteration.
											//
											// NOTE: GetFirstSubKey/GetNextKey will iterate keys AND values. Use the functions 
											// below if you want to iterate over just the keys or just the values.
											//
	KeyValues *GetFirstSubKey() { return m_pSub; }	// returns the first subkey in the list
	KeyValues *GetNextKey() { return m_pPeer; }		// returns the next subkey
	void SetNextKey(KeyValues * pDat);
	KeyValues *FindLastSubKey();	// returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

									//
									// These functions can be used to treat it like a true key/values tree instead of 
									// confusing values with keys.
									//
									// So if you wanted to iterate all subkeys, then all values, it would look like this:
									//     for ( KeyValues *pKey = pRoot->GetFirstTrueSubKey(); pKey; pKey = pKey->GetNextTrueSubKey() )
									//     {
									//		   Msg( "Key name: %s\n", pKey->GetName() );
									//     }
									//     for ( KeyValues *pValue = pRoot->GetFirstValue(); pKey; pKey = pKey->GetNextValue() )
									//     {
									//         Msg( "Int value: %d\n", pValue->GetInt() );  // Assuming pValue->GetDataType() == TYPE_INT...
									//     }
	KeyValues* GetFirstTrueSubKey();
	KeyValues* GetNextTrueSubKey();

	KeyValues* GetFirstValue();	// When you get a value back, you can use GetX and pass in NULL to get the value.
	KeyValues* GetNextValue();


	// Data access
	int   GetInt(const char *keyName = NULL, int defaultValue = 0);
	uint64 GetUint64(const char *keyName = NULL, uint64 defaultValue = 0);
	float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f);
	const char *GetString(const char *keyName = NULL, const char *defaultValue = "");
	const wchar_t *GetWString(const char *keyName = NULL, const wchar_t *defaultValue = L"");
	void *GetPtr(const char *keyName = NULL, void *defaultValue = (void*)0);
	bool GetBool(const char *keyName = NULL, bool defaultValue = false);
	Color GetColor(const char *keyName = NULL /* default value is all black */);
	bool  IsEmpty(const char *keyName = NULL);

	// Data access
	int   GetInt(int keySymbol, int defaultValue = 0);
	float GetFloat(int keySymbol, float defaultValue = 0.0f);
	const char *GetString(int keySymbol, const char *defaultValue = "");
	const wchar_t *GetWString(int keySymbol, const wchar_t *defaultValue = L"");
	void *GetPtr(int keySymbol, void *defaultValue = (void*)0);
	Color GetColor(int keySymbol /* default value is all black */);
	bool  IsEmpty(int keySymbol);

	// Key writing
	void SetWString(const char *keyName, const wchar_t *value);
	void SetString(const char *keyName, const char *value);
	void SetInt(const char *keyName, int value);
	void SetUint64(const char *keyName, uint64 value);
	void SetFloat(const char *keyName, float value);
	void SetPtr(const char *keyName, void *value);
	void SetColor(const char *keyName, Color value);
	void SetBool(const char *keyName, bool value) { SetInt(keyName, value ? 1 : 0); }

	void *operator new(size_t iAllocSize);
	void operator delete(void *pMem);

	// Adds a chain... if we don't find stuff in this keyvalue, we'll look
	// in the one we're chained to.
	void ChainKeyValue(KeyValues* pChain);

	void RecursiveSaveToFile(void* buf, int indentLevel, bool sortKeys = false, bool bAllowEmptyString = false);

	bool WriteAsBinary(void*buffer);
	bool ReadAsBinary(void*buffer, int nStackDepth = 0);

	// Allocate & create a new copy of the keys
	KeyValues *MakeCopy(void) const;

	// Make a new copy of all subkeys, add them all to the passed-in keyvalues
	void CopySubkeys(KeyValues *pParent) const;

	// Clear out all subkeys, and the current value
	void Clear(void);

	// Data type
	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};
	types_t GetDataType(const char *keyName = NULL);

	// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
	void deleteThis();

	void SetStringValue(char const *strValue);

	// unpack a key values list into a structure
	void UnpackIntoStructure(struct KeyValuesUnpackStructure const *pUnpackTable, void *pDest, size_t DestSizeInBytes);

	// Process conditional keys for widescreen support.
	bool ProcessResolutionKeys(const char *pResString);

	// Dump keyvalues recursively into a dump context
	bool Dump(class IKeyValuesDumpContext *pDump, int nIndentLevel = 0);

	// Merge in another KeyValues, keeping "our" settings
	void RecursiveMergeKeyValues(KeyValues *baseKV);

private:
	KeyValues(KeyValues&);	// prevent copy constructor being used

							// prevent delete being called except through deleteThis()
	~KeyValues();

	KeyValues* CreateKey(const char *keyName);

	/// Create a child key, given that we know which child is currently the last child.
	/// This avoids the O(N^2) behaviour when adding children in sequence to KV,
	/// when CreateKey() wil have to re-locate the end of the list each time.  This happens,
	/// for example, every time we load any KV file whatsoever.
	KeyValues* CreateKeyUsingKnownLastChild(const char *keyName, KeyValues *pLastChild);
	void AddSubkeyUsingKnownLastChild(KeyValues *pSubKey, KeyValues *pLastChild);

	void RecursiveCopyKeyValues(KeyValues& src);
	void RemoveEverything();
	//	void RecursiveSaveToFile( IBaseFileSystem *filesystem, void*buffer, int indentLevel );
	//	void WriteConvertedString( void*buffer, const char *pszString );

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void RecursiveSaveToFile(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void SaveKeyToFile(KeyValues *dat, void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void WriteConvertedString(void *filesystem, FileHandle_t f, void *pBuf, const char *pszString);

	void RecursiveLoadFromBuffer(char const *resourceName, void*buf);

	// For handling #include "filename"
	void AppendIncludedKeys(void* includedKeys);
	void ParseIncludedKeys(char const *resourceName, const char *filetoinclude,
		void* pFileSystem, const char *pPathID, void* includedKeys);

	// For handling #base "filename"
	void MergeBaseKeys(void* baseKeys);

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void InternalWrite(void *filesystem, FileHandle_t f, void *pBuf, const void *pData, int len);

	void Init();
	const char * ReadToken(void*buf, bool &wasQuoted, bool &wasConditional);
	void WriteIndents(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel);

	void FreeAllocatedValue();
	void AllocateValueBlock(int size);

	int m_iKeyName;	// keyname is a symbol defined in KeyValuesSystem

					// These are needed out of the union because the API returns string pointers
	char *m_sValue;
	wchar_t *m_wsValue;

	// we don't delete these
	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char	   m_iDataType;
	char	   m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
	char	   m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
	char	   unused[1];

	KeyValues *m_pPeer;	// pointer to next key in list
	KeyValues *m_pSub;	// pointer to Start of a new sub key list
	KeyValues *m_pChain;// Search here if it's not in our list

private:
	// Statics to implement the optional growable string table
	// Function pointers that will determine which mode we are in
	static int(*s_pfGetSymbolForString)(const char *name, bool bCreate);
	static const char *(*s_pfGetStringForSymbol)(int symbol);
	static void *s_pGrowableStringTable;

public:
	// Functions that invoke the default behavior
	static int GetSymbolForStringClassic(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolClassic(int symbol);

	// Functions that use the growable string table
	static int GetSymbolForStringGrowable(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolGrowable(int symbol);

	// Functions to get external access to whichever of the above functions we're going to call.
	static int CallGetSymbolForString(const char *name, bool bCreate = true) { return s_pfGetSymbolForString(name, bCreate); }
	static const char *CallGetStringForSymbol(int symbol) { return s_pfGetStringForSymbol(symbol); }
};


#pragma once
#include <stdint.h>
class CCSGOPlayerAnimState
{
public:
	char	__pad[0xEC];
	float	m_flSpeed;
};

class CFlashLightEffect
{
public:
	bool m_bIsOn; //0x0000 
	char pad_0x0001[0x3]; //0x0001
	int m_nEntIndex; //0x0004 
	WORD m_FlashLightHandle; //0x0008 
	char pad_0x000A[0x2]; //0x000A
	float m_flMuzzleFlashBrightness; //0x000C 
	float m_flFov; //0x0010 
	float m_flFarZ; //0x0014 
	float m_flLinearAtten; //0x0018 
	bool m_bCastsShadows; //0x001C 
	char pad_0x001D[0x3]; //0x001D
	float m_flCurrentPullBackDist; //0x0020 
	DWORD m_MuzzleFlashTexture; //0x0024 
	DWORD m_FlashLightTexture; //0x0028 
	char m_szTextureName[64]; //0x1559888 
}; //Size=0x006C

struct _CrtMemState;

#define MEMALLOC_VERSION 1

typedef size_t(*MemAllocFailHandler_t)(size_t);

//-----------------------------------------------------------------------------
// NOTE! This should never be called directly from leaf code
// Just use new,delete,malloc,free etc. They will call into this eventually
//-----------------------------------------------------------------------------
class IMemAlloc
{
public:
	virtual ~IMemAlloc();

	// Release versions
	virtual void *Alloc(size_t nSize) = 0;
	virtual void *Realloc(void *pMem, size_t nSize) = 0;
	virtual void Free(void *pMem) = 0;
	virtual void *Expand_NoLongerSupported(void *pMem, size_t nSize) = 0;

	// Debug versions
	//virtual void *Alloc(size_t nSize, const char *pFileName, int nLine) = 0;
	//virtual void *Realloc(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
	//virtual void  Free(void *pMem, const char *pFileName, int nLine) = 0;
	//virtual void *Expand_NoLongerSupported(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;

	// Returns size of a particular allocation
	virtual size_t GetSize(void *pMem) = 0;

	// Force file + line information for an allocation
	virtual void PushAllocDbgInfo(const char *pFileName, int nLine) = 0;
	virtual void PopAllocDbgInfo() = 0;

	// FIXME: Remove when we have our own allocator
	// these methods of the Crt debug code is used in our codebase currently
	virtual long CrtSetBreakAlloc(long lNewBreakAlloc) = 0;
	virtual	int CrtSetReportMode(int nReportType, int nReportMode) = 0;
	virtual int CrtIsValidHeapPointer(const void *pMem) = 0;
	virtual int CrtIsValidPointer(const void *pMem, unsigned int size, int access) = 0;
	virtual int CrtCheckMemory(void) = 0;
	virtual int CrtSetDbgFlag(int nNewFlag) = 0;
	virtual void CrtMemCheckpoint(_CrtMemState *pState) = 0;

	// FIXME: Make a better stats interface
	virtual void DumpStats() = 0;
	virtual void DumpStatsFileBase(char const *pchFileBase) = 0;

	// FIXME: Remove when we have our own allocator
	virtual void* CrtSetReportFile(int nRptType, void* hFile) = 0;
	virtual void* CrtSetReportHook(void* pfnNewHook) = 0;
	virtual int CrtDbgReport(int nRptType, const char * szFile,
		int nLine, const char * szModule, const char * pMsg) = 0;

	virtual int heapchk() = 0;

	virtual bool IsDebugHeap() = 0;

	virtual void GetActualDbgInfo(const char *&pFileName, int &nLine) = 0;
	virtual void RegisterAllocation(const char *pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime) = 0;
	virtual void RegisterDeallocation(const char *pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime) = 0;

	virtual int GetVersion() = 0;

	virtual void CompactHeap() = 0;

	// Function called when malloc fails or memory limits hit to attempt to free up memory (can come in any thread)
	virtual MemAllocFailHandler_t SetAllocFailHandler(MemAllocFailHandler_t pfnMemAllocFailHandler) = 0;

	virtual void DumpBlockStats(void *) = 0;

#if defined( _MEMTEST )	
	virtual void SetStatsExtraInfo(const char *pMapName, const char *pComment) = 0;
#endif

	// Returns 0 if no failure, otherwise the size_t of the last requested chunk
	//  "I'm sure this is completely thread safe!" Brian Deen 7/19/2012.
	virtual size_t MemoryAllocFailed() = 0;

	// handles storing allocation info for coroutines
	virtual int  GetDebugInfoSize() = 0;
	virtual void SaveDebugInfo(void *pvDebugInfo) = 0;
	virtual void RestoreDebugInfo(const void *pvDebugInfo) = 0;
	virtual void InitDebugInfo(void *pvDebugInfo, const char *pchRootFileName, int nLine) = 0;

	// Replacement for ::GlobalMemoryStatus which accounts for unused memory in our system
	virtual void GlobalMemoryStatus(size_t *pUsedMemory, size_t *pFreeMemory) = 0;
};

/*class CAnimations
{
public:
void UpdateServerAnimations(CUserCmd * cmd, bool * bsendpacket);
float m_flFirstBodyUpdate;
CCSGOPlayerAnimState*	m_serverAnimState;
private:
void CreateAnimationState(CCSGOPlayerAnimState* state, C_BasePlayer* player);
void UpdateAnimationState(CCSGOPlayerAnimState* state, QAngle ang);
void ResetAnimationState(CCSGOPlayerAnimState* state);


CBaseHandle				m_ulEntHandle;
float					m_flSpawnTime;
QAngle					m_angRealAngle = QAngle(0, 0, 0);
C_BasePlayer*			m_pLocalPlayer;
float					m_flNextBodyUpdate;
};*/

class C_AnimationLayer
{
public:
	char  pad_0000[20];
	uint32_t m_nOrder; //0x0014
	uint32_t m_nSequence; //0x0018
	float m_flPrevCycle; //0x001C
	float m_flWeight; //0x0020
	float m_flWeightDeltaRate; //0x0024
	float m_flPlaybackRate; //0x0028
	float m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
};

enum PlayerAnimEvent_t
{
	PLAYERANIMEVENT_ATTACK_PRIMARY,
	PLAYERANIMEVENT_ATTACK_SECONDARY,
	PLAYERANIMEVENT_ATTACK_GRENADE,
	PLAYERANIMEVENT_RELOAD,
	PLAYERANIMEVENT_RELOAD_LOOP,
	PLAYERANIMEVENT_RELOAD_END,
	PLAYERANIMEVENT_JUMP,
	PLAYERANIMEVENT_SWIM,
	PLAYERANIMEVENT_DIE,
	PLAYERANIMEVENT_FLINCH_CHEST,
	PLAYERANIMEVENT_FLINCH_HEAD,
	PLAYERANIMEVENT_FLINCH_LEFTARM,
	PLAYERANIMEVENT_FLINCH_RIGHTARM,
	PLAYERANIMEVENT_FLINCH_LEFTLEG,
	PLAYERANIMEVENT_FLINCH_RIGHTLEG,
	PLAYERANIMEVENT_DOUBLEJUMP,

	// Cancel.
	PLAYERANIMEVENT_CANCEL,
	PLAYERANIMEVENT_SPAWN,

	// Snap to current yaw exactly
	PLAYERANIMEVENT_SNAP_YAW,

	PLAYERANIMEVENT_CUSTOM,				// Used to play specific activities
	PLAYERANIMEVENT_CUSTOM_GESTURE,
	PLAYERANIMEVENT_CUSTOM_SEQUENCE,	// Used to play specific sequences
	PLAYERANIMEVENT_CUSTOM_GESTURE_SEQUENCE,

	// TF Specific. Here until there's a derived game solution to this.
	PLAYERANIMEVENT_ATTACK_PRE,
	PLAYERANIMEVENT_ATTACK_POST,
	PLAYERANIMEVENT_GRENADE1_DRAW,
	PLAYERANIMEVENT_GRENADE2_DRAW,
	PLAYERANIMEVENT_GRENADE1_THROW,
	PLAYERANIMEVENT_GRENADE2_THROW,
	PLAYERANIMEVENT_VOICE_COMMAND_GESTURE,
	PLAYERANIMEVENT_DOUBLEJUMP_CROUCH,
	PLAYERANIMEVENT_STUN_BEGIN,
	PLAYERANIMEVENT_STUN_MIDDLE,
	PLAYERANIMEVENT_STUN_END,
	PLAYERANIMEVENT_PASSTIME_THROW_BEGIN,
	PLAYERANIMEVENT_PASSTIME_THROW_MIDDLE,
	PLAYERANIMEVENT_PASSTIME_THROW_END,
	PLAYERANIMEVENT_PASSTIME_THROW_CANCEL,

	PLAYERANIMEVENT_ATTACK_PRIMARY_SUPER,

	PLAYERANIMEVENT_COUNT
};

enum CCSGOAnimStatePoses
{
	ACT_RESET,
	ACT_IDLE,
	ACT_TRANSITION,
	ACT_COVER,
	ACT_COVER_MED,
	ACT_COVER_LOW,
	ACT_WALK,
	ACT_WALK_AIM,
	ACT_WALK_CROUCH,
	ACT_WALK_CROUCH_AIM,
	ACT_RUN,
	ACT_RUN_AIM,
	ACT_RUN_CROUCH,
	ACT_RUN_CROUCH_AIM,
	ACT_RUN_PROTECTED,
	ACT_SCRIPT_CUSTOM_MOVE,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_RANGE_ATTACK1_LOW,
	ACT_RANGE_ATTACK2_LOW,
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_DIERAGDOLL,
	ACT_FLY,
	ACT_HOVER,
	ACT_GLIDE,
	ACT_SWIM,
	ACT_JUMP,
	ACT_HOP,
	ACT_LEAP,
	ACT_LAND,
	ACT_CLIMB_UP,
	ACT_CLIMB_DOWN,
	ACT_CLIMB_DISMOUNT,
	ACT_SHIPLADDER_UP,
	ACT_SHIPLADDER_DOWN,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,
	ACT_ROLL_RIGHT,
	ACT_TURN_LEFT,
	ACT_TURN_RIGHT,
	ACT_CROUCH,
	ACT_CROUCHIDLE,
	ACT_STAND,
	ACT_USE,
	ACT_ALIEN_BURROW_IDLE,
	ACT_ALIEN_BURROW_OUT,
	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,
	ACT_SIGNAL_ADVANCE,
	ACT_SIGNAL_FORWARD,
	ACT_SIGNAL_GROUP,
	ACT_SIGNAL_HALT,
	ACT_SIGNAL_LEFT,
	ACT_SIGNAL_RIGHT,
	ACT_SIGNAL_TAKECOVER,
	ACT_LOOKBACK_RIGHT,
	ACT_LOOKBACK_LEFT,
	ACT_COWER,
	ACT_SMALL_FLINCH,
	ACT_BIG_FLINCH,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_RELOAD_START,
	ACT_RELOAD_FINISH,
	ACT_RELOAD_LOW,
	ACT_ARM,
	ACT_DISARM,
	ACT_DROP_WEAPON,
	ACT_DROP_WEAPON_SHOTGUN,
	ACT_PICKUP_GROUND,
	ACT_PICKUP_RACK,
	ACT_IDLE_ANGRY,
	ACT_IDLE_RELAXED,
	ACT_IDLE_STIMULATED,
	ACT_IDLE_AGITATED,
	ACT_IDLE_STEALTH,
	ACT_IDLE_HURT,
	ACT_WALK_RELAXED,
	ACT_WALK_STIMULATED,
	ACT_WALK_AGITATED,
	ACT_WALK_STEALTH,
	ACT_RUN_RELAXED,
	ACT_RUN_STIMULATED,
	ACT_RUN_AGITATED,
	ACT_RUN_STEALTH,
	ACT_IDLE_AIM_RELAXED,
	ACT_IDLE_AIM_STIMULATED,
	ACT_IDLE_AIM_AGITATED,
	ACT_IDLE_AIM_STEALTH,
	ACT_WALK_AIM_RELAXED,
	ACT_WALK_AIM_STIMULATED,
	ACT_WALK_AIM_AGITATED,
	ACT_WALK_AIM_STEALTH,
	ACT_RUN_AIM_RELAXED,
	ACT_RUN_AIM_STIMULATED,
	ACT_RUN_AIM_AGITATED,
	ACT_RUN_AIM_STEALTH,
	ACT_CROUCHIDLE_STIMULATED,
	ACT_CROUCHIDLE_AIM_STIMULATED,
	ACT_CROUCHIDLE_AGITATED,
	ACT_WALK_HURT,
	ACT_RUN_HURT,
	ACT_SPECIAL_ATTACK1,
	ACT_SPECIAL_ATTACK2,
	ACT_COMBAT_IDLE,
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,
	ACT_DIE_HEADSHOT,
	ACT_DIE_CHESTSHOT,
	ACT_DIE_GUTSHOT,
	ACT_DIE_BACKSHOT,
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
	ACT_FLINCH_PHYSICS,
	ACT_FLINCH_HEAD_BACK,
	ACT_FLINCH_HEAD_LEFT,
	ACT_FLINCH_HEAD_RIGHT,
	ACT_FLINCH_CHEST_BACK,
	ACT_FLINCH_STOMACH_BACK,
	ACT_FLINCH_CROUCH_FRONT,
	ACT_FLINCH_CROUCH_BACK,
	ACT_FLINCH_CROUCH_LEFT,
	ACT_FLINCH_CROUCH_RIGHT,
	ACT_IDLE_ON_FIRE,
	ACT_WALK_ON_FIRE,
	ACT_RUN_ON_FIRE,
	ACT_RAPPEL_LOOP,
	ACT_180_LEFT,
	ACT_180_RIGHT,
	ACT_90_LEFT,
	ACT_90_RIGHT,
	ACT_STEP_LEFT,
	ACT_STEP_RIGHT,
	ACT_STEP_BACK,
	ACT_STEP_FORE,
	ACT_GESTURE_RANGE_ATTACK1,
	ACT_GESTURE_RANGE_ATTACK2,
	ACT_GESTURE_MELEE_ATTACK1,
	ACT_GESTURE_MELEE_ATTACK2,
	ACT_GESTURE_RANGE_ATTACK1_LOW,
	ACT_GESTURE_RANGE_ATTACK2_LOW,
	ACT_MELEE_ATTACK_SWING_GESTURE,
	ACT_GESTURE_SMALL_FLINCH,
	ACT_GESTURE_BIG_FLINCH,
	ACT_GESTURE_FLINCH_BLAST,
	ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
	ACT_GESTURE_FLINCH_BLAST_DAMAGED,
	ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
	ACT_GESTURE_FLINCH_HEAD,
	ACT_GESTURE_FLINCH_CHEST,
	ACT_GESTURE_FLINCH_STOMACH,
	ACT_GESTURE_FLINCH_LEFTARM,
	ACT_GESTURE_FLINCH_RIGHTARM,
	ACT_GESTURE_FLINCH_LEFTLEG,
	ACT_GESTURE_FLINCH_RIGHTLEG,
	ACT_GESTURE_TURN_LEFT,
	ACT_GESTURE_TURN_RIGHT,
	ACT_GESTURE_TURN_LEFT45,
	ACT_GESTURE_TURN_RIGHT45,
	ACT_GESTURE_TURN_LEFT90,
	ACT_GESTURE_TURN_RIGHT90,
	ACT_GESTURE_TURN_LEFT45_FLAT,
	ACT_GESTURE_TURN_RIGHT45_FLAT,
	ACT_GESTURE_TURN_LEFT90_FLAT,
	ACT_GESTURE_TURN_RIGHT90_FLAT,
	ACT_BARNACLE_HIT,
	ACT_BARNACLE_PULL,
	ACT_BARNACLE_CHOMP,
	ACT_BARNACLE_CHEW,
	ACT_DO_NOT_DISTURB,
	ACT_SPECIFIC_SEQUENCE,
	ACT_VM_DRAW,
	ACT_VM_HOLSTER,
	ACT_VM_IDLE,
	ACT_VM_FIDGET,
	ACT_VM_PULLBACK,
	ACT_VM_PULLBACK_HIGH,
	ACT_VM_PULLBACK_LOW,
	ACT_VM_THROW,
	ACT_VM_PULLPIN,
	ACT_VM_PRIMARYATTACK,
	ACT_VM_SECONDARYATTACK,
	ACT_VM_RELOAD,
	ACT_VM_DRYFIRE,
	ACT_VM_HITLEFT,
	ACT_VM_HITLEFT2,
	ACT_VM_HITRIGHT,
	ACT_VM_HITRIGHT2,
	ACT_VM_HITCENTER,
	ACT_VM_HITCENTER2,
	ACT_VM_MISSLEFT,
	ACT_VM_MISSLEFT2,
	ACT_VM_MISSRIGHT,
	ACT_VM_MISSRIGHT2,
	ACT_VM_MISSCENTER,
	ACT_VM_MISSCENTER2,
	ACT_VM_HAULBACK,
	ACT_VM_SWINGHARD,
	ACT_VM_SWINGMISS,
	ACT_VM_SWINGHIT,
	ACT_VM_IDLE_TO_LOWERED,
	ACT_VM_IDLE_LOWERED,
	ACT_VM_LOWERED_TO_IDLE,
	ACT_VM_RECOIL1,
	ACT_VM_RECOIL2,
	ACT_VM_RECOIL3,
	ACT_VM_PICKUP,
	ACT_VM_RELEASE,
	ACT_VM_ATTACH_SILENCER,
	ACT_VM_DETACH_SILENCER,
	ACT_VM_EMPTY_FIRE,
	ACT_VM_EMPTY_RELOAD,
	ACT_VM_EMPTY_DRAW,
	ACT_VM_EMPTY_IDLE,
	ACT_SLAM_STICKWALL_IDLE,
	ACT_SLAM_STICKWALL_ND_IDLE,
	ACT_SLAM_STICKWALL_ATTACH,
	ACT_SLAM_STICKWALL_ATTACH2,
	ACT_SLAM_STICKWALL_ND_ATTACH,
	ACT_SLAM_STICKWALL_ND_ATTACH2,
	ACT_SLAM_STICKWALL_DETONATE,
	ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
	ACT_SLAM_STICKWALL_DRAW,
	ACT_SLAM_STICKWALL_ND_DRAW,
	ACT_SLAM_STICKWALL_TO_THROW,
	ACT_SLAM_STICKWALL_TO_THROW_ND,
	ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
	ACT_SLAM_THROW_IDLE,
	ACT_SLAM_THROW_ND_IDLE,
	ACT_SLAM_THROW_THROW,
	ACT_SLAM_THROW_THROW2,
	ACT_SLAM_THROW_THROW_ND,
	ACT_SLAM_THROW_THROW_ND2,
	ACT_SLAM_THROW_DRAW,
	ACT_SLAM_THROW_ND_DRAW,
	ACT_SLAM_THROW_TO_STICKWALL,
	ACT_SLAM_THROW_TO_STICKWALL_ND,
	ACT_SLAM_THROW_DETONATE,
	ACT_SLAM_THROW_DETONATOR_HOLSTER,
	ACT_SLAM_THROW_TO_TRIPMINE_ND,
	ACT_SLAM_TRIPMINE_IDLE,
	ACT_SLAM_TRIPMINE_DRAW,
	ACT_SLAM_TRIPMINE_ATTACH,
	ACT_SLAM_TRIPMINE_ATTACH2,
	ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
	ACT_SLAM_TRIPMINE_TO_THROW_ND,
	ACT_SLAM_DETONATOR_IDLE,
	ACT_SLAM_DETONATOR_DRAW,
	ACT_SLAM_DETONATOR_DETONATE,
	ACT_SLAM_DETONATOR_HOLSTER,
	ACT_SLAM_DETONATOR_STICKWALL_DRAW,
	ACT_SLAM_DETONATOR_THROW_DRAW,
	ACT_SHOTGUN_RELOAD_START,
	ACT_SHOTGUN_RELOAD_FINISH,
	ACT_SHOTGUN_PUMP,
	ACT_SMG2_IDLE2,
	ACT_SMG2_FIRE2,
	ACT_SMG2_DRAW2,
	ACT_SMG2_RELOAD2,
	ACT_SMG2_DRYFIRE2,
	ACT_SMG2_TOAUTO,
	ACT_SMG2_TOBURST,
	ACT_PHYSCANNON_UPGRADE,
	ACT_RANGE_ATTACK_AR1,
	ACT_RANGE_ATTACK_AR2,
	ACT_RANGE_ATTACK_AR2_LOW,
	ACT_RANGE_ATTACK_AR2_GRENADE,
	ACT_RANGE_ATTACK_HMG1,
	ACT_RANGE_ATTACK_ML,
	ACT_RANGE_ATTACK_SMG1,
	ACT_RANGE_ATTACK_SMG1_LOW,
	ACT_RANGE_ATTACK_SMG2,
	ACT_RANGE_ATTACK_SHOTGUN,
	ACT_RANGE_ATTACK_SHOTGUN_LOW,
	ACT_RANGE_ATTACK_PISTOL,
	ACT_RANGE_ATTACK_PISTOL_LOW,
	ACT_RANGE_ATTACK_SLAM,
	ACT_RANGE_ATTACK_TRIPWIRE,
	ACT_RANGE_ATTACK_THROW,
	ACT_RANGE_ATTACK_SNIPER_RIFLE,
	ACT_RANGE_ATTACK_RPG,
	ACT_MELEE_ATTACK_SWING,
	ACT_RANGE_AIM_LOW,
	ACT_RANGE_AIM_SMG1_LOW,
	ACT_RANGE_AIM_PISTOL_LOW,
	ACT_RANGE_AIM_AR2_LOW,
	ACT_COVER_PISTOL_LOW,
	ACT_COVER_SMG1_LOW,
	ACT_GESTURE_RANGE_ATTACK_AR1,
	ACT_GESTURE_RANGE_ATTACK_AR2,
	ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
	ACT_GESTURE_RANGE_ATTACK_HMG1,
	ACT_GESTURE_RANGE_ATTACK_ML,
	ACT_GESTURE_RANGE_ATTACK_SMG1,
	ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
	ACT_GESTURE_RANGE_ATTACK_SMG2,
	ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
	ACT_GESTURE_RANGE_ATTACK_PISTOL,
	ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
	ACT_GESTURE_RANGE_ATTACK_SLAM,
	ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
	ACT_GESTURE_RANGE_ATTACK_THROW,
	ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
	ACT_GESTURE_MELEE_ATTACK_SWING,
	ACT_IDLE_RIFLE,
	ACT_IDLE_SMG1,
	ACT_IDLE_ANGRY_SMG1,
	ACT_IDLE_PISTOL,
	ACT_IDLE_ANGRY_PISTOL,
	ACT_IDLE_ANGRY_SHOTGUN,
	ACT_IDLE_STEALTH_PISTOL,
	ACT_IDLE_PACKAGE,
	ACT_WALK_PACKAGE,
	ACT_IDLE_SUITCASE,
	ACT_WALK_SUITCASE,
	ACT_IDLE_SMG1_RELAXED,
	ACT_IDLE_SMG1_STIMULATED,
	ACT_WALK_RIFLE_RELAXED,
	ACT_RUN_RIFLE_RELAXED,
	ACT_WALK_RIFLE_STIMULATED,
	ACT_RUN_RIFLE_STIMULATED,
	ACT_IDLE_AIM_RIFLE_STIMULATED,
	ACT_WALK_AIM_RIFLE_STIMULATED,
	ACT_RUN_AIM_RIFLE_STIMULATED,
	ACT_IDLE_SHOTGUN_RELAXED,
	ACT_IDLE_SHOTGUN_STIMULATED,
	ACT_IDLE_SHOTGUN_AGITATED,
	ACT_WALK_ANGRY,
	ACT_POLICE_HARASS1,
	ACT_POLICE_HARASS2,
	ACT_IDLE_MANNEDGUN,
	ACT_IDLE_MELEE,
	ACT_IDLE_ANGRY_MELEE,
	ACT_IDLE_RPG_RELAXED,
	ACT_IDLE_RPG,
	ACT_IDLE_ANGRY_RPG,
	ACT_COVER_LOW_RPG,
	ACT_WALK_RPG,
	ACT_RUN_RPG,
	ACT_WALK_CROUCH_RPG,
	ACT_RUN_CROUCH_RPG,
	ACT_WALK_RPG_RELAXED,
	ACT_RUN_RPG_RELAXED,
	ACT_WALK_RIFLE,
	ACT_WALK_AIM_RIFLE,
	ACT_WALK_CROUCH_RIFLE,
	ACT_WALK_CROUCH_AIM_RIFLE,
	ACT_RUN_RIFLE,
	ACT_RUN_AIM_RIFLE,
	ACT_RUN_CROUCH_RIFLE,
	ACT_RUN_CROUCH_AIM_RIFLE,
	ACT_RUN_STEALTH_PISTOL,
	ACT_WALK_AIM_SHOTGUN,
	ACT_RUN_AIM_SHOTGUN,
	ACT_WALK_PISTOL,
	ACT_RUN_PISTOL,
	ACT_WALK_AIM_PISTOL,
	ACT_RUN_AIM_PISTOL,
	ACT_WALK_STEALTH_PISTOL,
	ACT_WALK_AIM_STEALTH_PISTOL,
	ACT_RUN_AIM_STEALTH_PISTOL,
	ACT_RELOAD_PISTOL,
	ACT_RELOAD_PISTOL_LOW,
	ACT_RELOAD_SMG1,
	ACT_RELOAD_SMG1_LOW,
	ACT_RELOAD_SHOTGUN,
	ACT_RELOAD_SHOTGUN_LOW,
	ACT_GESTURE_RELOAD,
	ACT_GESTURE_RELOAD_PISTOL,
	ACT_GESTURE_RELOAD_SMG1,
	ACT_GESTURE_RELOAD_SHOTGUN,
	ACT_BUSY_LEAN_LEFT,
	ACT_BUSY_LEAN_LEFT_ENTRY,
	ACT_BUSY_LEAN_LEFT_EXIT,
	ACT_BUSY_LEAN_BACK,
	ACT_BUSY_LEAN_BACK_ENTRY,
	ACT_BUSY_LEAN_BACK_EXIT,
	ACT_BUSY_SIT_GROUND,
	ACT_BUSY_SIT_GROUND_ENTRY,
	ACT_BUSY_SIT_GROUND_EXIT,
	ACT_BUSY_SIT_CHAIR,
	ACT_BUSY_SIT_CHAIR_ENTRY,
	ACT_BUSY_SIT_CHAIR_EXIT,
	ACT_BUSY_STAND,
	ACT_BUSY_QUEUE,
	ACT_DUCK_DODGE,
	ACT_DIE_BARNACLE_SWALLOW,
	ACT_GESTURE_BARNACLE_STRANGLE,
	ACT_PHYSCANNON_DETACH,
	ACT_PHYSCANNON_ANIMATE,
	ACT_PHYSCANNON_ANIMATE_PRE,
	ACT_PHYSCANNON_ANIMATE_POST,
	ACT_DIE_FRONTSIDE,
	ACT_DIE_RIGHTSIDE,
	ACT_DIE_BACKSIDE,
	ACT_DIE_LEFTSIDE,
	ACT_DIE_CROUCH_FRONTSIDE,
	ACT_DIE_CROUCH_RIGHTSIDE,
	ACT_DIE_CROUCH_BACKSIDE,
	ACT_DIE_CROUCH_LEFTSIDE,
	ACT_OPEN_DOOR,
	ACT_DI_ALYX_ZOMBIE_MELEE,
	ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
	ACT_DI_ALYX_HEADCRAB_MELEE,
	ACT_DI_ALYX_ANTLION,
	ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
	ACT_DI_ALYX_ZOMBIE_SHOTGUN26,
	ACT_READINESS_RELAXED_TO_STIMULATED,
	ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
	ACT_READINESS_AGITATED_TO_STIMULATED,
	ACT_READINESS_STIMULATED_TO_RELAXED,
	ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
	ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
	ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
	ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,
	ACT_IDLE_CARRY,
	ACT_WALK_CARRY,
	ACT_STARTDYING,
	ACT_DYINGLOOP,
	ACT_DYINGTODEAD,
	ACT_RIDE_MANNED_GUN,
	ACT_VM_SPRINT_ENTER,
	ACT_VM_SPRINT_IDLE,
	ACT_VM_SPRINT_LEAVE,
	ACT_FIRE_START,
	ACT_FIRE_LOOP,
	ACT_FIRE_END,
	ACT_CROUCHING_GRENADEIDLE,
	ACT_CROUCHING_GRENADEREADY,
	ACT_CROUCHING_PRIMARYATTACK,
	ACT_OVERLAY_GRENADEIDLE,
	ACT_OVERLAY_GRENADEREADY,
	ACT_OVERLAY_PRIMARYATTACK,
	ACT_OVERLAY_SHIELD_UP,
	ACT_OVERLAY_SHIELD_DOWN,
	ACT_OVERLAY_SHIELD_UP_IDLE,
	ACT_OVERLAY_SHIELD_ATTACK,
	ACT_OVERLAY_SHIELD_KNOCKBACK,
	ACT_SHIELD_UP,
	ACT_SHIELD_DOWN,
	ACT_SHIELD_UP_IDLE,
	ACT_SHIELD_ATTACK,
	ACT_SHIELD_KNOCKBACK,
	ACT_CROUCHING_SHIELD_UP,
	ACT_CROUCHING_SHIELD_DOWN,
	ACT_CROUCHING_SHIELD_UP_IDLE,
	ACT_CROUCHING_SHIELD_ATTACK,
	ACT_CROUCHING_SHIELD_KNOCKBACK,
	ACT_TURNRIGHT45,
	ACT_TURNLEFT45,
	ACT_TURN,
	ACT_OBJ_ASSEMBLING,
	ACT_OBJ_DISMANTLING,
	ACT_OBJ_STARTUP,
	ACT_OBJ_RUNNING,
	ACT_OBJ_IDLE,
	ACT_OBJ_PLACING,
	ACT_OBJ_DETERIORATING,
	ACT_OBJ_UPGRADING,
	ACT_DEPLOY,
	ACT_DEPLOY_IDLE,
	ACT_UNDEPLOY,
	ACT_CROSSBOW_DRAW_UNLOADED,
	ACT_GAUSS_SPINUP,
	ACT_GAUSS_SPINCYCLE,
	ACT_VM_PRIMARYATTACK_SILENCED,
	ACT_VM_RELOAD_SILENCED,
	ACT_VM_DRYFIRE_SILENCED,
	ACT_VM_IDLE_SILENCED,
	ACT_VM_DRAW_SILENCED,
	ACT_VM_IDLE_EMPTY_LEFT,
	ACT_VM_DRYFIRE_LEFT,
	ACT_VM_IS_DRAW,
	ACT_VM_IS_HOLSTER,
	ACT_VM_IS_IDLE,
	ACT_VM_IS_PRIMARYATTACK,
	ACT_PLAYER_IDLE_FIRE,
	ACT_PLAYER_CROUCH_FIRE,
	ACT_PLAYER_CROUCH_WALK_FIRE,
	ACT_PLAYER_WALK_FIRE,
	ACT_PLAYER_RUN_FIRE,
	ACT_IDLETORUN,
	ACT_RUNTOIDLE,
	ACT_VM_DRAW_DEPLOYED,
	ACT_HL2MP_IDLE_MELEE,
	ACT_HL2MP_RUN_MELEE,
	ACT_HL2MP_IDLE_CROUCH_MELEE,
	ACT_HL2MP_WALK_CROUCH_MELEE,
	ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
	ACT_HL2MP_GESTURE_RELOAD_MELEE,
	ACT_HL2MP_JUMP_MELEE,
	ACT_VM_FIZZLE,
	ACT_MP_STAND_IDLE,
	ACT_MP_CROUCH_IDLE,
	ACT_MP_CROUCH_DEPLOYED_IDLE,
	ACT_MP_CROUCH_DEPLOYED,
	ACT_MP_DEPLOYED_IDLE,
	ACT_MP_RUN,
	ACT_MP_WALK,
	ACT_MP_AIRWALK,
	ACT_MP_CROUCHWALK,
	ACT_MP_SPRINT,
	ACT_MP_JUMP,
	ACT_MP_JUMP_START,
	ACT_MP_JUMP_FLOAT,
	ACT_MP_JUMP_LAND,
	ACT_MP_JUMP_IMPACT_N,
	ACT_MP_JUMP_IMPACT_E,
	ACT_MP_JUMP_IMPACT_W,
	ACT_MP_JUMP_IMPACT_S,
	ACT_MP_JUMP_IMPACT_TOP,
	ACT_MP_DOUBLEJUMP,
	ACT_MP_SWIM,
	ACT_MP_DEPLOYED,
	ACT_MP_SWIM_DEPLOYED,
	ACT_MP_VCD,
	ACT_MP_ATTACK_STAND_PRIMARYFIRE,
	ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
	ACT_MP_ATTACK_STAND_SECONDARYFIRE,
	ACT_MP_ATTACK_STAND_GRENADE,
	ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
	ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
	ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
	ACT_MP_ATTACK_CROUCH_GRENADE,
	ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
	ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
	ACT_MP_ATTACK_SWIM_GRENADE,
	ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
	ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
	ACT_MP_ATTACK_AIRWALK_GRENADE,
	ACT_MP_RELOAD_STAND,
	ACT_MP_RELOAD_STAND_LOOP,
	ACT_MP_RELOAD_STAND_END,
	ACT_MP_RELOAD_CROUCH,
	ACT_MP_RELOAD_CROUCH_LOOP,
	ACT_MP_RELOAD_CROUCH_END,
	ACT_MP_RELOAD_SWIM,
	ACT_MP_RELOAD_SWIM_LOOP,
	ACT_MP_RELOAD_SWIM_END,
	ACT_MP_RELOAD_AIRWALK,
	ACT_MP_RELOAD_AIRWALK_LOOP,
	ACT_MP_RELOAD_AIRWALK_END,
	ACT_MP_ATTACK_STAND_PREFIRE,
	ACT_MP_ATTACK_STAND_POSTFIRE,
	ACT_MP_ATTACK_STAND_STARTFIRE,
	ACT_MP_ATTACK_CROUCH_PREFIRE,
	ACT_MP_ATTACK_CROUCH_POSTFIRE,
	ACT_MP_ATTACK_SWIM_PREFIRE,
	ACT_MP_ATTACK_SWIM_POSTFIRE,
	ACT_MP_STAND_PRIMARY,
	ACT_MP_CROUCH_PRIMARY,
	ACT_MP_RUN_PRIMARY,
	ACT_MP_WALK_PRIMARY,
	ACT_MP_AIRWALK_PRIMARY,
	ACT_MP_CROUCHWALK_PRIMARY,
	ACT_MP_JUMP_PRIMARY,
	ACT_MP_JUMP_START_PRIMARY,
	ACT_MP_JUMP_FLOAT_PRIMARY,
	ACT_MP_JUMP_LAND_PRIMARY,
	ACT_MP_SWIM_PRIMARY,
	ACT_MP_DEPLOYED_PRIMARY,
	ACT_MP_SWIM_DEPLOYED_PRIMARY,
	ACT_MP_ATTACK_STAND_PRIMARY,
	ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
	ACT_MP_ATTACK_CROUCH_PRIMARY,
	ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
	ACT_MP_ATTACK_SWIM_PRIMARY,
	ACT_MP_ATTACK_AIRWALK_PRIMARY,
	ACT_MP_RELOAD_STAND_PRIMARY,
	ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
	ACT_MP_RELOAD_STAND_PRIMARY_END,
	ACT_MP_RELOAD_CROUCH_PRIMARY,
	ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
	ACT_MP_RELOAD_CROUCH_PRIMARY_END,
	ACT_MP_RELOAD_SWIM_PRIMARY,
	ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
	ACT_MP_RELOAD_SWIM_PRIMARY_END,
	ACT_MP_RELOAD_AIRWALK_PRIMARY,
	ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
	ACT_MP_RELOAD_AIRWALK_PRIMARY_END,
	ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,
	ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,
	ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
	ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,
	ACT_MP_STAND_SECONDARY,
	ACT_MP_CROUCH_SECONDARY,
	ACT_MP_RUN_SECONDARY,
	ACT_MP_WALK_SECONDARY,
	ACT_MP_AIRWALK_SECONDARY,
	ACT_MP_CROUCHWALK_SECONDARY,
	ACT_MP_JUMP_SECONDARY,
	ACT_MP_JUMP_START_SECONDARY,
	ACT_MP_JUMP_FLOAT_SECONDARY,
	ACT_MP_JUMP_LAND_SECONDARY,
	ACT_MP_SWIM_SECONDARY,
	ACT_MP_ATTACK_STAND_SECONDARY,
	ACT_MP_ATTACK_CROUCH_SECONDARY,
	ACT_MP_ATTACK_SWIM_SECONDARY,
	ACT_MP_ATTACK_AIRWALK_SECONDARY,
	ACT_MP_RELOAD_STAND_SECONDARY,
	ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
	ACT_MP_RELOAD_STAND_SECONDARY_END,
	ACT_MP_RELOAD_CROUCH_SECONDARY,
	ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
	ACT_MP_RELOAD_CROUCH_SECONDARY_END,
	ACT_MP_RELOAD_SWIM_SECONDARY,
	ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
	ACT_MP_RELOAD_SWIM_SECONDARY_END,
	ACT_MP_RELOAD_AIRWALK_SECONDARY,
	ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
	ACT_MP_RELOAD_AIRWALK_SECONDARY_END,
	ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,
	ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,
	ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
	ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,
	ACT_MP_STAND_MELEE,
	ACT_MP_CROUCH_MELEE,
	ACT_MP_RUN_MELEE,
	ACT_MP_WALK_MELEE,
	ACT_MP_AIRWALK_MELEE,
	ACT_MP_CROUCHWALK_MELEE,
	ACT_MP_JUMP_MELEE,
	ACT_MP_JUMP_START_MELEE,
	ACT_MP_JUMP_FLOAT_MELEE,
	ACT_MP_JUMP_LAND_MELEE,
	ACT_MP_SWIM_MELEE,
	ACT_MP_ATTACK_STAND_MELEE,
	ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
	ACT_MP_ATTACK_CROUCH_MELEE,
	ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
	ACT_MP_ATTACK_SWIM_MELEE,
	ACT_MP_ATTACK_AIRWALK_MELEE,
	ACT_MP_ATTACK_STAND_GRENADE_MELEE,
	ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,
	ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
	ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,
	ACT_MP_STAND_ITEM1,
	ACT_MP_CROUCH_ITEM1,
	ACT_MP_RUN_ITEM1,
	ACT_MP_WALK_ITEM1,
	ACT_MP_AIRWALK_ITEM1,
	ACT_MP_CROUCHWALK_ITEM1,
	ACT_MP_JUMP_ITEM1,
	ACT_MP_JUMP_START_ITEM1,
	ACT_MP_JUMP_FLOAT_ITEM1,
	ACT_MP_JUMP_LAND_ITEM1,
	ACT_MP_SWIM_ITEM1,
	ACT_MP_ATTACK_STAND_ITEM1,
	ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
	ACT_MP_ATTACK_CROUCH_ITEM1,
	ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
	ACT_MP_ATTACK_SWIM_ITEM1,
	ACT_MP_ATTACK_AIRWALK_ITEM1,
	ACT_MP_STAND_ITEM2,
	ACT_MP_CROUCH_ITEM2,
	ACT_MP_RUN_ITEM2,
	ACT_MP_WALK_ITEM2,
	ACT_MP_AIRWALK_ITEM2,
	ACT_MP_CROUCHWALK_ITEM2,
	ACT_MP_JUMP_ITEM2,
	ACT_MP_JUMP_START_ITEM2,
	ACT_MP_JUMP_FLOAT_ITEM2,
	ACT_MP_JUMP_LAND_ITEM2,
	ACT_MP_SWIM_ITEM2,
	ACT_MP_ATTACK_STAND_ITEM2,
	ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
	ACT_MP_ATTACK_CROUCH_ITEM2,
	ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
	ACT_MP_ATTACK_SWIM_ITEM2,
	ACT_MP_ATTACK_AIRWALK_ITEM2,
	ACT_MP_GESTURE_FLINCH,
	ACT_MP_GESTURE_FLINCH_PRIMARY,
	ACT_MP_GESTURE_FLINCH_SECONDARY,
	ACT_MP_GESTURE_FLINCH_MELEE,
	ACT_MP_GESTURE_FLINCH_ITEM1,
	ACT_MP_GESTURE_FLINCH_ITEM2,
	ACT_MP_GESTURE_FLINCH_HEAD,
	ACT_MP_GESTURE_FLINCH_CHEST,
	ACT_MP_GESTURE_FLINCH_STOMACH,
	ACT_MP_GESTURE_FLINCH_LEFTARM,
	ACT_MP_GESTURE_FLINCH_RIGHTARM,
	ACT_MP_GESTURE_FLINCH_LEFTLEG,
	ACT_MP_GESTURE_FLINCH_RIGHTLEG,
	ACT_MP_GRENADE1_DRAW,
	ACT_MP_GRENADE1_IDLE,
	ACT_MP_GRENADE1_ATTACK,
	ACT_MP_GRENADE2_DRAW,
	ACT_MP_GRENADE2_IDLE,
	ACT_MP_GRENADE2_ATTACK,
	ACT_MP_PRIMARY_GRENADE1_DRAW,
	ACT_MP_PRIMARY_GRENADE1_IDLE,
	ACT_MP_PRIMARY_GRENADE1_ATTACK,
	ACT_MP_PRIMARY_GRENADE2_DRAW,
	ACT_MP_PRIMARY_GRENADE2_IDLE,
	ACT_MP_PRIMARY_GRENADE2_ATTACK,
	ACT_MP_SECONDARY_GRENADE1_DRAW,
	ACT_MP_SECONDARY_GRENADE1_IDLE,
	ACT_MP_SECONDARY_GRENADE1_ATTACK,
	ACT_MP_SECONDARY_GRENADE2_DRAW,
	ACT_MP_SECONDARY_GRENADE2_IDLE,
	ACT_MP_SECONDARY_GRENADE2_ATTACK,
	ACT_MP_MELEE_GRENADE1_DRAW,
	ACT_MP_MELEE_GRENADE1_IDLE,
	ACT_MP_MELEE_GRENADE1_ATTACK,
	ACT_MP_MELEE_GRENADE2_DRAW,
	ACT_MP_MELEE_GRENADE2_IDLE,
	ACT_MP_MELEE_GRENADE2_ATTACK,
	ACT_MP_ITEM1_GRENADE1_DRAW,
	ACT_MP_ITEM1_GRENADE1_IDLE,
	ACT_MP_ITEM1_GRENADE1_ATTACK,
	ACT_MP_ITEM1_GRENADE2_DRAW,
	ACT_MP_ITEM1_GRENADE2_IDLE,
	ACT_MP_ITEM1_GRENADE2_ATTACK,
	ACT_MP_ITEM2_GRENADE1_DRAW,
	ACT_MP_ITEM2_GRENADE1_IDLE,
	ACT_MP_ITEM2_GRENADE1_ATTACK,
	ACT_MP_ITEM2_GRENADE2_DRAW,
	ACT_MP_ITEM2_GRENADE2_IDLE,
	ACT_MP_ITEM2_GRENADE2_ATTACK,
	ACT_MP_STAND_BUILDING,
	ACT_MP_CROUCH_BUILDING,
	ACT_MP_RUN_BUILDING,
	ACT_MP_WALK_BUILDING,
	ACT_MP_AIRWALK_BUILDING,
	ACT_MP_CROUCHWALK_BUILDING,
	ACT_MP_JUMP_BUILDING,
	ACT_MP_JUMP_START_BUILDING,
	ACT_MP_JUMP_FLOAT_BUILDING,
	ACT_MP_JUMP_LAND_BUILDING,
	ACT_MP_SWIM_BUILDING,
	ACT_MP_ATTACK_STAND_BUILDING,
	ACT_MP_ATTACK_CROUCH_BUILDING,
	ACT_MP_ATTACK_SWIM_BUILDING,
	ACT_MP_ATTACK_AIRWALK_BUILDING,
	ACT_MP_ATTACK_STAND_GRENADE_BUILDING,
	ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,
	ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
	ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,
	ACT_MP_STAND_PDA,
	ACT_MP_CROUCH_PDA,
	ACT_MP_RUN_PDA,
	ACT_MP_WALK_PDA,
	ACT_MP_AIRWALK_PDA,
	ACT_MP_CROUCHWALK_PDA,
	ACT_MP_JUMP_PDA,
	ACT_MP_JUMP_START_PDA,
	ACT_MP_JUMP_FLOAT_PDA,
	ACT_MP_JUMP_LAND_PDA,
	ACT_MP_SWIM_PDA,
	ACT_MP_ATTACK_STAND_PDA,
	ACT_MP_ATTACK_SWIM_PDA,
	ACT_MP_GESTURE_VC_HANDMOUTH,
	ACT_MP_GESTURE_VC_FINGERPOINT,
	ACT_MP_GESTURE_VC_FISTPUMP,
	ACT_MP_GESTURE_VC_THUMBSUP,
	ACT_MP_GESTURE_VC_NODYES,
	ACT_MP_GESTURE_VC_NODNO,
	ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
	ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
	ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
	ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
	ACT_MP_GESTURE_VC_NODYES_PRIMARY,
	ACT_MP_GESTURE_VC_NODNO_PRIMARY,
	ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
	ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
	ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
	ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
	ACT_MP_GESTURE_VC_NODYES_SECONDARY,
	ACT_MP_GESTURE_VC_NODNO_SECONDARY,
	ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
	ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
	ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
	ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
	ACT_MP_GESTURE_VC_NODYES_MELEE,
	ACT_MP_GESTURE_VC_NODNO_MELEE,
	ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
	ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
	ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
	ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
	ACT_MP_GESTURE_VC_NODYES_ITEM1,
	ACT_MP_GESTURE_VC_NODNO_ITEM1,
	ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
	ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
	ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
	ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
	ACT_MP_GESTURE_VC_NODYES_ITEM2,
	ACT_MP_GESTURE_VC_NODNO_ITEM2,
	ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
	ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
	ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
	ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
	ACT_MP_GESTURE_VC_NODYES_BUILDING,
	ACT_MP_GESTURE_VC_NODNO_BUILDING,
	ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
	ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
	ACT_MP_GESTURE_VC_FISTPUMP_PDA,
	ACT_MP_GESTURE_VC_THUMBSUP_PDA,
	ACT_MP_GESTURE_VC_NODYES_PDA,
	ACT_MP_GESTURE_VC_NODNO_PDA,
	ACT_VM_UNUSABLE,
	ACT_VM_UNUSABLE_TO_USABLE,
	ACT_VM_USABLE_TO_UNUSABLE,
	ACT_PRIMARY_VM_DRAW,
	ACT_PRIMARY_VM_HOLSTER,
	ACT_PRIMARY_VM_IDLE,
	ACT_PRIMARY_VM_PULLBACK,
	ACT_PRIMARY_VM_PRIMARYATTACK,
	ACT_PRIMARY_VM_SECONDARYATTACK,
	ACT_PRIMARY_VM_RELOAD,
	ACT_PRIMARY_VM_DRYFIRE,
	ACT_PRIMARY_VM_IDLE_TO_LOWERED,
	ACT_PRIMARY_VM_IDLE_LOWERED,
	ACT_PRIMARY_VM_LOWERED_TO_IDLE,
	ACT_SECONDARY_VM_DRAW,
	ACT_SECONDARY_VM_HOLSTER,
	ACT_SECONDARY_VM_IDLE,
	ACT_SECONDARY_VM_PULLBACK,
	ACT_SECONDARY_VM_PRIMARYATTACK,
	ACT_SECONDARY_VM_SECONDARYATTACK,
	ACT_SECONDARY_VM_RELOAD,
	ACT_SECONDARY_VM_DRYFIRE,
	ACT_SECONDARY_VM_IDLE_TO_LOWERED,
	ACT_SECONDARY_VM_IDLE_LOWERED,
	ACT_SECONDARY_VM_LOWERED_TO_IDLE,
	ACT_MELEE_VM_DRAW,
	ACT_MELEE_VM_HOLSTER,
	ACT_MELEE_VM_IDLE,
	ACT_MELEE_VM_PULLBACK,
	ACT_MELEE_VM_PRIMARYATTACK,
	ACT_MELEE_VM_SECONDARYATTACK,
	ACT_MELEE_VM_RELOAD,
	ACT_MELEE_VM_DRYFIRE,
	ACT_MELEE_VM_IDLE_TO_LOWERED,
	ACT_MELEE_VM_IDLE_LOWERED,
	ACT_MELEE_VM_LOWERED_TO_IDLE,
	ACT_PDA_VM_DRAW,
	ACT_PDA_VM_HOLSTER,
	ACT_PDA_VM_IDLE,
	ACT_PDA_VM_PULLBACK,
	ACT_PDA_VM_PRIMARYATTACK,
	ACT_PDA_VM_SECONDARYATTACK,
	ACT_PDA_VM_RELOAD,
	ACT_PDA_VM_DRYFIRE,
	ACT_PDA_VM_IDLE_TO_LOWERED,
	ACT_PDA_VM_IDLE_LOWERED,
	ACT_PDA_VM_LOWERED_TO_IDLE,
	ACT_ITEM1_VM_DRAW,
	ACT_ITEM1_VM_HOLSTER,
	ACT_ITEM1_VM_IDLE,
	ACT_ITEM1_VM_PULLBACK,
	ACT_ITEM1_VM_PRIMARYATTACK,
	ACT_ITEM1_VM_SECONDARYATTACK,
	ACT_ITEM1_VM_RELOAD,
	ACT_ITEM1_VM_DRYFIRE,
	ACT_ITEM1_VM_IDLE_TO_LOWERED,
	ACT_ITEM1_VM_IDLE_LOWERED,
	ACT_ITEM1_VM_LOWERED_TO_IDLE,
	ACT_ITEM2_VM_DRAW,
	ACT_ITEM2_VM_HOLSTER,
	ACT_ITEM2_VM_IDLE,
	ACT_ITEM2_VM_PULLBACK,
	ACT_ITEM2_VM_PRIMARYATTACK,
	ACT_ITEM2_VM_SECONDARYATTACK,
	ACT_ITEM2_VM_RELOAD,
	ACT_ITEM2_VM_DRYFIRE,
	ACT_ITEM2_VM_IDLE_TO_LOWERED,
	ACT_ITEM2_VM_IDLE_LOWERED,
	ACT_ITEM2_VM_LOWERED_TO_IDLE,
	ACT_RELOAD_SUCCEED,
	ACT_RELOAD_FAIL,
	ACT_WALK_AIM_AUTOGUN,
	ACT_RUN_AIM_AUTOGUN,
	ACT_IDLE_AUTOGUN,
	ACT_IDLE_AIM_AUTOGUN,
	ACT_RELOAD_AUTOGUN,
	ACT_CROUCH_IDLE_AUTOGUN,
	ACT_RANGE_ATTACK_AUTOGUN,
	ACT_JUMP_AUTOGUN,
	ACT_IDLE_AIM_PISTOL,
	ACT_WALK_AIM_DUAL,
	ACT_RUN_AIM_DUAL,
	ACT_IDLE_DUAL,
	ACT_IDLE_AIM_DUAL,
	ACT_RELOAD_DUAL,
	ACT_CROUCH_IDLE_DUAL,
	ACT_RANGE_ATTACK_DUAL,
	ACT_JUMP_DUAL,
	ACT_IDLE_SHOTGUN,
	ACT_IDLE_AIM_SHOTGUN,
	ACT_CROUCH_IDLE_SHOTGUN,
	ACT_JUMP_SHOTGUN,
	ACT_IDLE_AIM_RIFLE,
	ACT_RELOAD_RIFLE,
	ACT_CROUCH_IDLE_RIFLE,
	ACT_RANGE_ATTACK_RIFLE,
	ACT_JUMP_RIFLE,
	ACT_SLEEP,
	ACT_WAKE,
	ACT_FLICK_LEFT,
	ACT_FLICK_LEFT_MIDDLE,
	ACT_FLICK_RIGHT_MIDDLE,
	ACT_FLICK_RIGHT,
	ACT_SPINAROUND,
	ACT_PREP_TO_FIRE,
	ACT_FIRE,
	ACT_FIRE_RECOVER,
	ACT_SPRAY,
	ACT_PREP_EXPLODE,
	ACT_EXPLODE,
	ACT_DOTA_IDLE,
	ACT_DOTA_RUN,
	ACT_DOTA_ATTACK,
	ACT_DOTA_ATTACK_EVENT,
	ACT_DOTA_DIE,
	ACT_DOTA_FLINCH,
	ACT_DOTA_DISABLED,
	ACT_DOTA_CAST_ABILITY_1,
	ACT_DOTA_CAST_ABILITY_2,
	ACT_DOTA_CAST_ABILITY_3,
	ACT_DOTA_CAST_ABILITY_4,
	ACT_DOTA_OVERRIDE_ABILITY_1,
	ACT_DOTA_OVERRIDE_ABILITY_2,
	ACT_DOTA_OVERRIDE_ABILITY_3,
	ACT_DOTA_OVERRIDE_ABILITY_4,
	ACT_DOTA_CHANNEL_ABILITY_1,
	ACT_DOTA_CHANNEL_ABILITY_2,
	ACT_DOTA_CHANNEL_ABILITY_3,
	ACT_DOTA_CHANNEL_ABILITY_4,
	ACT_DOTA_CHANNEL_END_ABILITY_1,
	ACT_DOTA_CHANNEL_END_ABILITY_2,
	ACT_DOTA_CHANNEL_END_ABILITY_3,
	ACT_DOTA_CHANNEL_END_ABILITY_4,
	ACT_MP_RUN_SPEEDPAINT,
	ACT_MP_LONG_FALL,
	ACT_MP_TRACTORBEAM_FLOAT,
	ACT_MP_DEATH_CRUSH,
	ACT_MP_RUN_SPEEDPAINT_PRIMARY,
	ACT_MP_DROWNING_PRIMARY,
	ACT_MP_LONG_FALL_PRIMARY,
	ACT_MP_TRACTORBEAM_FLOAT_PRIMARY,
	ACT_MP_DEATH_CRUSH_PRIMARY,
	ACT_DIE_STAND,
	ACT_DIE_STAND_HEADSHOT,
	ACT_DIE_CROUCH,
	ACT_DIE_CROUCH_HEADSHOT,
	ACT_CSGO_NULL,
	ACT_CSGO_DEFUSE,
	ACT_CSGO_DEFUSE_WITH_KIT,
	ACT_CSGO_FLASHBANG_REACTION,
	ACT_CSGO_FIRE_PRIMARY,
	ACT_CSGO_FIRE_PRIMARY_OPT_1,
	ACT_CSGO_FIRE_PRIMARY_OPT_2,
	ACT_CSGO_FIRE_SECONDARY,
	ACT_CSGO_FIRE_SECONDARY_OPT_1,
	ACT_CSGO_FIRE_SECONDARY_OPT_2,
	ACT_CSGO_RELOAD,
	ACT_CSGO_RELOAD_START,
	ACT_CSGO_RELOAD_LOOP,
	ACT_CSGO_RELOAD_END,
	ACT_CSGO_OPERATE,
	ACT_CSGO_DEPLOY,
	ACT_CSGO_CATCH,
	ACT_CSGO_SILENCER_DETACH,
	ACT_CSGO_SILENCER_ATTACH,
	ACT_CSGO_TWITCH,
	ACT_CSGO_TWITCH_BUYZONE,
	ACT_CSGO_PLANT_BOMB,
	ACT_CSGO_IDLE_TURN_BALANCEADJUST,
	ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING,
	ACT_CSGO_ALIVE_LOOP,
	ACT_CSGO_FLINCH,
	ACT_CSGO_FLINCH_HEAD,
	ACT_CSGO_FLINCH_MOLOTOV,
	ACT_CSGO_JUMP,
	ACT_CSGO_FALL,
	ACT_CSGO_CLIMB_LADDER,
	ACT_CSGO_LAND_LIGHT,
	ACT_CSGO_LAND_HEAVY,
	ACT_CSGO_EXIT_LADDER_TOP,
	ACT_CSGO_EXIT_LADDER_BOTTOM,
};

enum ShaderStencilOp_t
{
#if !defined( _X360 )
	SHADER_STENCILOP_KEEP = 1,
	SHADER_STENCILOP_ZERO = 2,
	SHADER_STENCILOP_SET_TO_REFERENCE = 3,
	SHADER_STENCILOP_INCREMENT_CLAMP = 4,
	SHADER_STENCILOP_DECREMENT_CLAMP = 5,
	SHADER_STENCILOP_INVERT = 6,
	SHADER_STENCILOP_INCREMENT_WRAP = 7,
	SHADER_STENCILOP_DECREMENT_WRAP = 8,
#else
	SHADER_STENCILOP_KEEP = D3DSTENCILOP_KEEP,
	SHADER_STENCILOP_ZERO = D3DSTENCILOP_ZERO,
	SHADER_STENCILOP_SET_TO_REFERENCE = D3DSTENCILOP_REPLACE,
	SHADER_STENCILOP_INCREMENT_CLAMP = D3DSTENCILOP_INCRSAT,
	SHADER_STENCILOP_DECREMENT_CLAMP = D3DSTENCILOP_DECRSAT,
	SHADER_STENCILOP_INVERT = D3DSTENCILOP_INVERT,
	SHADER_STENCILOP_INCREMENT_WRAP = D3DSTENCILOP_INCR,
	SHADER_STENCILOP_DECREMENT_WRAP = D3DSTENCILOP_DECR,
#endif
	SHADER_STENCILOP_FORCE_DWORD = 0x7fffffff
};

enum ShaderStencilFunc_t
{
#if !defined( _X360 )
	SHADER_STENCILFUNC_NEVER = 1,
	SHADER_STENCILFUNC_LESS = 2,
	SHADER_STENCILFUNC_EQUAL = 3,
	SHADER_STENCILFUNC_LEQUAL = 4,
	SHADER_STENCILFUNC_GREATER = 5,
	SHADER_STENCILFUNC_NOTEQUAL = 6,
	SHADER_STENCILFUNC_GEQUAL = 7,
	SHADER_STENCILFUNC_ALWAYS = 8,
#else
	SHADER_STENCILFUNC_NEVER = D3DCMP_NEVER,
	SHADER_STENCILFUNC_LESS = D3DCMP_LESS,
	SHADER_STENCILFUNC_EQUAL = D3DCMP_EQUAL,
	SHADER_STENCILFUNC_LEQUAL = D3DCMP_LESSEQUAL,
	SHADER_STENCILFUNC_GREATER = D3DCMP_GREATER,
	SHADER_STENCILFUNC_NOTEQUAL = D3DCMP_NOTEQUAL,
	SHADER_STENCILFUNC_GEQUAL = D3DCMP_GREATEREQUAL,
	SHADER_STENCILFUNC_ALWAYS = D3DCMP_ALWAYS,
#endif

	SHADER_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};

#if defined( _X360 )
enum ShaderHiStencilFunc_t
{
	SHADER_HI_STENCILFUNC_EQUAL = D3DHSCMP_EQUAL,
	SHADER_HI_STENCILFUNC_NOTEQUAL = D3DHSCMP_NOTEQUAL,

	SHADER_HI_STENCILFUNC_FORCE_DWORD = 0x7fffffff
};
#endif

enum StencilOperation_t
{
#if !defined( _X360 )
	STENCILOPERATION_KEEP = 1,
	STENCILOPERATION_ZERO = 2,
	STENCILOPERATION_REPLACE = 3,
	STENCILOPERATION_INCRSAT = 4,
	STENCILOPERATION_DECRSAT = 5,
	STENCILOPERATION_INVERT = 6,
	STENCILOPERATION_INCR = 7,
	STENCILOPERATION_DECR = 8,
#else
	STENCILOPERATION_KEEP = D3DSTENCILOP_KEEP,
	STENCILOPERATION_ZERO = D3DSTENCILOP_ZERO,
	STENCILOPERATION_REPLACE = D3DSTENCILOP_REPLACE,
	STENCILOPERATION_INCRSAT = D3DSTENCILOP_INCRSAT,
	STENCILOPERATION_DECRSAT = D3DSTENCILOP_DECRSAT,
	STENCILOPERATION_INVERT = D3DSTENCILOP_INVERT,
	STENCILOPERATION_INCR = D3DSTENCILOP_INCR,
	STENCILOPERATION_DECR = D3DSTENCILOP_DECR,
#endif
	STENCILOPERATION_FORCE_DWORD = 0x7fffffff
};

enum StencilComparisonFunction_t
{
#if !defined( _X360 )
	STENCILCOMPARISONFUNCTION_NEVER = 1,
	STENCILCOMPARISONFUNCTION_LESS = 2,
	STENCILCOMPARISONFUNCTION_EQUAL = 3,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = 4,
	STENCILCOMPARISONFUNCTION_GREATER = 5,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = 6,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = 7,
	STENCILCOMPARISONFUNCTION_ALWAYS = 8,
#else
	STENCILCOMPARISONFUNCTION_NEVER = D3DCMP_NEVER,
	STENCILCOMPARISONFUNCTION_LESS = D3DCMP_LESS,
	STENCILCOMPARISONFUNCTION_EQUAL = D3DCMP_EQUAL,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = D3DCMP_LESSEQUAL,
	STENCILCOMPARISONFUNCTION_GREATER = D3DCMP_GREATER,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = D3DCMP_NOTEQUAL,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = D3DCMP_GREATEREQUAL,
	STENCILCOMPARISONFUNCTION_ALWAYS = D3DCMP_ALWAYS,
#endif

	STENCILCOMPARISONFUNCTION_FORCE_DWORD = 0x7fffffff
};

struct ShaderStencilState_t {
	bool m_bEnable;
	int m_FailOp;
	int m_ZFailOp;
	int m_PassOp;
	int m_CompareFunc;
	int m_nReferenceValue;
	uint32 m_nTestMask;
	uint32 m_nWriteMask;

	ShaderStencilState_t() {
		m_bEnable = false;
		m_PassOp = m_FailOp = m_ZFailOp = STENCILOPERATION_KEEP;
		m_CompareFunc = STENCILCOMPARISONFUNCTION_ALWAYS;
		m_nReferenceValue = 0;
		m_nTestMask = m_nWriteMask = 0xFFFFFFFF;
	}
};


class IRefCountedd
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};
class ITexture;
class IMatRenderContext : public IRefCountedd
{
public:
	virtual void				BeginRender() = 0;
	virtual void				EndRender() = 0;

	virtual void				Flush(bool flushHardware = false) = 0;

	virtual void				BindLocalCubemap(void *pTexture) = 0;

	// pass in an ITexture (that is build with "rendertarget" "1") or
	// pass in NULL for the regular backbuffer.
	virtual void				SetRenderTarget(ITexture *pTexture) = 0;
	virtual void *			GetRenderTarget() = 0;

	virtual void				GetRenderTargetDimensions(int &width, int &height) const = 0;

	// Bind a material is current for rendering.
	virtual void				Bind(void *material, void *proxyData = nullptr) = 0;
	// Bind a lightmap page current for rendering.  You only have to 
	// do this for materials that require lightmaps.
	virtual void				BindLightmapPage(int lightmapPageID) = 0;

	// inputs are between 0 and 1
	virtual void				DepthRange(float zNear, float zFar) = 0;

	virtual void				ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false) = 0;

	// read to a unsigned char rgb image.
	virtual void				ReadPixels(int x, int y, int width, int height, unsigned char *data, void* dstFormat) = 0;
	virtual void				ReadPixelsAsync(int, int, int, int, unsigned char *, void*, void *,/* CThreadEvent * */ void*) = 0;
	virtual void				ReadPixelsAsyncGetResult(int, int, int, int, unsigned char *, void*,/* CThreadEvent * */ void*) = 0;
	// Sets lighting
	virtual void				SetLightingState(void const*) = 0;
	//virtual void				SetAmbientLight(float r, float g, float b) = 0;
	virtual void				SetLights(int lightNum, const void* desc) = 0;

	// The faces of the cube are specified in the same order as cubemap textures
	virtual void				SetAmbientLightCube(void* cube[6]) = 0;

	// Blit the backbuffer to the framebuffer texture
	virtual void				CopyRenderTargetToTexture(void *pTexture) = 0;

	// Set the current texture that is a copy of the framebuffer.
	virtual void				SetFrameBufferCopyTexture(void *pTexture, int textureIndex = 0) = 0;
	virtual void		   *GetFrameBufferCopyTexture(int textureIndex) = 0;

	//
	// end vertex array api
	//

	// matrix api
	virtual void				MatrixMode(void* matrixMode) = 0;
	virtual void				PushMatrix() = 0;
	virtual void				PopMatrix() = 0;
	virtual void				LoadMatrix(VMatrix const& matrix) = 0;
	virtual void				LoadMatrix(matrix3x4_t const& matrix) = 0;
	virtual void				MultMatrix(VMatrix const& matrix) = 0;
	virtual void				MultMatrix(matrix3x4_t const& matrix) = 0;
	virtual void				MultMatrixLocal(VMatrix const& matrix) = 0;
	virtual void				MultMatrixLocal(matrix3x4_t const& matrix) = 0;
	virtual void				GetMatrix(void* matrixMode, VMatrix *matrix) = 0;
	virtual void				GetMatrix(void* matrixMode, matrix3x4_t *matrix) = 0;
	virtual void				LoadIdentity(void) = 0;
	virtual void				Ortho(double left, double top, double right, double bottom, double zNear, double zFar) = 0;
	virtual void				PerspectiveX(double fovx, double aspect, double zNear, double zFar) = 0;
	virtual void				PickMatrix(int x, int y, int width, int height) = 0;
	virtual void				Rotate(float angle, float x, float y, float z) = 0;
	virtual void				Translate(float x, float y, float z) = 0;
	virtual void				Scale(float x, float y, float z) = 0;
	// end matrix api

	// Sets/gets the viewport
	virtual void				Viewport(int x, int y, int width, int height) = 0;
	virtual void				GetViewport(int& x, int& y, int& width, int& height) const = 0;

	// The cull mode
	virtual void				CullMode(void* cullMode) = 0;
	virtual void				FlipCullMode() = 0;
	// end matrix api

	virtual void				BeginGeneratingCSMs() = 0;
	virtual void				EndGeneratingCSMs() = 0;
	virtual void				PerpareForCascadeDraw(int, float, float) = 0;

	// This could easily be extended to a general user clip plane
	virtual void				SetHeightClipMode(void* nHeightClipMode) = 0;
	// garymcthack : fog z is always used for heightclipz for now.
	virtual void				SetHeightClipZ(float z) = 0;

	// Fog methods...
	virtual void				FogMode(void* fogMode) = 0;
	virtual void				FogStart(float fStart) = 0;
	virtual void				FogEnd(float fEnd) = 0;
	virtual void				SetFogZ(float fogZ) = 0;
	virtual void*	GetFogMode(void) = 0;

	virtual void				FogColor3f(float r, float g, float b) = 0;
	virtual void				FogColor3fv(float const* rgb) = 0;
	virtual void				FogColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void				FogColor3ubv(unsigned char const* rgb) = 0;

	virtual void				GetFogColor(unsigned char *rgb) = 0;

	// Sets the number of bones for skinning
	virtual void				SetNumBoneWeights(int numBones) = 0;

	// Creates/destroys Mesh
	virtual void* CreateStaticMesh(void* fmt, const char *pTextureBudgetGroup, void * pMaterial = nullptr) = 0;
	virtual void DestroyStaticMesh(void* mesh) = 0;

	// Gets the dynamic mesh associated with the currently bound material
	// note that you've got to render the mesh before calling this function 
	// a second time. Clients should *not* call DestroyStaticMesh on the mesh 
	// returned by this call.
	// Use buffered = false if you want to not have the mesh be buffered,
	// but use it instead in the following pattern:
	//		meshBuilder.Begin
	//		meshBuilder.End
	//		Draw partial
	//		Draw partial
	//		Draw partial
	//		meshBuilder.Begin
	//		meshBuilder.End
	//		etc
	// Use Vertex or Index Override to supply a static vertex or index buffer
	// to use in place of the dynamic buffers.
	//
	// If you pass in a material in pAutoBind, it will automatically bind the
	// material. This can be helpful since you must bind the material you're
	// going to use BEFORE calling GetDynamicMesh.
	virtual void* GetDynamicMesh(
		bool buffered = true,
		void** pVertexOverride = nullptr,
		void** pIndexOverride = nullptr,
		void *pAutoBind = nullptr) = 0;

	// ------------ New Vertex/Index Buffer interface ----------------------------
	// Do we need support for bForceTempMesh and bSoftwareVertexShader?
	// I don't think we use bSoftwareVertexShader anymore. .need to look into bForceTempMesh.
	virtual void* *CreateStaticVertexBuffer(int fmt, int nVertexCount, const char *pTextureBudgetGroup) = 0;
	virtual void* *CreateStaticIndexBuffer(void* fmt, int nIndexCount, const char *pTextureBudgetGroup) = 0;
	virtual void DestroyVertexBuffer(void* *) = 0;
	virtual void DestroyIndexBuffer(void* *) = 0;
	// Do we need to specify the stream here in the case of locking multiple dynamic VBs on different streams?
	virtual void* *GetDynamicVertexBuffer(int streamID, int vertexFormat, bool bBuffered = true) = 0;
	virtual void* *GetDynamicIndexBuffer(void* fmt, bool bBuffered = true) = 0;
	virtual void BindVertexBuffer(int streamID, void* *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, int fmt, int nRepetitions = 1) = 0;
	virtual void BindIndexBuffer(void* *pIndexBuffer, int nOffsetInBytes) = 0;
	virtual void Draw(void* primitiveType, int firstIndex, int numIndices) = 0;
	// ------------ End ----------------------------

	// Selection mode methods
	virtual int  SelectionMode(bool selectionMode) = 0;
	virtual void SelectionBuffer(unsigned int* pBuffer, int size) = 0;
	virtual void ClearSelectionNames() = 0;
	virtual void LoadSelectionName(int name) = 0;
	virtual void PushSelectionName(int name) = 0;
	virtual void PopSelectionName() = 0;

	// Sets the Clear Color for ClearBuffer....
	virtual void		ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void		ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;

	// Allows us to override the depth buffer setting of a material
	virtual void	OverrideDepthEnable(bool bEnable, bool bDepthEnable) = 0;

	// FIXME: This is a hack required for NVidia/XBox, can they fix in drivers?
	virtual void	DrawScreenSpaceQuad(void* pMaterial) = 0;

	// For debugging and building recording files. This will stuff a token into the recording file,
	// then someone doing a playback can watch for the token.
	virtual void	SyncToken(const char *pToken) = 0;

	// FIXME: REMOVE THIS FUNCTION!
	// The only reason why it's not gone is because we're a week from ship when I found the bug in it
	// and everything's tuned to use it.
	// It's returning values which are 2x too big (it's returning sphere diameter x2)
	// Use ComputePixelDiameterOfSphere below in all new code instead.
	virtual float	ComputePixelWidthOfSphere(const void*& origin, float flRadius) = 0;

	//
	// Occlusion query support
	//

	// Allocate and delete query objects.
	virtual void* CreateOcclusionQueryObject(void) = 0;
	virtual void DestroyOcclusionQueryObject(void*) = 0;

	// Bracket drawing with begin and end so that we can get counts next frame.
	virtual void BeginOcclusionQueryDrawing(void*) = 0;
	virtual void EndOcclusionQueryDrawing(void*) = 0;

	// Get the number of pixels rendered between begin and end on an earlier frame.
	// Calling this in the same frame is a huge perf hit!
	virtual int OcclusionQuery_GetNumPixelsRendered(void*) = 0;

	virtual void SetFlashlightMode(bool bEnable) = 0;

	virtual void SetFlashlightState(const void* &state, const VMatrix &worldToTexture) = 0;

	virtual bool IsCascadedShadowMapping() = 0;
	virtual void SetCascadedShadowMapping(bool) = 0;
	virtual void SetCascadedShadowMappingState(/*CascadedShadowMappingState_t*/ int const&, void *) = 0;

	// Gets the current height clip mode
	virtual void* GetHeightClipMode() = 0;

	// This returns the diameter of the sphere in pixels based on 
	// the current model, view, + projection matrices and viewport.
	virtual float	ComputePixelDiameterOfSphere(const void*& vecAbsOrigin, float flRadius) = 0;

	// By default, the material system applies the VIEW and PROJECTION matrices	to the user clip
	// planes (which are specified in world space) to generate projection-space user clip planes
	// Occasionally (for the particle system in hl2, for example), we want to override that
	// behavior and explictly specify a ViewProj transform for user clip planes
	virtual void	EnableUserClipTransformOverride(bool bEnable) = 0;
	virtual void	UserClipTransform(const VMatrix &worldToView) = 0;

	virtual bool GetFlashlightMode() const = 0;

	virtual bool IsCullingEnabledForSinglePassFlashlight() = 0;
	virtual void EnableCullingForSinglePassFlashlight(bool) = 0;
	// Used to make the handle think it's never had a successful query before
	virtual void ResetOcclusionQueryObject(void*) = 0;

	// Creates/destroys morph data associated w/ a particular material
	virtual void* *CreateMorph(void* format, const char *pDebugName) = 0;
	virtual void DestroyMorph(void* *pMorph) = 0;

	// Binds the morph data for use in rendering
	virtual void BindMorph(void* *pMorph) = 0;

	// Sets flexweights for rendering
	virtual void SetFlexWeights(int nFirstWeight, int nCount, const void** pWeights) = 0;

	virtual void LockRenderData(int) = 0;
	virtual void UnlockRenderData() = 0;
	virtual void AddRefRenderData() = 0;
	virtual void ReleaseRenderData() = 0;
	virtual void IsRenderData(void const*) = 0;

	// Read w/ stretch to a host-memory buffer
	virtual void ReadPixelsAndStretch(void* *pSrcRect, void* *pDstRect, unsigned char *pBuffer, ImageFormat dstFormat, int nDstStride) = 0;

	// Gets the window size
	virtual void GetWindowSize(int &width, int &height) const = 0;

	// This function performs a texture map from one texture map to the render destination, doing
	// all the necessary pixel/texel coordinate fix ups. fractional values can be used for the
	// src_texture coordinates to get linear sampling - integer values should produce 1:1 mappings
	// for non-scaled operations.
	virtual void DrawScreenSpaceRectangle(
		void *pMaterial, //imaterial
		int destx, int desty,
		int width, int height,
		float src_texture_x0, float src_texture_y0,			// which texel you want to appear at
															// destx/y
		float src_texture_x1, float src_texture_y1,			// which texel you want to appear at
															// destx+width-1, desty+height-1
		int src_texture_width, int src_texture_height,		// needed for fixup
		void *pClientRenderable = nullptr,
		int nXDice = 1,
		int nYDice = 1) = 0;

	virtual void LoadBoneMatrix(int boneIndex, const matrix3x4_t& matrix) = 0;

	// This version will push the current rendertarget + current viewport onto the stack
	virtual void PushRenderTargetAndViewport() = 0;

	// This version will push a new rendertarget + a maximal viewport for that rendertarget onto the stack
	virtual void PushRenderTargetAndViewport(void *pTexture) = 0;

	// This version will push a new rendertarget + a specified viewport onto the stack
	virtual void PushRenderTargetAndViewport(void *pTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;

	// This version will push a new rendertarget + a specified viewport onto the stack
	virtual void PushRenderTargetAndViewport(void *pTexture, void *pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH) = 0;

	// This will pop a rendertarget + viewport
	virtual void PopRenderTargetAndViewport() = 0;

	// Binds a particular texture as the current lightmap
	virtual void BindLightmapTexture(void *pLightmapTexture) = 0;

	// Blit a subrect of the current render target to another texture
	virtual void CopyRenderTargetToTextureEx(void *pTexture, int nRenderTargetID, void* *pSrcRect, void* *pDstRect = nullptr) = 0;
	virtual void CopyRenderTargetToTextureExCopyTextureToRenderTargetEx(int, void *, void* *, void* *) = 0;
	// Special off-center perspective matrix for DoF, MSAA jitter and poster rendering
	virtual void PerspectiveOffCenterX(double fovx, double aspect, double zNear, double zFar, double bottom, double top, double left, double right) = 0;

	// Rendering parameters control special drawing modes withing the material system, shader
	// system, shaders, and engine. renderparm.h has their definitions.
	virtual void SetFloatRenderingParameter(int parm_number, float value) = 0;
	virtual void SetIntRenderingParameter(int parm_number, int value) = 0;
	virtual void SetVectorRenderingParameter(int parm_number, void* const &value) = 0;

	// stencil buffer operations.
	virtual void SetStencilState(ShaderStencilState_t  const&) = 0;
	//virtual void SetStencilEnable(bool onoff) = 0;
	//virtual void SetStencilFailOperation(StencilOperation_t op) = 0;
	//virtual void SetStencilZFailOperation(StencilOperation_t op) = 0;
	//virtual void SetStencilPassOperation(StencilOperation_t op) = 0;
	//virtual void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) = 0;
	//virtual void SetStencilReferenceValue(int ref) = 0;
	//virtual void SetStencilTestMask(uint32 msk) = 0;
	//virtual void SetStencilWriteMask(uint32 msk) = 0;
	virtual void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) = 0;

	virtual void SetRenderTargetEx(int nRenderTargetID, void *pTexture) = 0;

	// rendering clip planes, beware that only the most recently pushed plane will actually be used in a sizeable chunk of hardware configurations
	// and that changes to the clip planes mid-frame while UsingFastClipping() is true will result unresolvable depth inconsistencies
	virtual void PushCustomClipPlane(const float *pPlane) = 0;
	virtual void PopCustomClipPlane() = 0;

	// Returns the number of vertices + indices we can render using the dynamic mesh
	// Passing true in the second parameter will return the max # of vertices + indices
	// we can use before a flush is provoked and may return different values 
	// if called multiple times in succession. 
	// Passing false into the second parameter will return
	// the maximum possible vertices + indices that can be rendered in a single batch
	virtual void GetMaxToRender(void* *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices) = 0;

	// Returns the max possible vertices + indices to render in a single draw call
	virtual int GetMaxVerticesToRender(void *pMaterial) = 0;
	virtual int GetMaxIndicesToRender() = 0;
	virtual void DisableAllLocalLights() = 0;
	virtual int CompareMaterialCombos(void *pMaterial1, void *pMaterial2, int lightMapID1, int lightMapID2) = 0;

	virtual void* *GetFlexMesh() = 0;

	virtual void SetFlashlightStateEx(const void* &state, const VMatrix &worldToTexture, void *pFlashlightDepthTexture) = 0;

	// Returns the currently bound local cubemap
	virtual int *GetLocalCubemap() = 0;

	// This is a version of clear buffers which will only clear the buffer at pixels which pass the stencil test
	virtual void ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) = 0;

	//enables/disables all entered clipping planes, returns the input from the last time it was called.
	virtual bool EnableClipping(bool bEnable) = 0;

	//get fog distances entered with FogStart(), FogEnd(), and SetFogZ()
	virtual void GetFogDistances(float *fStart, float *fEnd, float *fFogZ) = 0;

	// Hooks for firing PIX events from outside the Material System...
	virtual void BeginPIXEvent(unsigned long color, const char *szName) = 0;
	virtual void EndPIXEvent() = 0;
	virtual void SetPIXMarker(unsigned long color, const char *szName) = 0;

	// Batch API
	// from changelist 166623:
	// - replaced obtuse material system batch usage with an explicit and easier to thread API
	virtual void BeginBatch(void** pIndices) = 0;
	virtual void BindBatch(void** pVertices, void *pAutoBind = nullptr) = 0;
	virtual void DrawBatch(int firstIndex, int numIndices) = 0;
	virtual void EndBatch() = 0;

	// Raw access to the call queue, which can be NULL if not in a queued mode
	virtual void* *GetCallQueue() = 0;

	// Returns the world-space camera position
	virtual void GetWorldSpaceCameraPosition(void* *pCameraPos) = 0;
	virtual void GetWorldSpaceCameraVectors(void* *pVecForward, void* *pVecRight, void* *pVecUp) = 0;

	// Tone mapping
	//virtual void				ResetToneMappingScale(float monoscale) = 0; 			// set scale to monoscale instantly with no chasing
	//virtual void				SetGoalToneMappingScale(float monoscale) = 0; 			// set scale to monoscale instantly with no chasing

	// call TurnOnToneMapping before drawing the 3d scene to get the proper interpolated brightness
	// value set.
	//virtual void				TurnOnToneMapping() = 0;

	// Set a linear vector color scale for all 3D rendering.
	// A value of [1.0f, 1.0f, 1.0f] should match non-tone-mapped rendering.
	virtual void				SetToneMappingScaleLinear(const void* &scale) = 0;

	virtual void*				GetToneMappingScaleLinear() = 0;
	virtual void				SetShadowDepthBiasFactors(float fSlopeScaleDepthBias, float fDepthBias) = 0;

	// Apply stencil operations to every pixel on the screen without disturbing depth or color buffers
	virtual void				PerformFullScreenStencilOperation(void) = 0;

	// Sets lighting origin for the current model (needed to convert directional lights to points)
	virtual void				SetLightingOrigin(void* vLightingOrigin) = 0;

	// Set scissor rect for rendering
	virtual void				PushScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom) = 0;
	virtual void				PopScissorRect() = 0;

	// Methods used to build the morph accumulator that is read from when HW morph<ing is enabled.
	virtual void				BeginMorphAccumulation() = 0;
	virtual void				EndMorphAccumulation() = 0;
	virtual void				AccumulateMorph(void** pMorph, int nMorphCount, const void** pWeights) = 0;

	virtual void				PushDeformation(void* const *Deformation) = 0;
	virtual void				PopDeformation() = 0;
	virtual int					GetNumActiveDeformations() const = 0;

	virtual bool				GetMorphAccumulatorTexCoord(Vector2D *pTexCoord, void* *pMorph, int nVertex) = 0;

	// Version of get dynamic mesh that specifies a specific vertex format
	virtual void**				GetDynamicMeshEx(void* vertexFormat, bool bBuffered = true,
		void** pVertexOverride = nullptr, void** pIndexOverride = nullptr, void *pAutoBind = nullptr) = 0;

	virtual void				FogMaxDensity(float flMaxDensity) = 0;

	virtual void *GetCurrentMaterial() = 0;
	virtual int  GetCurrentNumBones() const = 0;
	virtual void *GetCurrentProxy() = 0;

	// Color correction related methods..
	// Client cannot call IColorCorrectionSystem directly because it is not thread-safe
	// FIXME: Make IColorCorrectionSystem threadsafe?
	virtual void EnableColorCorrection(bool bEnable) = 0;
	virtual void* AddLookup(const char *pName) = 0;
	virtual bool RemoveLookup(void* handle) = 0;
	virtual void LockLookup(void* handle) = 0;
	virtual void LoadLookup(void* handle, const char *pLookupName) = 0;
	virtual void UnlockLookup(void* handle) = 0;
	virtual void SetLookupWeight(void* handle, float flWeight) = 0;
	virtual void ResetLookupWeights() = 0;
	virtual void SetResetable(void* handle, bool bResetable) = 0;

	//There are some cases where it's simply not reasonable to update the full screen depth texture (mostly on PC).
	//Use this to mark it as invalid and use a dummy texture for depth reads.
	virtual void SetFullScreenDepthTextureValidityFlag(bool bIsValid) = 0;

	// A special path used to tick the front buffer while loading on the 360
	virtual void SetNonInteractivePacifierTexture(void *pTexture, float flNormalizedX, float flNormalizedY, float flNormalizedSize) = 0;
	virtual void SetNonInteractiveTempFullscreenBuffer(void *pTexture, void* mode) = 0;
	virtual void EnableNonInteractiveMode(void* mode) = 0;
	virtual void RefreshFrontBufferNonInteractive() = 0;
};
class ITexture;
//-----------------------------------------------------------------------------
// This will get called on procedural textures to re-fill the textures
// with the appropriate bit pattern. Calling Download() will also
// cause this interface to be called. It will also be called upon
// mode switch, or on other occasions where the bits are discarded.
//-----------------------------------------------------------------------------
class ITextureRegenerator
{
public:
	// This will be called when the texture bits need to be regenerated.
	// Use the VTFTexture interface, which has been set up with the
	// appropriate texture size + format
	// The rect specifies which part of the texture needs to be updated
	// You can choose to update all of the bits if you prefer
	virtual void RegenerateTextureBits(ITexture *pTexture, void *pVTFTexture, void *pRect) = 0;

	// This will be called when the regenerator needs to be deleted
	// which will happen when the texture is destroyed
	virtual void Release() = 0;

	// (erics): This should have a virtual destructor, but would be ABI breaking (non-versioned interface implemented
	//          by the game)
	//	virtual ~ITextureRegenerator(){}
};
enum NormalDecodeMode_t
{
	NORMAL_DECODE_NONE = 0,
	NORMAL_DECODE_ATI2N = 1,
	NORMAL_DECODE_ATI2N_ALPHA = 2
};
class ITexture
{
public:
	// Various texture polling methods
	virtual const char *GetName(void) const = 0;
	virtual int GetMappingWidth() const = 0;
	virtual int GetMappingHeight() const = 0;
	virtual int GetActualWidth() const = 0;
	virtual int GetActualHeight() const = 0;
	virtual int GetNumAnimationFrames() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsMipmapped() const = 0;

	virtual void GetLowResColorSample(float s, float t, float *color) const = 0;

	// Gets texture resource data of the specified type.
	// Params:
	//		eDataType		type of resource to retrieve.
	//		pnumBytes		on return is the number of bytes available in the read-only data buffer or is undefined
	// Returns:
	//		pointer to the resource data, or NULL
	virtual void *GetResourceData(uint32 eDataType, size_t *pNumBytes) const = 0;

	// Methods associated with reference count
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	// Used to modify the texture bits (procedural textures only)
	virtual void SetTextureRegenerator(ITextureRegenerator *pTextureRegen) = 0;

	// Reconstruct the texture bits in HW memory

	// If rect is not specified, reconstruct all bits, otherwise just
	// reconstruct a subrect.
	virtual void Download(void *pRect = 0, int nAdditionalCreationFlags = 0) = 0;

	// Uses for stats. . .get the approximate size of the texture in it's current format.
	virtual int GetApproximateVidMemBytes(void) const = 0;

	// Returns true if the texture data couldn't be loaded.
	virtual bool IsError() const = 0;

	// NOTE: Stuff after this is added after shipping HL2.

	// For volume textures
	virtual bool IsVolumeTexture() const = 0;
	virtual int GetMappingDepth() const = 0;
	virtual int GetActualDepth() const = 0;

	virtual ImageFormat GetImageFormat() const = 0;
	virtual NormalDecodeMode_t GetNormalDecodeMode() const = 0;

	// Various information about the texture
	virtual bool IsRenderTarget() const = 0;
	virtual bool IsCubeMap() const = 0;
	virtual bool IsNormalMap() const = 0;
	virtual bool IsProcedural() const = 0;

	virtual void DeleteIfUnreferenced() = 0;

#if defined( _X360 )
	virtual bool ClearTexture(int r, int g, int b, int a) = 0;
	virtual bool CreateRenderTargetSurface(int width, int height, ImageFormat format, bool bSameAsTexture) = 0;
#endif

	// swap everything except the name with another texture
	virtual void SwapContents(ITexture *pOther) = 0;

	// Retrieve the vtf flags mask
	virtual unsigned int GetFlags(void) const = 0;

	// Force LOD override (automatically downloads the texture)
	virtual void ForceLODOverride(int iNumLodsOverrideUpOrDown) = 0;

	// Save texture to a file.
	virtual bool SaveToFile(const char *fileName) = 0;

	// Copy this texture, which must be a render target or a renderable texture, to the destination texture, 
	// which must have been created with the STAGING bit.
	virtual void CopyToStagingTexture(ITexture* pDstTex) = 0;

	// Set that this texture should return true for the call "IsError"
	virtual void SetErrorTexture(bool bIsErrorTexture) = 0;
};


inline bool IsErrorTexture(ITexture *pTex)
{
	return !pTex || pTex->IsError();
}
