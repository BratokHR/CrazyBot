#pragma once
#include <Windows.h>
#include <stdio.h>

#define MAX_SAY_TEXT 150

// ������ �������
#define SAYLINE_0			0x004B9230
#define SAYLINE_2			0x004BF5E0
#define SAYLINE_3			0x004BF650
#define SAYBOLD_0			0x004B9340
#define SAYBOLD_2			0x004BF700
#define SAYBOLD_3			0x004BF770
#define SAY_0				0x004CABB0
#define SAY_2				0x004D0DA0
#define SAY_3				0x004D0E10
#define PRINTINCONSOLE_0	0x00430540
#define PRINTINCONSOLE_2	0x00431E90
#define PRINTINCONSOLE_3	0x00431EE0
#define CMDCONSOLE_0		0x0041FD10
#define CMDCONSOLE_2		0x00421470
#define CMDCONSOLE_3		0x004214C0
#define REGFUNCTION_0		0x0041FB40
#define REGFUNCTION_2		0X0
#define REGFUNCTION_3		0X0

typedef void (*xcommand_t)( );
typedef void (*g_CG_Printf)( const char *msg, ... ); 
typedef void (*g_WritetoConsole) ( const char *msg );
typedef void (*g_CG_AddCommand)( const char *cmdName, xcommand_t func );

class print
{
private:
	static int version;				// ������ ���� 0 / 2 / 3
	static DWORD d_sayline;			// ����� ������� ������ ��������� � sayline (����� �����)
	static DWORD d_saybold;			// ����� ������� ������ ��������� � saybold (�� ������ ������)
	static DWORD d_say;				// ����� ������� ������ ������ � ��� ����
	static DWORD d_printinconsole;	// ����� ������� ��������� ������ � ������� ����
	static DWORD d_cmdconsole;		// ����� ������� �������� ������� � ������� ����
	static DWORD d_addcmd;			// ����� ������� ����������� ������� � �������

public:
	// �������������� ����������, ���������� ������ 1 ���
	static void PrintInit();
	// ���������� ������ ���� (��-��������� ������ 1.3)
	static char* CheckVersionGame();
	// ������� ������ ��������� � sayline (����� �����)
	static void Sayline( const char *msg, ...);
	// ������� ������ ��������� � saybold (�� ������ ������)
	static void Saybold( const char *msg, ...);
	// ������� ������ ������ � ��� ����
	static void Say( const char *msg, ...);

	// ������� ��������� ������ � �������
	static g_CG_Printf PrintConsole;
	// ������� �������� ������� � �������
	static g_WritetoConsole WritetoConsole;
	// ������� ����������� ������� � �������
	static g_CG_AddCommand AddCommand;
};