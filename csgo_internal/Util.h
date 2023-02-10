#pragma once

#define RandomInt(min, max) (rand() % (max - min + 1) + min)

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

#define MakePtr (cast, ptr, addValue) ( cast )( (DWORD)( ptr ) + ( DWORD )( addValue ) )

class KeyValues;





namespace U
{

	extern DWORD FindPattern(const char* moduleName, const char* pattern);
	extern CNetVarManager* NetVars;
	extern void SetupInterfaces();
	extern void SetupHooks();
	extern void SetupOffsets();
	extern void SetupTextures();
	extern void Setup();

	namespace exports
	{
		inline float RandomFloat(float min, float max)
		{
			static auto fn = (decltype(&RandomFloat))(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
			return fn(min, max);
		}

		inline void RandomSeed(int seed)
		{
			static auto fn = (decltype(&RandomSeed))(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));

			return fn(seed);
		}
	}

	template< class T, class Y >
	T Clamp(T const &val, Y const &minVal, Y const &maxVal)
	{
		if (val < minVal)
			return minVal;
		else if (val > maxVal)
			return maxVal;
		else
			return val;
	}

	template <typename T>
	T GetVFunc(void *vTable, int iIndex) {
		return (*(T**)vTable)[iIndex];
	}

	template <typename T>
	T* CaptureInterface(const char* strModule, const char* strInterface)
	{
		typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);

		CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(strModule), "CreateInterface");
		return CreateInterface(strInterface, 0);
	}

	template<typename... Args>
	void ConColorMsg(const Color& clr, const char* pMsg, Args... args)
	{
		static auto import = (void(*)(const Color&, const char*, ...))GetProcAddress(GetModuleHandleA("tier0.dll"), "?ConColorMsg@@YAXABVColor@@PBDZZ");
		return import(clr, pMsg, args...);
	}

	extern float random_float(float min, float max);
}
