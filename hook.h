#pragma once
class chook
{
public:
	void MemoryWrite(void *adr, void *ptr, int size);
	BOOL bCompare(const BYTE *pData, const BYTE *bMask, const char *szMask);
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char *szMask);
};