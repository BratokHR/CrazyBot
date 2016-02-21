#include "stdafx.h"

typedef void	(*t_EndFrame)	( );
t_EndFrame	o_EndFrame = (t_EndFrame)NULL;

typedef void	(*t_CG_Obituary)	( );
t_CG_Obituary	o_CG_Obituary	= (t_CG_Obituary)NULL;

char WickedSick[MAX_PATH];
char GodLike[MAX_PATH];
char Dominating[MAX_PATH];
char HeadShot[MAX_PATH];
char KillingSpree[MAX_PATH];
char Rampage[MAX_PATH];
char MonsterKill[MAX_PATH];
char Unstoppable[MAX_PATH];
char DoubleKill[MAX_PATH];
char Dead[MAX_PATH];
char HolyShit[MAX_PATH];

void Bot_Obituary( entityState_t * ent, int iMod )
{
	int				iTarget		= ent->otherEntityNum;
	int				iAttacker	= ent->otherEntityNum2;
	clientInfo_t *	ciTarget	= NULL;
	clientInfo_t *	ciAttacker	= NULL;

	if( iTarget >= 0 && iTarget < MAX_PLAYERS )
	{
		ciTarget = &bot.clientinfo[ iTarget ];

		// entity is dead
		bot.cg_entities[ iTarget ].currentState.eFlags &= 1;

		if( iAttacker >= 0 && iAttacker < MAX_PLAYERS )
			ciAttacker = &bot.clientinfo[ iAttacker ];
		else
			iAttacker = ENTITYNUM_WORLD;

		if( ciAttacker && ciAttacker->clientNum == bot.cg->clientNum )
		{
			if( ciTarget->clientNum == bot.cg->clientNum )
			{
				bot.stats.suicides++;
				bot.stats.killstreak = 0;
				if (cFuncMiscKillSound.bValue)
					PlaySound(Dead, NULL, SND_ASYNC);
			}
			else
			{
				if( iMod == 7 )
				{
					bot.stats.totalkills++;
					bot.stats.bash++;
					bot.stats.killstreak++;
				}
				else if( iMod == 8 )
				{
					bot.stats.totalkills++;
					bot.stats.headshot++;
					bot.stats.killstreak++;
				}
				else
				{
					bot.stats.totalkills++;
					bot.stats.killstreak++;
				}
				if (cFuncMiscKillSound.bValue)
				switch (bot.stats.killstreak)
				{
				case 2:
					PlaySound(DoubleKill, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Double kill!");
					break;
				case 5:
					PlaySound(KillingSpree, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Killing Spree!");
					break;
				case 10:
					PlaySound(Dominating, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Dominating!");
					break;
				case 15:
					PlaySound(MonsterKill, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Monster Kill!");
					break;
				case 20:
					PlaySound(Rampage, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Rampage!");
					break;
				case 25:
					PlaySound(Unstoppable, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3Unstoppable!");
					break;
				case 30:
					PlaySound(GodLike, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3GodLike!");
					break;
				case 40:
					PlaySound(WickedSick, NULL, SND_ASYNC);
					print::Sayline("^2[^7Crazy^9Bot^2] ^3WickedSick!");
					break;
				default:
					if (iMod == 8)
					{
						PlaySound(HeadShot, NULL, SND_ASYNC);
						print::Saybold("^2[ ^9Head^7Shot ^2]");
					}
					break;
				}
			}
		}
		else if( ciTarget->clientNum == bot.cg->clientNum )
		{
			bot.stats.death++;
			bot.stats.killstreak = 0;
		}
	}
}

void h_CG_Obituary( )
{
	static entityState_t * ent;
	__asm mov ent, eax

	if( ent )
		Bot_Obituary( ent, ent->eventParm & 0xFFFFFF7F );

	__asm mov eax, ent
	o_CG_Obituary( );
}

void __stdcall Bot_Initialize()
{
	bot.fonts.Console		= "fonts/consoleFont";
	bot.fonts.Normal		= "fonts/normalFont";
	bot.fonts.Small			= "fonts/smallFont";
	bot.fonts.Big			= "fonts/bigFont";
	bot.fonts.ExtraBig		= "fonts/extraBigFont";
	bot.fonts.Bold			= "fonts/boldFont";

	bot.shaders.Arrow		= "hud_grenadepointer";
	bot.shaders.GrenadeIcon	= "hud_grenadeicon";
	bot.shaders.Cursor		= "ui/assets/3_cursor3";
	bot.shaders.Gradient	= "ui/assets/gradientbar2";
	bot.shaders.Black		= "black";
	bot.shaders.White		= "white";				
	bot.shaders.RadarFriend = "compassping_friendlyyelling";
	bot.shaders.RadarEnemy	= "compassping_enemyyelling";

	/*CVAR UNLOCKER*/
	Hook->MemoryWrite((void*)bot.CvarUnlocker1, (void*)"\xEB", 1); //0xEB - on / 0x74 - off
	Hook->MemoryWrite((void*)bot.CvarUnlocker2, (void*)"\xEB", 1); //0xEB - on / 0x74 - off
	Hook->MemoryWrite((void*)bot.CvarUnlocker3, (void*)"\xEB", 1); //0xEB - on / 0x75 - off

	sprintf( WickedSick, "%s\\sounds\\wickedsick.wav", bot.path );
	sprintf( GodLike, "%s\\sounds\\godlike.wav", bot.path );
	sprintf( Dominating, "%s\\sounds\\dominating.wav", bot.path );
	sprintf( HeadShot, "%s\\sounds\\Headshot.wav", bot.path );
	sprintf( KillingSpree, "%s\\sounds\\killingspree.wav", bot.path );
	sprintf( Rampage, "%s\\sounds\\rampage.wav", bot.path );
	sprintf( MonsterKill, "%s\\sounds\\monsterkill.wav", bot.path );
	sprintf( Unstoppable, "%s\\sounds\\unstoppable.wav", bot.path );
	sprintf( DoubleKill, "%s\\sounds\\DoubleKill.wav", bot.path );
	sprintf( Dead, "%s\\sounds\\dead.wav", bot.path );
	sprintf( HolyShit, "%s\\sounds\\HolyShit.wav", bot.path );
}

int InfoSettingsSleep = 12000;
int infoNowTickCount = 0;
void InfoSettings()
{
	if (bot.InitSettings || !((infoNowTickCount + InfoSettingsSleep) <= GetTickCount()))
		return;

	infoNowTickCount = GetTickCount();
	print::Say("^2[^7Crazy^9Bot^1:error^2]^7: Configuration file not found");
	print::Say("^2[^7Crazy^9Bot^3:ad^2]^7: To open the menu, press ^5[^7Insert^5]");
}

int nameStealerSleep = 700;
int nowTickCount = 0;
void NameStealer()
{
	if (!cFuncMiscNameStealer.bValue || !((nowTickCount + nameStealerSleep) <= GetTickCount()))
		return;

	nowTickCount = GetTickCount();
	int				clientNum;
	clientInfo_t *	ci;

	for( int i = 0; i < 500; i++ )
	{
		clientNum = ( rand( ) % MAX_PLAYERS );

		if( clientNum != bot.cg->clientNum )
		{
			ci = &bot.clientinfo[ clientNum ];

			if( ci->infoValid && strcmp( bot.clientinfo[ bot.cg->clientNum ].name, ci->name ) != 0 )
			{
				static char szCommand[128];
				sprintf_s<128>( szCommand, "name %s", ci->name );
				print::WritetoConsole( szCommand );
				break;
			}
		}
	}
}

void h_EndFrame(  )
{ 
	o_EndFrame();

	char *hostname = (char*)0x013706c4;
	if( bot.cg->snap && strcmp(hostname, "^9D^7eath^9R^7un^3... ^6Cracked") != 0)
    {
		if (!bot.init) {
			Bot_Initialize();
			MenuManager.initialize();
			GSettings.ResetSettings();
			GSettings.LoadSettings();
			bot.init = !bot.init;
		}
		Cheats();
		MenuManager.perform();
		NameStealer();
		InfoSettings();
	}
}

void DetoursInstall()
{
	o_EndFrame = (t_EndFrame)DetourFunction( (PBYTE)bot.gfx_endframe, (PBYTE)h_EndFrame );
	o_CG_Obituary = (t_CG_Obituary)DetourFunction( (PBYTE)bot.obituary, (PBYTE)h_CG_Obituary );
}

void DetoursUnistall()
{
	DetourRemove( (PBYTE)o_EndFrame, (PBYTE)h_EndFrame );
	DetourRemove( (PBYTE)o_CG_Obituary, (PBYTE)h_CG_Obituary );
}