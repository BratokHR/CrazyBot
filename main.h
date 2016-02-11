#pragma once

#define PROCESS_NAME "CoD2MP_s.exe" 
#define DLL_NAME "CrazyBot.dll"

#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ) 

BOOL LoadDll(char *procName, char *dllName);
BOOL InjectDLL(DWORD ProcessID, char *dllName);
