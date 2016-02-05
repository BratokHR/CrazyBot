#include "stdafx.h"

vector<BotTarger_t> Targets;

#define FILTR_MINCROSS		0
#define FILTR_MINDISTANSE	1
#define FILTR_MAXDISTANSE	2

#define FILTR_CARZYAIM		0
#define FILTR_SILENTAIM		1
#define FILTR_AIMKEY		2

#define FILTR_BONEHELMET	0
#define FILTR_BONENOSE		1
#define FILTR_BONEJAW		2
#define FILTR_BONECHEST		3
#define FILTR_BONEPELVIS	4

#define FILTR_ESPALL		0
#define FILTR_ESPENEMY		1
#define FILTR_ESPFRIENDS	2

#define FILTR_BIG			1
#define FILTR_NORMAL		2
#define FILTR_SMALL			3
#define FILTR_BOLD			4

#define FILTR_CROSSCIRCLE	1
#define FILTR_CROSSSQUARE	2
#define FILTR_CROSSCROSS	3

bool Aimkeypress = false;

cRadar radar;

void AddTargets()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!clientinfo[i].infoValid || clientinfo[i].team == TEAM_SPECTATOR || clientinfo[i].clientNum == cg->clientNum)
			continue;

		BotTarger_t NewTarget;

		NewTarget.ci = &clientinfo[i];
		NewTarget.cent = &cg_entities[i];
		NewTarget.enemy = (NewTarget.ci->team == TEAM_FREE || NewTarget.ci->team != clientinfo[cg->clientNum].team);

		string bone = "j_jaw";
		if ((int)cFuncAimBoneTag.iValue == FILTR_BONEHELMET)
			bone = "j_helmet";
		else if ((int)cFuncAimBoneTag.iValue == FILTR_BONENOSE)
			bone = "j_levator_ri";
		else if ((int)cFuncAimBoneTag.iValue == FILTR_BONEJAW)
			bone = "j_jaw";
		else if ((int)cFuncAimBoneTag.iValue == FILTR_BONECHEST)
			bone = "j_spine3";
		else if ((int)cFuncAimBoneTag.iValue == FILTR_BONEPELVIS)
			bone = "torso_stabilizer";

		vec3_t head;
		GetBoneOriginID(NewTarget.cent, (char*)bone.c_str(), head);

		if(IsVisible(head)) NewTarget.visible = true;
		else NewTarget.visible = false;

		NewTarget.distance = distance(NewTarget.cent->lerpOrigin);

		vec3_t aimangle, trDelta;
		float CG_PING=(*ping)/50;
		VectorSubtract(NewTarget.cent->lerpOrigin, NewTarget.cent->lerpOrigin, trDelta);
		VectorMA(head,CG_PING,trDelta, head);
		GetAngleToOrigin( head, aimangle );

		NewTarget.aimangles[PITCH] = aimangle[PITCH] + ((int)cFuncAimOffsetX.iValue - 50)/10;
		NewTarget.aimangles[YAW] = aimangle[YAW] + ((int)cFuncAimOffsetY.iValue - 50)/10;
		NewTarget.aimangles[ROLL] = aimangle[ROLL];

		if(NewTarget.visible && NewTarget.enemy && NewTarget.ci->infoValid == qtrue && NewTarget.cent->currentValid == ET_PLAYER)
			NewTarget.valid = true;
		else NewTarget.valid = false;
		NewTarget.alive = (NewTarget.ci->infoValid == qtrue && NewTarget.cent->currentValid == ET_PLAYER);
		NewTarget.fov_x = fabs( NewTarget.aimangles[PITCH] ) * 2;
		NewTarget.fov_y = fabs( NewTarget.aimangles[YAW] ) * 2;
		Targets.push_back(NewTarget);
	}
}

void ClearTargets()
{
	if (!Targets.empty())
		Targets.clear();
}

//—ортирует по минимаьлной дистанции
bool SortPredicateA( BotTarger_t lhs, BotTarger_t rhs )
{
	return ( lhs.distance < rhs.distance );
}

//—ортирует по максимальной дистанции
bool SortPredicateC( BotTarger_t lhs, BotTarger_t rhs )
{
	return ( lhs.distance > rhs.distance );
}


//—ортирует по минимальному углу
bool SortPredicateB( BotTarger_t lhs, BotTarger_t rhs )
{
	float fLHS = ( lhs.aimangles[0] * lhs.aimangles[0] ) + ( lhs.aimangles[1] * lhs.aimangles[1] );
	float fRHS = ( rhs.aimangles[0] * rhs.aimangles[0] ) + ( rhs.aimangles[1] * rhs.aimangles[1] );

	return ( fLHS < fRHS );
}

//—ортирует таргеты
void SortTargets()
{
	if ((int)cFuncAimFilter.iValue == FILTR_MINDISTANSE)
		sort( Targets.begin(), Targets.end(), SortPredicateA );
	else if ((int)cFuncAimFilter.iValue == FILTR_MAXDISTANSE)
		sort( Targets.begin(), Targets.end(), SortPredicateC );
	else if ((int)cFuncAimFilter.iValue == FILTR_MINCROSS)
		sort( Targets.begin(), Targets.end(), SortPredicateB );
}

void GetBoneOriginID(centity_t *entity, char *bone, vec3_t origin)
{
	short Aimpoint = CG_GetTagNumber( bone );
	orientation_t head;
	CG_SetTagOrigin( entity, Aimpoint, &head);
	VectorCopy(head.origin, origin);
}

//==========================================================================
// AIMBOT
//==========================================================================
void Aimbot()
{
	if (!(bool)cFuncAimbot.iValue)
		return;
	if (!Targets.empty())
	{
		for (int i = 0; i < Targets.size(); i++)
		{
			if (Targets[i].valid && (Targets[i].fov_x < cFuncAimFov.iValue) && (Targets[i].fov_y < cFuncAimFov.iValue))
			{
				if ((int)cFuncAimType.iValue == FILTR_SILENTAIM)
				{
					cmd = input->GetUserCmd(input->currentCmdNum);
					oldcmd = input->GetUserCmd(input->currentCmdNum - 1);
 
					oldcmd->ServerTime += 1;
					if (GetAsyncKeyState(VK_LBUTTON)) {
						oldcmd->ViewAngle[0] = cmd->ViewAngle[0] + ANGLE2SHORT( Targets[i].aimangles[0] );
						oldcmd->ViewAngle[1] = cmd->ViewAngle[1] + ANGLE2SHORT( Targets[i].aimangles[1] ); 
					}
				}
				else if ((int)cFuncAimType.iValue == FILTR_CARZYAIM || ((int)cFuncAimType.iValue == FILTR_AIMKEY && Aimkeypress))
				{
					viewangles[PITCH] += Targets[i].aimangles[PITCH];
					viewangles[YAW]	+= Targets[i].aimangles[YAW];
					viewangles[ROLL] += Targets[i].aimangles[ROLL];
				}
				break;
			}
		}
	}
}

//==========================================================================
// ESP
//==========================================================================
//j_wrist_le - зап€стие
//j_wrist_ri - зап€стие
//j_brow_le - глаз
//j_brow_ri - глаз
//j_elbow_le - локоть
//j_elbow_ri - локоть
//j_clavicle_le - ключица
//j_clavicle_ri - ключица
//j_shoulder_le - плечо
//j_shoulder_ri - плечо
//j_neck - ше€
//j_head - голова
//j_helmet - шлем
//j_jaw - челюсть
//j_spine[1-4] - позвоночник
//j_knee_le - колено
//j_knee_ri - колено
//torso_stabilizer - таз
//j_levator_ri - нос
//j_hiptwist_le - бедро
//j_hiptwist_ri - бедро
//j_ankle_le - стопа
//j_ankle_ri - стопа
//parentj_mainroot - последн€€ часть скелета
//j_ball_le - конец пальцев ног
//j_ball_ri - конец пальцев ног
void DrawBone(centity_t* entity, char* Start, char* End, float *colour)
{
	vec2_t startOrg, endOrg;
	vec3_t boneStart, boneEnd;
	GetBoneOriginID(entity, Start, boneStart);
	GetBoneOriginID(entity, End, boneEnd);
	if (GetDistance(entity->lerpOrigin, boneStart) > 5 || GetDistance(entity->lerpOrigin, boneEnd) > 5)
		return;

	if (WorldToScreen(boneStart, startOrg))
	{
		if (WorldToScreen(boneEnd, endOrg))
		{
			Draw.Draw_Line(startOrg[0], startOrg[1], endOrg[0], endOrg[1], colour);
		}
	}
}

void Draw3DBox(BotTarger_t player)
{

}

void Esp()
{
	if (!Targets.empty())
	{
		vec4_t clEnemyVIS = { cFuncESPEnemyVISR.iValue/255.0f, cFuncESPEnemyVISG.iValue/255.0f, cFuncESPEnemyVISB.iValue/255.0f, 1.0f };
		vec4_t clEnemyINVIS = { cFuncESPEnemyUNVISR.iValue/255.0f, cFuncESPEnemyUNVISG.iValue/255.0f, cFuncESPEnemyUNVISB.iValue/255.0f, 1.0f };
		vec4_t clFriendyVIS = { cFuncESPFriendVISR.iValue/255.0f, cFuncESPFriendVISG.iValue/255.0f, cFuncESPFriendVISB.iValue/255.0f, 1.0f };
		vec4_t clFriendINVIS = { cFuncESPFriendUNVISR.iValue/255.0f, cFuncESPFriendUNVISG.iValue/255.0f, cFuncESPFriendUNVISB.iValue/255.0f, 1.0f };
		
		for (int i = 0; i < Targets.size(); i++)
		{
			if (!Targets[i].alive || (Targets[i].enemy && cFuncESPFilter.iValue == FILTR_ESPFRIENDS) || 
				(!Targets[i].enemy && cFuncESPFilter.iValue == FILTR_ESPENEMY) || (cg->snap->ps.clientNum == Targets[i].ci->clientNum)) //cg->snap->ps.clientNum != cg->clientNum
				continue;

			vec4_t colour;
			if (Targets[i].enemy)
			{
				if (Targets[i].visible)
					CopyVec4(colour, clEnemyVIS);
				else
					CopyVec4(colour, clEnemyINVIS);
			}
			else {
				if (Targets[i].visible)
					CopyVec4(colour, clFriendyVIS);
				else
					CopyVec4(colour, clFriendINVIS);
			}

			float	fov_x	= *(float*)((DWORD)GetModuleHandleA("gfx_d3d_mp_x86_s.dll") + 0x646488);
			float	fov_y	= *(float*)((DWORD)GetModuleHandleA("gfx_d3d_mp_x86_s.dll") + 0x64649C);

			if ((bool)cFuncESP3Dbox.iValue)
			{
				Draw3DBox(Targets[i]);
			}

			if ((bool)cFuncESP2Dbox.iValue)
			{
				vec3_t orgUP, orgDown;
				vec2_t crdUP, crdDown;
				GetBoneOriginID(Targets[i].cent, "j_helmet", orgUP);
				CopyVec3(orgDown, Targets[i].cent->lerpOrigin);
				if (WorldToScreen(orgUP, crdUP) && WorldToScreen(orgDown, crdDown))
				{
					float width = 400.0f;
					float x = crdDown[0]-((width / Targets[i].distance * fov_x)/2);
					float y = crdUP[1];
					float w = (width / Targets[i].distance * fov_x);
					float h = crdDown[1] - crdUP[1];
					Draw.Draw_Border(x, y, w, h, 2, colour);
				}
			}

			if ((bool)cFuncESPSkeleton.iValue)
			{
				DrawBone(Targets[i].cent, "j_head_end", "j_head", colour);
				DrawBone(Targets[i].cent, "j_head", "j_neck", colour);
				DrawBone(Targets[i].cent, "j_neck", "j_clavicle_le", colour);
				DrawBone(Targets[i].cent, "j_neck", "j_clavicle_ri", colour);

				DrawBone(Targets[i].cent, "j_clavicle_le", "j_shoulder_le", colour);
				DrawBone(Targets[i].cent, "j_shoulder_le", "j_elbow_le", colour);
				DrawBone(Targets[i].cent, "j_elbow_le", "j_wrist_le", colour);

				DrawBone(Targets[i].cent, "j_clavicle_ri", "j_shoulder_ri", colour);
				DrawBone(Targets[i].cent, "j_shoulder_ri", "j_elbow_ri", colour);
				DrawBone(Targets[i].cent, "j_elbow_ri", "j_wrist_ri", colour);

				DrawBone(Targets[i].cent, "j_neck", "j_spine4", colour);
				DrawBone(Targets[i].cent, "j_spine4", "j_spine3", colour);
				DrawBone(Targets[i].cent, "j_spine3", "j_spine2", colour);
				DrawBone(Targets[i].cent, "j_spine2", "j_spine1", colour);
				DrawBone(Targets[i].cent, "j_spine1", "torso_stabilizer", colour);

				DrawBone(Targets[i].cent, "torso_stabilizer", "j_hiptwist_le", colour);
				DrawBone(Targets[i].cent, "j_hiptwist_le", "j_knee_le", colour);
				DrawBone(Targets[i].cent, "j_knee_le", "j_ankle_le", colour);
				DrawBone(Targets[i].cent, "j_ankle_le", "j_ball_le", colour);

				DrawBone(Targets[i].cent, "torso_stabilizer", "j_hiptwist_ri", colour);
				DrawBone(Targets[i].cent, "j_hiptwist_ri", "j_knee_ri", colour);
				DrawBone(Targets[i].cent, "j_knee_ri", "j_ankle_ri", colour);
				DrawBone(Targets[i].cent, "j_ankle_ri", "j_ball_ri", colour);
			}

			if ((bool)cFuncESPLines.iValue)
			{
				vec2_t screen;
				vec3_t org;
				GetBoneOriginID(Targets[i].cent, "j_spine1", org);
				if(WorldToScreen(org, screen))
				{
					float x = cg->refdef.width/2;
					float y = cg->refdef.height;
					Draw.Draw_Line(x, y, screen[0], screen[1], colour, 1);
				}
			}

			LPSTR font = bot.fonts.Big;
			if (cFuncESPFont.iValue == FILTR_BIG)
				font = bot.fonts.Big;
			else if (cFuncESPFont.iValue == FILTR_NORMAL)
				font = bot.fonts.Normal;
			else if (cFuncESPFont.iValue == FILTR_SMALL)
				font = bot.fonts.Small;
			else if (cFuncESPFont.iValue == FILTR_BOLD)
				font = bot.fonts.Bold;
			vec3_t org_helmet; vec2_t screen1, screen2;
			GetBoneOriginID(Targets[i].cent, "j_helmet", org_helmet);
			if(WorldToScreen(org_helmet, screen1) && WorldToScreen(Targets[i].cent->lerpOrigin, screen2))
			{
				if ((bool)cFuncESPNames.iValue)
					Draw.Draw_Text(screen1[0], screen1[1], 0.8, colorWhite, F_CENTER, font, "%s", Targets[i].ci->name);
				if ((bool)cFuncESPDistance.iValue)
					Draw.Draw_Text(screen2[0], screen2[1], 0.9, colour, F_CENTER, font, "%im", (int)Targets[i].distance);
			}
		}
	}
}

//==========================================================================
// VISUAL
//==========================================================================
void Visual()
{
	if ((bool)cFuncVisualWH.iValue)Hook->MemoryWrite((void*)Wallhack, (void*)"\xC7\x44\x24\x14\x88\x00\x00", 7);
	else Hook->MemoryWrite((void*)Wallhack, (void*)"\xC7\x44\x24\x14\x80\x00\x00", 7);

	if ((bool)cFuncVisualGranade.iValue || (bool)cFuncVisualMG.iValue)
	{
		vec2_t screen;
		for (int i = 64; i < MAX_GENTITIES; i++)
		{
			if (WorldToScreen(cg_entities[i].lerpOrigin, screen))
			{
				if (cg_entities[i].currentState.eType == 4 && (bool)cFuncVisualGranade.iValue)
				{
					vec4_t colour;
					float dist = GetDistance(cg->refdef.vieworg, cg_entities[i].lerpOrigin);
					if (dist < 5)
					{
						Draw.Draw_Text(cg->refdef.width/2, 50, 2, colorRed, F_CENTER, bot.fonts.Normal, "GRANADE");
						CopyVec4(colour, colorRed);
					}
					else if (dist < 8)
						CopyVec4(colour, colorOrange);
					else CopyVec4(colour, colorGreen);
					Draw.Draw_Text(screen[0], screen[1]-20, 1.0, colour, F_CENTER, bot.fonts.Normal, "[ %im ]", (int)dist);
					Draw.Draw_Shader(screen[0]-25, screen[1]-25, 50, 50, colour, bot.shaders.GrenadeIcon);
				}
				
				if (cg_entities[i].currentState.eType == 9 && (bool)cFuncVisualMG.iValue)
				{
					Draw.Draw_Text(screen[0], screen[1], 1.2, colorCyan, F_CENTER, bot.fonts.Console, "MG");
				}
			}
		}
	}

	int x = cg->refdef.width/2;
	int y = cg->refdef.height/2;
	if (cFuncVisualCross.iValue == FILTR_CROSSCIRCLE)
		Draw.Draw_Shader(x-5, y-5, 10, 10, colorWhite, bot.shaders.RadarEnemy);
	else if (cFuncVisualCross.iValue == FILTR_CROSSCROSS)
	{
		Draw.Draw_Shader(x-1, y-5, 2, 10, colorGreen, bot.shaders.White);
		Draw.Draw_Shader(x-5, y-1, 10, 2, colorGreen, bot.shaders.White);
	}
	else if (cFuncVisualCross.iValue == FILTR_CROSSSQUARE)
	{
		Draw.Draw_Border(x-5, y-5, 10, 10, 1, colorGreen);
		Draw.Draw_Line(x-5, y-5, x+5, y+5, colorGreen);
		Draw.Draw_Line(x+5, y-5, x-5, y+5, colorGreen);
	}
}

//==========================================================================
// MISC
//==========================================================================
void Autoshoot( bool toggle )
{
	if( toggle )
	{
		StartAttack( );
		StopAttack( );
	}
		//ri->Cmd_ExecuteText( EXEC_INSERT, "+attack; wait 1; -attack" );
}

void Autosight( bool toggle )
{
	static bool bSighted = false;

	if( toggle )
	{
		trap_WriteConsole( "+speed" );
		bSighted = true;
	}
	else if( bSighted )
	{
		trap_WriteConsole( "-speed" );
		bSighted = false;
	}
}

void Misc()
{
	if (cFuncMiscNoRecoil.iValue) Hook->MemoryWrite((void*)NoRecoil, (void*)"\x75\x2C", 2);
	else Hook->MemoryWrite((void*)NoRecoil, (void*)"\x74\x2C", 2);

	clientInfo_t * ci = AimingAtClient( );
	if( ci)
	{
		if ((bool)cFuncVisualTargetInfo.iValue)
		{
			int x = cg->refdef.width/5;
			int y = cg->refdef.height/2;
			int w = 300;
			int h = 80;
			Draw.Draw_Box(x, y, w, 20, MainColor);
			Draw.Draw_Box(x, y+20, w, h, colorBlack_);
			Draw.Draw_Text(x+5, y+20, 0.8, colorWhite, F_LEFT, bot.fonts.Big, "TargetInfo");
			string team;
			if (ci->team == TEAM_ALLIES)
				team = "Allies";
			else if (ci->team == TEAM_AXIS)
				team = "Axis";
			else
				team = "Enemy...";
			Draw.Draw_Text(x+5, y+40, 1.2, colorWhite, F_LEFT, bot.fonts.Normal, "^2Name: ^7%s\n^1Num: ^7%i\n^3Team: ^7%s", ci->name, ci->clientNum, team.c_str());
		}

		if ((bool)cFuncAutoShoot.iValue && ci->team < TEAM_SPECTATOR && ( ci->team == TEAM_FREE || ci->team != clientinfo[ cg->clientNum ].team ))
		{
			keybd_event(VK_LBUTTON, 0, 0, 0);
			keybd_event(VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0);
		}
	}
}

void Cheats() 
{
	AddTargets();
	SortTargets();

    Aimbot();
	Esp();
	Visual();
	radar.perform();
	Misc();

	ClearTargets();
}