#include <windows.h>
#include <tlhelp32.h>
#include <io.h>

#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LoadDll(PROCESS_NAME, DLL_NAME);
	return 1;
}

BOOL LoadDll(char *procName, char *dllName)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, PROCESS_NAME) == 0)
			{
				InjectDLL(entry.th32ProcessID, dllName);
				return 1;
			}
		}
	}

	MessageBox(NULL, "CoD2MP_s.exe process not found", "CrazyBot", NULL);
	return 0;
}

BOOL InjectDLL(DWORD ProcessID, char *dllName)
{
	HANDLE Proc;
	char buf[50] = { 0 };
	LPVOID RemoteString, LoadLibAddy;

	if (_access(DLL_NAME, 0) == -1)
	{
		MessageBox(NULL, "CrazyBot.dll not found", "CrazyBot", NULL);
		return false;
	}

	Proc = OpenProcess(CREATE_THREAD_ACCESS, false, ProcessID);

	if (!Proc)
	{
		MessageBox(NULL, "OpenProcess failed", "CrazyBot", NULL);
		return false;
	}

	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(Proc, (LPVOID)RemoteString, dllName, strlen(dllName), NULL);
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);

	CloseHandle(Proc);

	MessageBox(NULL, "Injection complete", "CrazyBot", NULL);
	return true;
}