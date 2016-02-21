#include "stdafx.h"

crazybot			bot;
chook				*Hook;
POINT				Cursor;
vector<BotTarger_t> Targets;

bool Aimkeypress = false;
bool Shoot = false;

void crazybot::InitVersion()
{
	print::PrintInit();
	Draw.Init();
	char *version = print::CheckVersionGame();

	if (strcmp(version, "1.0") == 0)
	{
		bot.cg			= (cg_t*)		0x01379000;
		bot.cgs			= (cgs_t *)		0x0137068C;
		bot.clientinfo		= (clientInfo_t *)	0x0145A914;
		bot.cg_entities		= (centity_t *)		0x0146DA00;
		bot.input		= (input_t *)		0x00924864;
		bot.OpenConsole		= (xcommand_t)		0x00403820;
		bot.ping		= (int *)		0x008DC234;
		bot.viewangles		= (float *)		0x008E4824;

		bot.gfx_endframe	=			0x004C5A40;
		bot.obituary		=			0x004D9ED0;

		bot.trace		=			0x004D8170;
		bot.lerptag		=			0x004C6AE0;
		bot.gethandle		=			0x00433DB0;
		bot.gettagnumber	=			0x00474560;

		bot.MenuOpen		=			0x00461C6F;
		bot.NoRecoil		=			0x004D0F15;
		bot.Wallhack		=			0x004D631E;
		bot.Attack		=			0x00407180;
		bot.Fov_x		=			0x00646488;

		bot.CvarUnlocker1	=			0x00435840;
		bot.CvarUnlocker2	=			0x0043585F;
		bot.CvarUnlocker3	=			0x00435890;

		bot.inGame		= (bool *)		0x00C1E26C;
		bot.inMenu		= (int *)		0x008DC20C;
	}
	else if (strcmp(version, "1.2") == 0)
	{
		bot.cg			= (cg_t*)		0x0141A080;
		bot.cgs			= (cgs_t *)		0x0141170C;
		bot.clientinfo		= (clientInfo_t *)	0x014FB994;
		bot.cg_entities		= (centity_t *)		0x0150EA80;
		bot.input		= (input_t *)		0x00997E2C;
		bot.OpenConsole		= (xcommand_t)		0x004039A0;
		bot.ping		= (int *)		0x0093367C;
		bot.viewangles		= (float *)		0x00957DEC;

		bot.gfx_endframe	=			0x004CBC30;
		bot.obituary		=			0x004E0380;

		bot.trace		=			0x004DE620;
		bot.lerptag		=			0x004CCCD0;
		bot.gethandle		=			0x00435660;
		bot.gettagnumber	=			0x004774C0;

		bot.MenuOpen		=			0x0046498F;
		bot.NoRecoil		=			0x004D70A5;
		bot.Wallhack		=			0x004DC79E;
		bot.Attack		=			0x00407B10;
		bot.Fov_x		=			0x009839D4;

		bot.CvarUnlocker1	=			0x00437150;
		bot.CvarUnlocker2	=			0x0043716F;
		bot.CvarUnlocker3	=			0x004371A0;

		bot.inGame		= (bool *)		0x00CA3144;
		bot.inMenu		= (int *)		0x00933654;
	}
	else 
	{
		bot.cg			= (cg_t*)		0x014EE080;
		bot.cgs			= (cgs_t *)		0x014E5704;
		bot.clientinfo		= (clientInfo_t *)	0x015CF994;
		bot.cg_entities		= (centity_t *)		0x015E2A80;
		bot.input		= (input_t *)		0x009CFE2C;
		bot.OpenConsole		= (xcommand_t)		0x00403910;
		bot.ping		= (int *)		0x0096B67C;
		bot.viewangles		= (float *)		0x0098FDEC;

		bot.gfx_endframe	=			0x004CBCA0;
		bot.obituary		=			0x004E03F0;

		bot.trace		=			0x004DE690;
		bot.lerptag		=			0x004CCD40;
		bot.gethandle		=			0x004356B0;
		bot.gettagnumber	=			0x00477500;

		bot.MenuOpen		=			0x004649CF;
		bot.NoRecoil		=			0x004D7115;
		bot.Wallhack		=			0x004DC80E;
		bot.Attack		=			0x00407A90;
		bot.Fov_x		=			0x009839D4;

		bot.CvarUnlocker1	=			0x004371A0;
		bot.CvarUnlocker2	=			0x004371BF;
		bot.CvarUnlocker3	=			0x004371DF;
		
		bot.inGame		= (bool *)		0x00D77144;
		bot.inMenu		= (int *)		0x0096B654;
	}

	bot.InitSettings = false;
}
