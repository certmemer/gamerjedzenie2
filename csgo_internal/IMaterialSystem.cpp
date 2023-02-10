#include "SDK.h"

int created = 0;

void InitKeyValues(KeyValues* pKeyValues, const char* name)
{
	using InitKeyValuesFn = void(__thiscall*)(void* thisptr, const char* name);
	auto kek = (InitKeyValuesFn)(offsets.InitKeyValuesEx);
	kek(pKeyValues, name);
}

void LoadFromBuffer(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem = nullptr, const char* pPathID = nullptr, void* pfnEvaluateSymbolProc = nullptr)
{
	using LoadFromBufferFn = void(__thiscall*)(void* thisptr, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc);
	auto kek = (LoadFromBufferFn)(offsets.LoadFromBufferEx);
	kek(pKeyValues, resourceName, pBuffer, pFileSystem, pPathID, pfnEvaluateSymbolProc);
}


/*IMaterial* IMaterialSystem::CreateMaterial(bool flat, bool ignorez, bool wireframed, int color)
{
static const char tmp[] =
{
"\"VertexLitGeneric\"\
\n{\
\n\t\"$basetexture\" \"vgui/white_additive\"\
\n\t\"$envmap\" \"\"\
\n\t\"$color2\" \"[ %f %f %f ]\"\
\n\t\"$model\" \"1\"\
\n\t\"$flat\" \"1\"\
\n\t\"$nocull\" \"0\"\
\n\t\"$selfillum\" \"1\"\
\n\t\"$halflambert\" \"1\"\
\n\t\"$nofog\" \"1\"\
\n\t\"$znearer\" \"0\"\
\n\t\"$ignorez\" \"%i\"\
\n\t\"$wireframe\" \"%i\"\
\n}\n"
};

float r, g, b;

/*if (color == 1) //xqz
{
r = 0.2823f;
g = 0.0627f;
b = 0.276f;
}
else if (color == 2) //vis
{
r = 0.212f;
g = 0.69f;
b = 0.094f;
}

else if (color == 0)
{*//*
r = 1.f;
g = 1.f;
b = 1.f;
//}

char material[512];
sprintf_s(material, sizeof(material), tmp, r, g, b, (ignorez) ? 1 : 0, (wireframed) ? 1 : 0);

std::string matname = strenc("mat") + std::to_string(created);
++created;

KeyValues* pKeyValues = new KeyValues(matname.c_str()); //!!! badstera post
InitKeyValues(pKeyValues, charenc("VertexLitGeneric"));
LoadFromBuffer(pKeyValues, matname.c_str(), material);

typedef IMaterial*(__thiscall* OriginalFn)(void*, const char *pMaterialName, KeyValues *pVMTKeyValues);
IMaterial* createdMaterial = U::GetVFunc<OriginalFn>(this, 83)(this, matname.c_str(), pKeyValues);

return createdMaterial;
}*/

IMaterial* IMaterialSystem::CreateMaterial(bool flat, bool ignorez, bool wireframed, int color) //opcje dodaj
{
	std::string type = (flat) ? ("UnlitGeneric") : ("VertexLitGeneric");

	//to zostaw encrypted bo xD jednak dosc jednoznaczne
	std::string matdata = ("\"") + type + ("\"\n{\n\t\"$basetexture\" \"vgui/white_additive\"\n\t\"$envmap\"  \"\"\n\t\"$model\" \"1\"\n\t\"$flat\" \"1\"\n\t\"$nocull\"  \"0\"\n\t\"$selfillum\" \"1\"\n\t\"$halflambert\" \"1\"\n\t\"$nofog\"  \"0\"\n\t\"$znearer\" \"0\"\n\t\"$wireframe\" \"") + std::to_string(wireframed) + ("\"\n\t\"$ignorez\" \"") + std::to_string(ignorez) + ("\"\n}\n");

	std::string matname = ("xdxdxd") + std::to_string(created);
	++created;

	KeyValues* pKeyValues = new KeyValues(matname.c_str());

	InitKeyValues(pKeyValues, type.c_str());
	LoadFromBuffer(pKeyValues, matname.c_str(), matdata.c_str());

	typedef IMaterial*(__thiscall* OriginalFn)(void*, const char* pMaterialName, KeyValues* pVMTKeyValues);
	IMaterial* createdMaterial = U::GetVFunc< OriginalFn >(this, 83)(this, matname.c_str(), pKeyValues);

	//createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}

IMaterial* IMaterialSystem::CreateMaterial2(const char* pMaterialNamez, KeyValues* pVMTKeyValuesz)
{
	typedef IMaterial*(__thiscall* OriginalFn)(void*, const char* pMaterialName, KeyValues* pVMTKeyValues);
	return  U::GetVFunc< OriginalFn >(this, 83)(this, pMaterialNamez, pVMTKeyValuesz);
}

IMaterial* IMaterialSystem::FindMaterial(char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix)
{
	typedef IMaterial*(__thiscall* OriginalFn)(void*, char const* pMaterialName, const char *pTextureGroupName, bool complain, const char *pComplainPrefix);
	return U::GetVFunc<OriginalFn>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
}

MaterialHandle_t IMaterialSystem::FirstMaterial()
{
	typedef MaterialHandle_t(__thiscall* FirstMaterialFn)(void*);
	return U::GetVFunc<FirstMaterialFn>(this, 86)(this);
}

MaterialHandle_t IMaterialSystem::NextMaterial(MaterialHandle_t h)
{
	typedef MaterialHandle_t(__thiscall* NextMaterialFn)(void*, MaterialHandle_t);
	return U::GetVFunc<NextMaterialFn>(this, 87)(this, h);
}

MaterialHandle_t IMaterialSystem::InvalidMaterial()
{
	typedef MaterialHandle_t(__thiscall* InvalidMaterialFn)(void*);
	return U::GetVFunc<InvalidMaterialFn>(this, 88)(this);
}

IMaterial* IMaterialSystem::GetMaterial(MaterialHandle_t h)
{
	typedef IMaterial*(__thiscall* GetMaterialFn)(void*, MaterialHandle_t);
	return U::GetVFunc<GetMaterialFn>(this, 89)(this, h);
}

ITexture* IMaterialSystem::FindTexture(char const* pTextureName, const char *pTextureGroupNamed, bool complaind, int nAdditionalCreationFlags)
{
	typedef ITexture*(__thiscall* OriginalFn)(void*, char const*, const char *, bool , int );
	return U::GetVFunc<OriginalFn>(this, 91)(this, pTextureName, pTextureGroupNamed, complaind, nAdditionalCreationFlags);
};

IMatRenderContext* IMaterialSystem::GetRenderContext()
{
	typedef IMatRenderContext*(__thiscall* OriginalFn)(void*);
	return U::GetVFunc<OriginalFn>(this, 115)(this);
};