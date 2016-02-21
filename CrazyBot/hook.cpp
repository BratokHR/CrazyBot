#include "stdafx.h"

void chook::MemoryWrite(void *adr, void *ptr, int size)
{
	DWORD OldProtection;
	VirtualProtect(adr, size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy(adr, ptr, size);
	VirtualProtect(adr, size, OldProtection, &OldProtection);
}

BOOL chook::bCompare(const BYTE *pData, const BYTE *bMask, const char *szMask)
{
	for (; *szMask; szMask++, bMask++, pData++)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD chook::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask)
{
	for (DWORD i = 0; i <  dwLen; i++)
		if (bCompare((BYTE*)dwAddress + i, bMask, szMask))
			return (DWORD)(dwAddress + i);
	return -1;
}