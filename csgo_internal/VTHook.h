#pragma once

class VTHook
{
public:
	VTHook()
	{
		memset(this, 0, sizeof(VTHook));
	}

	VTHook(PDWORD* ppdwClassBase)
	{
		bInitialize(ppdwClassBase);
	}

	~VTHook()
	{
		UnHook();
	}

	bool bInitialize(PDWORD* ppdwClassBase)
	{
		m_ClassBase = ppdwClassBase;
		m_OldVT = *ppdwClassBase;
		m_VTSize = GetVTCount(*ppdwClassBase);
		m_NewVT = new DWORD[m_VTSize + 1];
		memcpy(&m_NewVT[1], m_OldVT, sizeof(DWORD) * m_VTSize);
		m_NewVT[0] = (uintptr_t)m_OldVT[-1];
		DWORD old;
		VirtualProtect(ppdwClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
		*ppdwClassBase = &m_NewVT[1];
		VirtualProtect(ppdwClassBase, sizeof(DWORD), old, &old);
		return true;
	}

	/*
	for anyone wondering how to
	include copying the rtti pointer
	when replacing the table Code:

	m_ClassBase = ppdwClassBase;
	m_OldVT = *ppdwClassBase;
	m_VTSize = GetVTCount( *ppdwClassBase );
	m_NewVT = new DWORD[ m_VTSize + 1 ];
	memcpy( &m_NewVT[ 1 ], m_OldVT, sizeof( DWORD ) * m_VTSize );
	m_NewVT[ 0 ] = ( uintptr_t ) m_OldVT[ -1 ];
   *ppdwClassBase = &m_NewVT[ 1 ];  //7 line

keep in mind that the rtti pointer is now
at the first place inside your new table so youll need
to take that into consideration when rehooking for
example (hint: line 7)

	*/
	bool bInitialize(PDWORD** pppdwClassBase) // fix for pp
	{
		return bInitialize(*pppdwClassBase);
	}

	void UnHook()
	{
		if (m_ClassBase)
		{
			DWORD old;
			VirtualProtect(m_ClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*m_ClassBase = m_OldVT;
			VirtualProtect(m_ClassBase, sizeof(DWORD), old, &old);
		}
	}

	void ReHook()
	{
		if (m_ClassBase)
		{
			DWORD old;
			VirtualProtect(m_ClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*m_ClassBase = &m_NewVT[1];
			VirtualProtect(m_ClassBase, sizeof(DWORD), old, &old);
		}
	}

	int iGetFuncCount()
	{
		return (int)m_VTSize;
	}

	DWORD GetFuncAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_VTSize && m_OldVT != NULL)
		{
			return m_OldVT[Index];
		}
		return NULL;
	}

	PDWORD GetOldVT()
	{
		return m_OldVT;
	}

	DWORD HookFunction(DWORD dwNewFunc, unsigned int iIndex)
	{
		if (m_NewVT && m_OldVT && iIndex <= m_VTSize && iIndex >= 0)
		{
			m_NewVT[iIndex + 1] = dwNewFunc;
			return m_OldVT[iIndex];
		}

		return NULL;
	}

private:
	DWORD GetVTCount(PDWORD pdwVMT)
	{
		DWORD dwIndex = 0;

		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
			{
				break;
			}
		}
		return dwIndex;
	}
	PDWORD*	m_ClassBase;
	PDWORD	m_NewVT, m_OldVT;
	DWORD	m_VTSize;
};


namespace detail
{
	class protect_guard
	{
	public:
		protect_guard(void* base, size_t len, std::uint32_t flags)
		{
			_base = base;
			_length = len;
			if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
				throw std::runtime_error("...");
		}
		~protect_guard()
		{
			VirtualProtect(_base, _length, _old, (PDWORD)&_old);
		}

	private:
		void*         _base;
		size_t        _length;
		std::uint32_t _old;
	};
}
