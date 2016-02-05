#include "stdafx.h"

crazybot	bot;
chook		*Hook;

cg_t *				cg				= (cg_t *)			0x01379000;
cgs_t *				cgs				= (cgs_t *)			0x0137068C;
clientInfo_t *		clientinfo		= (clientInfo_t *)	0x0145A914;
centity_t *			cg_entities		= (centity_t *)		0x0146DA00;
input_t*			input			= (input_t *)		0x924864;
userCmd_t			*cmd, *oldcmd;
POINT				Cursor;

DWORD		MenuOpen	=				0x00461C6F;
DWORD		Attack		=				0x00407180;
DWORD		Wallhack	= (DWORD)		0x4D631E;
DWORD		NoRecoil	= (DWORD)		0x4D0F15;
float*		viewangles	= (float *)		0x8E4824;
int *		ping		= (int *)		0x8DC234;

const xcommand_t	StartAttack	= (xcommand_t)0x407180;
const xcommand_t	StopAttack	= (xcommand_t)0x4071A0;
const xcommand_t	OpenConsole = (xcommand_t)0x403820;

g_WriteConsole trap_WriteConsole = (g_WriteConsole)0x41FD10;