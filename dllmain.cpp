#include "stdafx.h"

DWORD GFX_MODULE_Base = NULL;
bool init = false;
cMenuManager m;

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

string spam[] = {
	"say ^6%s ^7Took a ^3HEADSHOT ^7by ^3Crazy^1bot [^5PUBLIC^1]",
};

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
	Hook->MemoryWrite((void*)0x435840, (void*)"\xEB", 1); //0xEB - on / 0x74 - off
	Hook->MemoryWrite((void*)0x43585F, (void*)"\xEB", 1); //0xEB - on / 0x74 - off
	Hook->MemoryWrite((void*)0x435890, (void*)"\xEB", 1); //0xEB - on / 0x75 - off

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

void Bot_Obituary( entityState_t * ent, int iMod )
{
	int				iTarget		= ent->otherEntityNum;
	int				iAttacker	= ent->otherEntityNum2;
	clientInfo_t *	ciTarget	= NULL;
	clientInfo_t *	ciAttacker	= NULL;

	if( iTarget >= 0 && iTarget < MAX_PLAYERS )
	{
		ciTarget = &clientinfo[ iTarget ];

		// entity is dead
		cg_entities[ iTarget ].currentState.eFlags &= 1;
		//pBot->SetInvalidPlayer( iTarget );
		
		if( iAttacker >= 0 && iAttacker < MAX_PLAYERS )
			ciAttacker = &clientinfo[ iAttacker ];
		else
			iAttacker = ENTITYNUM_WORLD;

		if( ciAttacker && ciAttacker->clientNum == cg->clientNum )
		{
			if( ciTarget->clientNum == cg->clientNum )
			{
				bot.stats.suicides++;
				bot.stats.killstreak = 0;
				if ((bool)cFuncMiscKillSound.iValue)
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
					if ((bool)cFuncMiscKillSpam.iValue)
					{
							char spamtext[128];
							sprintf(spamtext, spam[rand() % 1].c_str(), ciTarget->name);
							trap_WriteConsole(spamtext);
					}
				}
				else
				{
					bot.stats.totalkills++;
					bot.stats.killstreak++;
				}
				if ((bool)cFuncMiscKillSound.iValue)
				switch (bot.stats.killstreak)
				{
				case 2:
					PlaySound(DoubleKill, NULL, SND_ASYNC);
					break;
				case 5:
					PlaySound(KillingSpree, NULL, SND_ASYNC);
					break;
				case 10:
					PlaySound(Dominating, NULL, SND_ASYNC);
					break;
				case 15:
					PlaySound(MonsterKill, NULL, SND_ASYNC);
					break;
				case 20:
					PlaySound(Rampage, NULL, SND_ASYNC);
					break;
				case 25:
					PlaySound(Unstoppable, NULL, SND_ASYNC);
					break;
				case 30:
					PlaySound(GodLike, NULL, SND_ASYNC);
					break;
				case 40:
					PlaySound(WickedSick, NULL, SND_ASYNC);
					break;
				default:
					if (iMod == 8)
						PlaySound(HeadShot, NULL, SND_ASYNC);
					break;
				}
			}
		}
		else if( ciTarget->clientNum == cg->clientNum )
		{
			bot.stats.death++;
			bot.stats.killstreak = 0;
		}
	}
}

void h_CG_Obituary( )
{
	static entityState_t * ent;
	__asm(".intel_syntax noprefix\n");
	__asm("mov ent, eax\n");

	if( ent )
		Bot_Obituary( ent, ent->eventParm & 0xFFFFFF7F );

	__asm(".intel_syntax noprefix\n");
	__asm("mov eax, ent\n");
	o_CG_Obituary( );
}

void __cdecl h_EndFrame(  )
{ 
	o_EndFrame();
	if( cg->snap )
    {
		if (!init) {
			Bot_Initialize();
			MenuManager.initialize();
			GSettings.ResetSettings();
			GSettings.LoadSettings();
			init = !init;
		}
		Cheats();
		MenuManager.perform();
	}
}

/*
561B1C - 1.0
5A1D54 - 1.2
5A1D44 - 1.3

if (strcmp((char*)0x561B1C, "1.0") == 0)
	Draw.Draw_Text(300, 300, 0.8, colorRed, F_LEFT, bot.fonts.Big, "1.0");
else if (strcmp((char*)0x5A1D54, "1.2") == 0)
	Draw.Draw_Text(300, 300, 0.8, colorRed, F_LEFT, bot.fonts.Big, "1.2");
else if (strcmp((char*)0x5A1D44, "1.3") == 0)
	Draw.Draw_Text(300, 300, 0.8, colorRed, F_LEFT, bot.fonts.Big, "1.3");
*/

/*
EndFrame:
1.0 -> 0x004C5A40
1.2 -> 0x004CBC30
1.3 -> 0x004CBCA0
*/

void __stdcall NameStealer()
{
	static char szCommand[128];
	for (;;)
	{
		if (cg->snap && !Targets.empty())
		{
			if ((bool)cFuncMiscNameStealer.iValue)
			{
				BotTarger_t player = Targets[ rand() % Targets.size() ];

				if (player.ci->infoValid)
				{
					sprintf_s<128>( szCommand, "name %s", player.ci->name );
					trap_WriteConsole(szCommand);
				}
				Sleep(300);
			}
		}
	}
}

void __stdcall AutoVote()
{
	static char szCommand[128];
	for (;;)
	{
		if (cg->snap && !Targets.empty())
		{
			if ((bool)cFuncAutoVote.iValue && !cgs->voteTime)
			{
				for (int i = 0; i < 25; i++)
				{
					BotTarger_t player = Targets[ rand() % Targets.size() ];

					if (player.ci->infoValid)
					{
						sprintf_s<128>( szCommand, "callvote clientkick %i\n", player.ci->clientNum );
						trap_WriteConsole(szCommand);
						break;
					}
				}
				Sleep(100);
			}
		}
	}
}

void __stdcall KeyHook()
{
	MessageBox(NULL, "CrazyBot by BratokHR...", "Good!", NULL);
	while (true)
	{
		if (KEY_DOWN(VirtualKeyTable[(int)cFuncAimKey.iValue].uiKey))
			Aimkeypress = true;
		else
			Aimkeypress = false;

		Sleep(100);
	}
}

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		bot.hModule = hModule;

		DWORD n = GetModuleFileName( hModule, bot.path, MAX_PATH );
		for( char * p = &bot.path[ n ]; *p != '\\'; p-- )
			*p = '\0';

		//waveOutSetVolume(NULL, 0xFFFF); //0x7530

		Thread(KeyHook);
		Thread(NameStealer);
		Thread(AutoVote);

		for(; GFX_MODULE_Base == NULL; Sleep(320))
		GFX_MODULE_Base = (DWORD)LoadLibrary("gfx_d3d_mp_x86_s.dll");

		if(GFX_MODULE_Base)
		{
			o_EndFrame = (t_EndFrame)DetourFunction( (PBYTE)OFFSET_GFX_ENDFRAME, (PBYTE)h_EndFrame );
			o_CG_Obituary = (t_CG_Obituary)DetourFunction( (PBYTE)CG_OBITUARY, (PBYTE)h_CG_Obituary );
		}
		else
			MessageBox ( NULL, "GFX_D3D_MP_X86_S.dll not Found", "Error", MB_OK);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		DetourRemove( (PBYTE)o_EndFrame, (PBYTE)h_EndFrame );
		DetourRemove( (PBYTE)o_CG_Obituary, (PBYTE)h_CG_Obituary );
	}
	return TRUE;
}