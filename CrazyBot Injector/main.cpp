#include <windows.h>
#include <tlhelp32.h>
#include <io.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ) 

#define PROCESS_NAME "CoD2MP_s.exe" 
#define DLL_NAME "CrazyBot.dll"
#define CFG_NAME "CrazyGame.cfg"

char path_folder[MAX_PATH];
char path_dll[MAX_PATH];
char path_cfg[MAX_PATH];
string path_exe;

FILE * pLogFile;

BOOL InjectDLL(DWORD ProcessID, char *dllName)
{
	HANDLE Proc;
	char buf[50] = { 0 };
	LPVOID RemoteString, LoadLibAddy;

	Proc = OpenProcess(CREATE_THREAD_ACCESS, false, ProcessID);
	if (!Proc)
	{
		MessageBox(NULL, "OpenProcess failed\nRun as administrator", "CrazyBot", NULL);
		return false;
	}
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(Proc, (LPVOID)RemoteString, dllName, strlen(dllName), NULL);
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);

	CloseHandle(Proc);

	return true;
}

bool isProcessRun(DWORD *ProcessID)
{
	PROCESSENTRY32	entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	bool process = false;

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, PROCESS_NAME) == 0)
			{
				*ProcessID = entry.th32ProcessID;
				CloseHandle(snapshot);
				return true;
			}
		}
	}
	CloseHandle(snapshot);
	return false;
}

void PrintCFG( LPCSTR lpszText )
{
	fopen_s( &pLogFile, path_cfg, "a+" );

	if( pLogFile )
	{
		fprintf_s( pLogFile, "%s", lpszText );
		fflush( pLogFile );
	}
}

void ReadFile()
{
	string line;
    string text;
    int count = 0;
	ifstream myfile (path_cfg);
 
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            getline (myfile,line);
            text += line;
        }
        myfile.close();
    }

	path_exe = text.c_str();
}

void FolderToGame()
{
	OPENFILENAME ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name

	ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "CoD2MP_s.exe\0*.exe\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    GetOpenFileName(&ofn);

	PrintCFG(ofn.lpstrFile);

	path_exe = string(ofn.lpstrFile);
}

void RunGame()
{
	HANDLE hProcess = NULL;

	STARTUPINFO st; 
    ZeroMemory (&st, sizeof(st));

    st.cb = sizeof (STARTUPINFO);

    PROCESS_INFORMATION Proc_Info;
    ZeroMemory (&Proc_Info, sizeof(Proc_Info));

	string dir = path_exe;
	for( char * p = &dir[strlen(dir.c_str())]; *p != '\\'; p-- )
		*p = '\0';

	if(!CreateProcess(path_exe.c_str(), NULL, NULL, NULL, FALSE, NULL, NULL, dir.c_str(), &st, &Proc_Info))
	{
		MessageBox(NULL, "Couldn't Create process\nRun as administrator", "CrazyBot", NULL);
		return;
	}

	WaitForInputIdle(Proc_Info.hProcess, 10000);

	DWORD dump;
	if (isProcessRun(&dump))
		InjectDLL(Proc_Info.dwProcessId, path_dll);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD ProcessID;

	GetCurrentDirectory(MAX_PATH, path_folder);

	sprintf_s<MAX_PATH>(path_cfg, "%s\\%s", path_folder, CFG_NAME);
	sprintf_s<MAX_PATH>(path_dll, "%s\\%s", path_folder, DLL_NAME);

	if (_access(path_dll, 0) == -1)
	{
		MessageBox(NULL, "CrazyBot.dll not found", "CrazyBot", NULL);
		return false;
	}

	if (isProcessRun(&ProcessID))
	{
		InjectDLL(ProcessID, path_dll);
	}
	else
	{
		ReadFile();
		if (_access(path_exe.c_str(), 0) == -1 || strlen(path_exe.c_str()) == 0)
			FolderToGame();
		RunGame();
	}
	return 1;
}