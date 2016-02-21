#include "cPrintinEngine.h"

int print::version = 0;
DWORD print::d_sayline = 0x0;
DWORD print::d_saybold = 0x0;
DWORD print::d_say = 0x0;
DWORD print::d_printinconsole = 0x0;
DWORD print::d_cmdconsole = 0x0;
DWORD print::d_addcmd = 0x0;

g_CG_Printf print::PrintConsole = (g_CG_Printf)0x0;
g_CG_AddCommand print::AddCommand = (g_CG_AddCommand)0x0;
g_WritetoConsole print::WritetoConsole = (g_WritetoConsole)0x0;

void print::PrintInit()
{
	if (strcmp((char*)0x561B1C, "1.0") == 0)
	{
		version = 0;
		d_cmdconsole = CMDCONSOLE_0;
		d_printinconsole = PRINTINCONSOLE_0;
		d_say = SAY_0;
		d_saybold = SAYBOLD_0;
		d_sayline = SAYLINE_0;
		d_addcmd = REGFUNCTION_0;
	}
	else if (strcmp((char*)0x5A1D54, "1.2") == 0)
	{
		version = 2;
		d_cmdconsole = CMDCONSOLE_2;
		d_printinconsole = PRINTINCONSOLE_2;
		d_say = SAY_2;
		d_saybold = SAYBOLD_2;
		d_sayline = SAYLINE_2;
		d_addcmd = REGFUNCTION_2;
	}
	else
	{
		version = 3;
		d_cmdconsole = CMDCONSOLE_3;
		d_printinconsole = PRINTINCONSOLE_3;
		d_say = SAY_3;
		d_saybold = SAYBOLD_3;
		d_sayline = SAYLINE_3;
		d_addcmd = REGFUNCTION_3;
	}

	PrintConsole = (g_CG_Printf)d_printinconsole;
	WritetoConsole = (g_WritetoConsole)d_cmdconsole;
	AddCommand = (g_CG_AddCommand)d_addcmd;
}

char* print::CheckVersionGame()
{
	if (version == 0)
		return "1.0";
	else if (version == 2)
		return "1.2";

	return "1.3";
}

void print::Sayline( const char *msg, ...)
{
	va_list		argptr;
	char		text[MAX_SAY_TEXT];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	__asm
    {
        lea ESI, text
        mov ECX, ESI
		call d_sayline
    }
}

void print::Saybold( const char *msg, ...)
{
	va_list		argptr;
	char		text[MAX_SAY_TEXT];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	__asm
    {
        lea ESI, text
        mov ECX, ESI
		call d_saybold
    }
}

void print::Say( const char *msg, ...)
{
	va_list		argptr;
	char		text[MAX_SAY_TEXT];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	__asm
    {
        lea ESI, text
        mov ECX, ESI
		call d_say
    }
}