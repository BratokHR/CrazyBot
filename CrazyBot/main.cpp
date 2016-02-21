#include "stdafx.h"

#define Thread(function) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)function, NULL, NULL, NULL)

void __stdcall KeyHook()
{
	for (;;Sleep(20))
	{
		if (KEY_DOWN(VirtualKeyTable[(int)cFuncAimKey.iValue].uiKey))
			Aimkeypress = true;
		else
			Aimkeypress = false;

		if (Shoot && !MenuManager.menuOpen && *bot.inMenu == 0)
		{
			keybd_event(VK_LBUTTON, 0, 0, 0);
			keybd_event(VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0);
			Shoot = false;
		}

		if (!bot.cg->snap && MenuManager.menuOpen)
		{
			Hook->MemoryWrite((void*)bot.MenuOpen, (void*)"\x75\x7C", 2);
			Hook->MemoryWrite((void*)bot.Attack, (void*)"\x56", 1);
		}
	}
}

void __stdcall main()
{
	while (GetModuleHandleA("gfx_d3d_mp_x86_s.dll") == NULL)
			Sleep(100);

	bot.InitVersion();
	DetoursInstall();

	Thread(KeyHook);
}

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		MessageBox(NULL, "CrazyBot by BratokHR...", "Good!", NULL);
		bot.hModule = hModule;

		DWORD n = GetModuleFileName( hModule, bot.path, MAX_PATH );
		for( char * p = &bot.path[ n ]; *p != '\\'; p-- )
			*p = '\0';

		Thread(main);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) 
	{
		DetoursUnistall();
	}
	return TRUE;
}