#include "sdk.h"


void *KeyValues::operator new(size_t iAllocSize)
{
	static PVOID pKeyValuesSystem;
	if (!pKeyValuesSystem)
	{
		typedef PVOID(__cdecl* oKeyValuesSystem)();
		oKeyValuesSystem KeyValuesSystem = (oKeyValuesSystem)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "KeyValuesSystem");

		pKeyValuesSystem = KeyValuesSystem();
	}

	typedef PVOID(__thiscall* oAllocKeyValuesMemory)(PVOID, size_t);
	return U::GetVFunc<oAllocKeyValuesMemory>(pKeyValuesSystem, 1)(pKeyValuesSystem, iAllocSize);
}

void KeyValues::operator delete(void * pMem)
{
	static PVOID pKeyValuesSystem;
	if (!pKeyValuesSystem)
	{
		typedef PVOID(__cdecl* oKeyValuesSystem)();
		oKeyValuesSystem KeyValuesSystem = (oKeyValuesSystem)GetProcAddress(GetModuleHandleA("vstdlib.dll"), "KeyValuesSystem");

		pKeyValuesSystem = KeyValuesSystem();
	}

	typedef void(__thiscall* oFreeKeyValuesMemory)(PVOID, PVOID);
	U::GetVFunc<oFreeKeyValuesMemory>(pKeyValuesSystem, 2)(pKeyValuesSystem, pMem);
}

KeyValues* KeyValues::FindKey(const char *keyName, bool bCreate)
{
	static auto key_values_find_key = reinterpret_cast<KeyValues*(__thiscall*)(void*, const char*, bool)>(U::FindPattern("client.dll", "55 8B EC 83 EC 1C 53 8B D9 85 DB"));
	return key_values_find_key(this, keyName, bCreate);
}

void KeyValues::SetString(const char* keyName, const char* value)
{
	auto key = FindKey(keyName, true);
	if (key)
	{
		static auto key_values_set_string = reinterpret_cast<void(__thiscall*)(void*, const char*)>(U::FindPattern("client.dll", "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01"));
		key_values_set_string(key, value);
	}
}
void KeyValues::SetInt(const char *keyName, int Value)
{
	auto key_int = FindKey(keyName, true);
	if (key_int)
	{
		*reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(key_int) + 0xC) = Value;
		*reinterpret_cast<char*>(reinterpret_cast<uintptr_t>(key_int) + 0x10) = 2;
	}
}

// How many bits to use to encode an edict.
#define	MAX_EDICT_BITS				11			// # of bits needed to represent max edicts
// Max # of edicts in a level
#define	MAX_EDICTS					(1<<MAX_EDICT_BITS)

// How many bits to use to encode an server class index
#define MAX_SERVER_CLASS_BITS		9
// Max # of networkable server classes
#define MAX_SERVER_CLASSES			(1<<MAX_SERVER_CLASS_BITS)

#define SIGNED_GUID_LEN 32 // Hashed CD Key (32 hex alphabetic chars + 0 terminator )

// Used for networking ehandles.
#define NUM_ENT_ENTRY_BITS		(MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES			(1 << NUM_ENT_ENTRY_BITS)
#define INVALID_EHANDLE_INDEX	0xFFFFFFFF

#define NUM_SERIAL_NUM_BITS		16 // (32 - NUM_ENT_ENTRY_BITS)
#define NUM_SERIAL_NUM_SHIFT_BITS (32 - NUM_SERIAL_NUM_BITS)
#define ENT_ENTRY_MASK			(( 1 << NUM_SERIAL_NUM_BITS) - 1)


// Networked ehandles use less bits to encode the serial number.
#define NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS	10
#define NUM_NETWORKED_EHANDLE_BITS					(MAX_EDICT_BITS + NUM_NETWORKED_EHANDLE_SERIAL_NUMBER_BITS)
#define INVALID_NETWORKED_EHANDLE_VALUE				((1 << NUM_NETWORKED_EHANDLE_BITS) - 1)



inline CBaseHandle::CBaseHandle() {
	m_Index = INVALID_EHANDLE_INDEX;
}

//inline CBaseHandle::CBaseHandle(const CBaseHandle &other) {
//	m_Index = other.m_Index;
//}

inline CBaseHandle::CBaseHandle(unsigned long value) {
	m_Index = value;
}

inline CBaseHandle::CBaseHandle(int iEntry, int iSerialNumber) {
	Init(iEntry, iSerialNumber);
}

inline void CBaseHandle::Init(int iEntry, int iSerialNumber) {
	Assert(iEntry >= 0 && iEntry < NUM_ENT_ENTRIES);
	Assert(iSerialNumber >= 0 && iSerialNumber < (1 << NUM_SERIAL_NUM_BITS));

	m_Index = iEntry | (iSerialNumber << NUM_ENT_ENTRY_BITS);
}

inline void CBaseHandle::Term() {
	m_Index = INVALID_EHANDLE_INDEX;
}

inline bool CBaseHandle::IsValid() const {
	return m_Index != INVALID_EHANDLE_INDEX;
}

inline int CBaseHandle::GetEntryIndex() const {
	return m_Index & ENT_ENTRY_MASK;
}

inline int CBaseHandle::GetSerialNumber() const {
	return m_Index >> NUM_ENT_ENTRY_BITS;
}

inline int CBaseHandle::ToInt() const {
	return (int)m_Index;
}

inline bool CBaseHandle::operator !=(const CBaseHandle &other) const {
	return m_Index != other.m_Index;
}

inline bool CBaseHandle::operator ==(const CBaseHandle &other) const {
	return m_Index == other.m_Index;
}

inline bool CBaseHandle::operator ==(const IHandleEntity* pEnt) const {
	return Get() == pEnt;
}

inline bool CBaseHandle::operator !=(const IHandleEntity* pEnt) const {
	return Get() != pEnt;
}

inline bool CBaseHandle::operator <(const CBaseHandle &other) const {
	return m_Index < other.m_Index;
}

inline bool CBaseHandle::operator <(const IHandleEntity *pEntity) const {
	unsigned long otherIndex =  (pEntity) ? pEntity->GetRefEHandle().m_Index : INVALID_EHANDLE_INDEX;
	return m_Index < otherIndex;
}

inline const CBaseHandle& CBaseHandle::operator=(const IHandleEntity *pEntity) {
	return Set(pEntity);
}

inline const CBaseHandle& CBaseHandle::Set(const IHandleEntity *pEntity) {
	if (pEntity) {
		*this =  pEntity->GetRefEHandle();
	}
	else {
		m_Index = INVALID_EHANDLE_INDEX;
	}

	return *this;
}

IHandleEntity* CBaseHandle::Get() const 
{ return i::ClientEntList->GetClientEntityFromHandle(m_Index & 0xFFF); };

inline int CBaseEntityList::GetEntInfoIndex(const CEntInfo *pEntInfo) const {
	Assert(pEntInfo);
	int index = (int)(pEntInfo - m_EntPtrArray);
	Assert(index >= 0 && index < NUM_ENT_ENTRIES);
	return index;
}

inline CBaseHandle CBaseEntityList::GetNetworkableHandle(int iEntity) const {
	Assert(iEntity >= 0 && iEntity < MAX_EDICTS);
	if (m_EntPtrArray[iEntity].m_pEntity)
		return CBaseHandle(iEntity, m_EntPtrArray[iEntity].m_SerialNumber);
	else
		return CBaseHandle();
}


inline IHandleEntity* CBaseEntityList::LookupEntity(const CBaseHandle &handle) const {
	if (handle.m_Index == INVALID_EHANDLE_INDEX)
		return NULL;

	const CEntInfo *pInfo = &m_EntPtrArray[handle.GetEntryIndex()];
	if (pInfo->m_SerialNumber == handle.GetSerialNumber())
		return (IHandleEntity*)pInfo->m_pEntity;
	else
		return NULL;
}


inline IHandleEntity* CBaseEntityList::LookupEntityByNetworkIndex(int edictIndex) const {
	// (Legacy support).
	if (edictIndex < 0)
		return NULL;

	Assert(edictIndex < NUM_ENT_ENTRIES);
	return (IHandleEntity*)m_EntPtrArray[edictIndex].m_pEntity;
}


inline CBaseHandle CBaseEntityList::FirstHandle() const {
	if (!m_activeList.Head())
		return INVALID_EHANDLE_INDEX;

	int index = GetEntInfoIndex(m_activeList.Head());
	return CBaseHandle(index, m_EntPtrArray[index].m_SerialNumber);
}

inline CBaseHandle CBaseEntityList::NextHandle(CBaseHandle hEnt) const {
	int iSlot = hEnt.GetEntryIndex();
	CEntInfo *pNext = m_EntPtrArray[iSlot].m_pNext;
	if (!pNext)
		return INVALID_EHANDLE_INDEX;

	int index = GetEntInfoIndex(pNext);

	return CBaseHandle(index, m_EntPtrArray[index].m_SerialNumber);
}

inline CBaseHandle CBaseEntityList::InvalidHandle() {
	return INVALID_EHANDLE_INDEX;
}

inline const CEntInfo *CBaseEntityList::FirstEntInfo() const {
	return m_activeList.Head();
}

inline const CEntInfo *CBaseEntityList::NextEntInfo(const CEntInfo *pInfo) const {
	return pInfo->m_pNext;
}

inline const CEntInfo *CBaseEntityList::GetEntInfoPtr(const CBaseHandle &hEnt) const {
	int iSlot = hEnt.GetEntryIndex();
	return &m_EntPtrArray[iSlot];
}

inline const CEntInfo *CBaseEntityList::GetEntInfoPtrByIndex(int index) const {
	return &m_EntPtrArray[index];
}

/*
bool StandardFilterRules(IHandleEntity* pHandleEntity, int fContentsMask, int collisionGroup) {
	CBaseEntity* pCollide = dynamic_cast<CBaseEntity*>(pHandleEntity);

	if (!pCollide)
		return true;

	const SolidType_t solid = (SolidType_t)pCollide->GetSolid();
	const model_t* pModel = pCollide->get_model();
	auto mod = i::ModelInfo->GetModelType(pModel);

	if ((mod != mod_brush) || (solid != SOLID_BSP && solid != SOLID_VPHYSICS)) {
		if ((fContentsMask & CONTENTS_MONSTER) == 0)
			return false;
	}

	if (!(fContentsMask & CONTENTS_WINDOW) && pCollide->IsTransparent())
		return false;

	if (!(fContentsMask & CONTENTS_MOVEABLE) && (pCollide->get_movetype() == MOVETYPE_PUSH))// !(touch->flags & FL_WORLDBRUSH) )
		return false;

	return true;
}

bool PassServerEntityFilter(const IHandleEntity *pTouch, const IHandleEntity *pPass) {
	if (!pPass)
		return true;

	if (pTouch == pPass)
		return false;

	CBaseEntity *pEntTouch = (CBaseEntity*)pTouch;
	CBaseEntity *pEntPass = (CBaseEntity*)pPass;
	if (!pEntTouch || !pEntPass)
		return true;

	if (pEntTouch->GetOwnerEntity() == pEntPass)
		return false;

	if (pEntPass->GetOwnerEntity() == pEntTouch)
		return false;

	return true;
}

IGameRules*				GameRules;
bool GameRulesShouldCollide(int collisionGroup0, int collisionGroup1) {
	static bool once = true;
	if (once)
	{
		GameRules = *(IGameRules**)(U::FindPattern("client.dll", "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 0F 84 ? ? ? ? 0F 10 05") + 1);
		once = false;
	}
	//IGameRules*				GameRules;
	uintptr_t shouldcollide = reinterpret_cast<uintptr_t>(GameRules);
	__asm {
		push collisionGroup1
		push collisionGroup0
		mov ecx, shouldcollide
		mov ecx, [ecx]
		mov eax, [ecx]
		mov eax, [eax + 0x70]
		call eax
	}
}

bool BaseShouldHitEntity(IHandleEntity* pSkip, IHandleEntity* pHandleEntity, int m_collisionGroup, int contentsMask) {
	if (!StandardFilterRules(pHandleEntity, contentsMask, m_collisionGroup))
		return false;

	if (pSkip) {
		if (!PassServerEntityFilter(pHandleEntity, pSkip)) {
			return false;
		}
	}

	CBaseEntity* pEntity = dynamic_cast<CBaseEntity*>(pHandleEntity);//EntityFromEntityHandle(pHandleEntity);
	if (!pEntity)
		return false;
	if (!pEntity->ShouldCollide(m_collisionGroup, contentsMask))
		return false;
	if (!GameRulesShouldCollide(m_collisionGroup, pEntity->GetCollisionGroup()))
		return false;

	return true;
}
*/