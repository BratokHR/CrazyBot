#pragma once
#include <Windows.h>
#include <stdio.h>

#define MAX_SAY_TEXT 150

// Адреса функций
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
	static int version;				// Версия игры 0 / 2 / 3
	static DWORD d_sayline;			// Адрес функции вывода сообщения в sayline (слева снизу)
	static DWORD d_saybold;			// Адрес функции вывода сообщения в saybold (по центру экрана)
	static DWORD d_say;				// Адрес функции вывода текста в чат игры
	static DWORD d_printinconsole;	// Адрес функции написания текста в консоль игры
	static DWORD d_cmdconsole;		// Адрес функции отправки команды в консоль игры
	static DWORD d_addcmd;			// Адрес функции добавляющая команды в консоль

public:
	// Инициализирует переменные, вызывается только 1 раз
	static void PrintInit();
	// Возвращает версию игры (по-умолчанию вернет 1.3)
	static char* CheckVersionGame();
	// Функция вывода сообщения в sayline (слева снизу)
	static void Sayline( const char *msg, ...);
	// Функция вывода сообщения в saybold (по центру экрана)
	static void Saybold( const char *msg, ...);
	// Функция вывода текста в чат игры
	static void Say( const char *msg, ...);

	// Функция написания текста в консоле
	static g_CG_Printf PrintConsole;
	// Функция отправки команды в консоль
	static g_WritetoConsole WritetoConsole;
	// Функция добавляющая команды в консоль
	static g_CG_AddCommand AddCommand;
};