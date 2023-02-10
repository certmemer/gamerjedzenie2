#pragma once



class IMaterialSystem
{
public:
	IMaterial * CreateMaterial(bool flat, bool ignorez, bool wireframed, int color);
	IMaterial* CreateMaterial2(const char* pMaterialNamez, KeyValues* pVMTKeyValuesz);

	IMaterial* FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL);
	ITexture * FindTexture(char const* pTextureName, const char *pTextureGroupNamed, bool complaind = true, int nAdditionalCreationFlags = 0);
	MaterialHandle_t FirstMaterial();
	MaterialHandle_t NextMaterial(MaterialHandle_t h);
	MaterialHandle_t InvalidMaterial();
	IMaterial* GetMaterial(MaterialHandle_t h);
	IMatRenderContext* GetRenderContext();
};

class IMaterialVar {
public:
	ITexture * GetTextureValue()
	{
		typedef ITexture*(__thiscall* OriginalFn)(void*);
		return U::GetVFunc<OriginalFn>(this, 1)(this);
	};
	void SetFloatValue(float a)
	{
		typedef void(__thiscall* OriginalFn)(void*, float);
		return U::GetVFunc<OriginalFn>(this, 4)(this, a);
	};
	void SetIntValue(int a)
	{
		typedef void(__thiscall* OriginalFn)(void*, int);
		return U::GetVFunc<OriginalFn>(this, 5)(this, a);
	};
	void SetStringValue(char const* a)
	{
		typedef void(__thiscall* OriginalFn)(void*, char const*);
		return U::GetVFunc<OriginalFn>(this, 6)(this, a);
	};
	void SetVecValue(float a, float b, float c)
	{
		typedef void(__thiscall* OriginalFn)(void*, float, float, float);
		return U::GetVFunc<OriginalFn>(this, 11)(this, a, b, c);
	};
	void SetTextureValue(ITexture* aaa)
	{
		typedef void(__thiscall* OriginalFn)(void*, ITexture* aaa);
		return U::GetVFunc<OriginalFn>(this, 15)(this, aaa);
	};
};