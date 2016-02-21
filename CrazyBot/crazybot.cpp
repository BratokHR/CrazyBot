#include "stdafx.h"

void AddTargets()
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!bot.clientinfo[i].infoValid || bot.clientinfo[i].team == TEAM_SPECTATOR || bot.clientinfo[i].clientNum == bot.cg->clientNum)
			continue;

		BotTarger_t NewTarget;

		NewTarget.ci = &bot.clientinfo[i];
		NewTarget.cent = &bot.cg_entities[i];
		NewTarget.enemy = (NewTarget.ci->team == TEAM_FREE || NewTarget.ci->team != bot.clientinfo[bot.cg->clientNum].team);
		NewTarget.distance = distance(NewTarget.cent->lerpOrigin);
		NewTarget.alive = (NewTarget.ci->infoValid == qtrue && NewTarget.cent->currentValid == ET_PLAYER);

		string bone;
		switch ((int)cFuncAimBoneTag.iValue)
		{
		case FILTR_BONEHELMET:
			bone = "j_helmet";
			break;
		case FILTR_BONECHEST:
			bone = "j_spine3";
			break;
		case FILTR_BONEPELVIS:
			bone = "pelvis";
			break;
		default:
			bone = "j_jaw";
			break;
		}

		vec3_t head;
		GetBoneOriginID(NewTarget.cent, (char*)bone.c_str(), head);

		if(IsVisible(head)) NewTarget.visible = true;
		else NewTarget.visible = false;

		vec3_t aimangle, trDelta;
		VectorMA( head, (*bot.ping*0.3)/300, NewTarget.cent->currentState.pos.trDelta, trDelta );
		VectorCopy(trDelta, head);

		GetAngleToOrigin( head, aimangle );

		NewTarget.aimangles[PITCH] = aimangle[PITCH] + ((int)cFuncAimOffsetX.iValue - 50)/10;
		NewTarget.aimangles[YAW] = aimangle[YAW] + ((int)cFuncAimOffsetY.iValue - 50)/10;
		NewTarget.aimangles[ROLL] = aimangle[ROLL];

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
static bool SortPredicateA( BotTarger_t lhs, BotTarger_t rhs )
{
	return ( lhs.distance < rhs.distance );
}

//—ортирует по максимальной дистанции
static bool SortPredicateC( BotTarger_t lhs, BotTarger_t rhs )
{
	return ( lhs.distance > rhs.distance );
}


//—ортирует по минимальному углу
static bool SortPredicateB( BotTarger_t lhs, BotTarger_t rhs )
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
void HumanAim(BotTarger_t *target)
{
	float fDivisions = cFuncAimSpeed.fValue; //15
	float fFrequency = 1.0f; //1
	float fAmplitude = 5.0f; //5

	static bool		bAiming			= false;
	static int		iAimed			= 0;
	static float	fTotalPitch		= 0.0f;
	static float	fTotalYaw		= 0.0f;
	static float	fResultant		= 0.0f;
	static float	fRoll			= 0.0f;
	static float	fCurrent		= 0.0f;
	static float	fCurrentPitch	= 0.0f;
	static float	fCurrentYaw		= 0.0f;
	static float	fLastPitch		= 0.0f;
	static float	fLastYaw		= 0.0f;

	if( bAiming )
	{
		fCurrent		+= ( fResultant   / fDivisions );
		fCurrentPitch	+= ( fTotalPitch  / fDivisions );
		fCurrentYaw		+= ( fTotalYaw    / fDivisions );

		fAmplitude = ( ( fAmplitude - 0.05f ) * ( fResultant / 100.0f ) ) + 0.05f;
		float fSin		= sin( ( fCurrent / fResultant ) * ( fFrequency * M_PI ) ) * fAmplitude;
		float fNewPitch	= fCurrentPitch + ( fSin * cos( fRoll ) );
		float fNewYaw	= fCurrentYaw   + ( fSin * sin( fRoll ) );

		bot.viewangles[PITCH] += ( fNewPitch - fLastPitch );
		bot.viewangles[YAW]   += ( fNewYaw   - fLastYaw   );

		fLastPitch = fNewPitch;
		fLastYaw   = fNewYaw;

		iAimed++;

		if( iAimed >= fDivisions )
		{
			bAiming = false;
			if (cFuncAutoShoot.bValue)
				Shoot = true;
		}
	}
	else
	{
		fTotalPitch		= target->aimangles[PITCH];
		fTotalYaw		= target->aimangles[YAW];
		fResultant		= sqrt( ( fTotalPitch * fTotalPitch ) + ( fTotalYaw * fTotalYaw ) );
		fRoll			= atan( fTotalPitch / fTotalYaw );
		fCurrent		= 0.0f;
		fCurrentPitch	= 0.0f;
		fCurrentYaw		= 0.0f;
		fLastPitch		= 0.0f;
		fLastYaw		= 0.0f;
		bAiming			= true;
		iAimed			= 0;
	}
}

void Aimbot()
{
	if (!cFuncAimbot.bValue)
		return;
	if (!Targets.empty())
	{
		for (int i = 0; i < Targets.size(); i++)
		{
			if (Targets[i].enemy && Targets[i].alive && Targets[i].visible && (Targets[i].fov_x < cFuncAimFov.iValue) && (Targets[i].fov_y < cFuncAimFov.iValue))
			{
				bool keyPress = ((cFuncAimKeyBool.bValue && Aimkeypress) || !cFuncAimKeyBool.bValue);

				if (cFuncAimType.iValue == FILTR_AUTOAIM && keyPress)
				{
					bot.viewangles[PITCH] += Targets[i].aimangles[PITCH];
					bot.viewangles[YAW]	+= Targets[i].aimangles[YAW];
					bot.viewangles[ROLL] += Targets[i].aimangles[ROLL];
					if (cFuncAutoShoot.bValue)
						Shoot = true;
				}
				else if (cFuncAimType.iValue == FILTR_HUMANAIM && keyPress)
				{
					HumanAim(&Targets[i]);
				}
				else if (cFuncAimType.iValue == FILTR_SILENTAIM && keyPress)
				{
					bot.cmd = bot.input->GetUserCmd(bot.input->currentCmdNum);
					bot.oldcmd = bot.input->GetUserCmd(bot.input->currentCmdNum - 1);
					*bot.oldcmd = *bot.cmd;
					bot.cmd->ServerTime += 1;
					bot.input->currentCmdNum++;

					bot.cmd->ViewAngle[0] += ANGLE2SHORT( Targets[i].aimangles[0] );
					bot.cmd->ViewAngle[1] += ANGLE2SHORT( Targets[i].aimangles[1] );
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
	int maxdist = 2; // If the player is not the bone, the line tends to be the center of the map.
	if (GetDistance(entity->lerpOrigin, boneStart) > maxdist || GetDistance(entity->lerpOrigin, boneEnd) > maxdist)
		return;

	if (WorldToScreen(boneStart, startOrg))
	{
		if (WorldToScreen(boneEnd, endOrg))
		{
			Draw.Line(startOrg[0], startOrg[1], endOrg[0], endOrg[1], colour);
		}
	}
}

void minDistance(centity_t *cent, vec3_t A, vec3_t B, vec3_t *O)
{
	float a = GetDistanceXY(cent->lerpOrigin, A);
	float b = GetDistanceXY(cent->lerpOrigin, B);

	if (a > b)
		VectorCopy(A, *O);
	else
		VectorCopy(B, *O);
}

void Draw3DBox(BotTarger_t player, vec4_t colour)
{
	vec3_t up, down, front1, front2, front, backside1, backside2, backside, left1, left2, left, right1, right2, right;
	vec2_t coords1[4], coords2[4];

	GetBoneOriginID(player.cent, "j_helmet", up);
	VectorCopy(player.cent->lerpOrigin, down);
	GetBoneOriginID(player.cent, "j_wrist_le", front1);
	GetBoneOriginID(player.cent, "j_wrist_ri", front2);
	GetBoneOriginID(player.cent, "j_ankle_le", backside1);
	GetBoneOriginID(player.cent, "j_ankle_ri", backside2);
	GetBoneOriginID(player.cent, "j_shoulder_le", left1);
	GetBoneOriginID(player.cent, "j_elbow_le", left2);
	GetBoneOriginID(player.cent, "j_shoulder__le", right1);
	GetBoneOriginID(player.cent, "j_elbow_ri", right2);

	minDistance(player.cent, front1, front2, &front);
	minDistance(player.cent, backside1, backside2, &backside);
	minDistance(player.cent, left1, left2, &left);
	minDistance(player.cent, right1, right2, &right);

	float distFront = GetDistanceXY(down, front);
	float distBack = GetDistanceXY(down, backside);
	float distLeft = GetDistanceXY(down, left);
	float distRight = GetDistanceXY(down, right);
	float distUp = up[2] - down[2];
	
	float hypotenuse = sqrt((distLeft*distLeft)+(distFront*distFront));
	float angle = RAD2DEG(atan(distLeft/distFront));
	if (!WorldToScreen3D(player.cent, coords1[0], distUp, -angle, hypotenuse)) return;
	if (!WorldToScreen3D(player.cent, coords2[0], 0, -angle, hypotenuse)) return;

	hypotenuse = sqrt((distRight*distRight)+(distFront*distFront));
	angle = RAD2DEG(atan(distRight/distFront));
	if (!WorldToScreen3D(player.cent, coords1[1], distUp, angle, hypotenuse)) return;
	if (!WorldToScreen3D(player.cent, coords2[1], 0, angle, hypotenuse)) return;

	hypotenuse = sqrt((distRight*distRight)+(distBack*distBack));
	angle = RAD2DEG(atan(distBack/distRight));
	if (!WorldToScreen3D(player.cent, coords1[2], distUp, angle+90, hypotenuse)) return;
	if (!WorldToScreen3D(player.cent, coords2[2], 0, angle+90, hypotenuse)) return;

	hypotenuse = sqrt((distLeft*distLeft)+(distBack*distBack));
	angle = RAD2DEG(atan(distBack/distLeft));
	if (!WorldToScreen3D(player.cent, coords1[3], distUp, -angle-90, hypotenuse)) return;
	if (!WorldToScreen3D(player.cent, coords2[3], 0, -angle-90, hypotenuse)) return;

	Draw.BorderLine(coords1[0], coords1[1], coords1[2], coords1[3], colour, 1);
	Draw.BorderLine(coords2[0], coords2[1], coords2[2], coords2[3], colour, 1);
	Draw.BorderLine(coords1[0], coords2[0], coords2[1], coords1[1], colour, 1);
	Draw.BorderLine(coords1[2], coords2[2], coords2[3], coords1[3], colour, 1);
}

string strip_color(string strip)
{
	regex pattern("\\^\\d");
	strip = regex_replace(strip, pattern, "");
	return strip;
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
				(!Targets[i].enemy && cFuncESPFilter.iValue == FILTR_ESPENEMY) || (bot.cg->snap->ps.clientNum == Targets[i].ci->clientNum))
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

			float	fov_x	= *(float*)((DWORD)GetModuleHandleA("gfx_d3d_mp_x86_s.dll") + bot.Fov_x);

			if (cFuncESP3Dbox.bValue)
			{
				Draw3DBox(Targets[i], colour);
			}

			if (cFuncESP2Dbox.bValue)
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
					Draw.Border(x, y, w, h, 2, colour);
				}
			}

			if (cFuncESPSkeleton.bValue)
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

			if (cFuncESPLines.bValue)
			{
				vec2_t screen;
				vec3_t org;
				GetBoneOriginID(Targets[i].cent, "j_spine1", org);
				if(WorldToScreen(org, screen))
				{
					float x = bot.cg->refdef.width/2;
					float y = bot.cg->refdef.height;
					Draw.Line(x, y, screen[0], screen[1], colour, 1);
				}
			}

			LPSTR font;
			switch (cFuncESPFont.iValue)
			{
			case FILTR_BIG:
				font = bot.fonts.Big;
				break;
			case FILTR_NORMAL:
				font = bot.fonts.Normal;
				break;
			case FILTR_SMALL:
				font = bot.fonts.Small;
				break;
			case FILTR_BOLD:
				font = bot.fonts.Bold;
			default:
				font = bot.fonts.Big;
				break;
			}

			vec3_t org_helmet; vec2_t screen1, screen2;
			GetBoneOriginID(Targets[i].cent, "j_helmet", org_helmet);
			if(WorldToScreen(org_helmet, screen1) && WorldToScreen(Targets[i].cent->lerpOrigin, screen2))
			{
				string name = strip_color(string(Targets[i].ci->name));
				name = strip_color(name);

				if (cFuncESPNames.bValue)
					Draw.Text(screen1[0], screen1[1], 0.8, colour, F_CENTER, font, "%s", name.c_str());
				if (cFuncESPDistance.bValue)
					Draw.Text(screen2[0], screen2[1], 0.9, colour, F_CENTER, font, "%im", (int)Targets[i].distance);
			}
		}
	}
}

//==========================================================================
// VISUAL
//==========================================================================
void Visual()
{
	if (cFuncVisualWH.bValue)Hook->MemoryWrite((void*)bot.Wallhack, (void*)"\xC7\x44\x24\x14\x88\x00\x00", 7);
	else Hook->MemoryWrite((void*)bot.Wallhack, (void*)"\xC7\x44\x24\x14\x80\x00\x00", 7);

	if (cFuncVisualGranade.bValue || cFuncVisualMG.bValue)
	{
		vec2_t screen;
		for (int i = 64; i < MAX_GENTITIES; i++)
		{
			if (WorldToScreen(bot.cg_entities[i].lerpOrigin, screen))
			{
				if (bot.cg_entities[i].currentState.eType == 4 && cFuncVisualGranade.bValue)
				{
					vec4_t colour;
					float dist = GetDistance(bot.cg->refdef.vieworg, bot.cg_entities[i].lerpOrigin);
					if (dist < 5)
					{
						Draw.Text(bot.cg->refdef.width/2, 50, 2, colorRed, F_CENTER, bot.fonts.Normal, "GRANADE");
						CopyVec4(colour, colorRed);
					}
					else if (dist < 8)
						CopyVec4(colour, colorOrange);
					else CopyVec4(colour, colorGreen);
					Draw.Text(screen[0], screen[1]-20, 1.0, colour, F_CENTER, bot.fonts.Normal, "[ %im ]", (int)dist);
					Draw.Shader(screen[0]-25, screen[1]-25, 50, 50, colour, bot.shaders.GrenadeIcon);
				}
				
				if (bot.cg_entities[i].currentState.eType == 9 && cFuncVisualMG.bValue)
				{
					Draw.Text(screen[0], screen[1], 1.2, colorCyan, F_CENTER, bot.fonts.Console, "MG");
				}
			}
		}
	}

	int x = bot.cg->refdef.width/2;
	int y = bot.cg->refdef.height/2;
	if (cFuncVisualCross.iValue == FILTR_CROSSCIRCLE)
		Draw.Shader(x-5, y-5, 10, 10, colorWhite, bot.shaders.RadarEnemy);
	else if (cFuncVisualCross.iValue == FILTR_CROSSCROSSBIG)
	{
		Draw.Shader(x-1, y-25, 2, 50, colorYellow, bot.shaders.White);
		Draw.Shader(x-25, y-1, 50, 2, colorYellow, bot.shaders.White);

		Draw.Shader(x-1, y-15, 2, 8, colorBlack, bot.shaders.White);
		Draw.Shader(x+7, y-1, 8, 2, colorBlack, bot.shaders.White);
		Draw.Shader(x-1, y+7, 2, 8, colorBlack, bot.shaders.White);
		Draw.Shader(x-15, y-1, 8, 2, colorBlack, bot.shaders.White);
	}
	else if (cFuncVisualCross.iValue == FILTR_CROSSCROSSSMALL)
	{
		Draw.Shader(x-1, y-8, 2, 16, colorYellow, bot.shaders.White);
		Draw.Shader(x-8, y-1, 16, 2, colorYellow, bot.shaders.White);
	}
	else if (cFuncVisualCross.iValue == FILTR_CROSSSQUARE)
	{
		int size = 15, leng = 5;
		Draw.Shader(x-size, y-size, leng, 2, colorGreen, bot.shaders.White);
		Draw.Shader(x-size, y-size, 2, leng, colorGreen, bot.shaders.White);

		Draw.Shader(x+(size-leng), y-size, leng, 2, colorGreen, bot.shaders.White);
		Draw.Shader(x+size, y-size, 2, leng, colorGreen, bot.shaders.White);

		Draw.Shader(x+(size-leng), y+size, leng+2, 2, colorGreen, bot.shaders.White);
		Draw.Shader(x+size, y+(size-leng), 2, leng, colorGreen, bot.shaders.White);

		Draw.Shader(x-size, y+size, leng, 2, colorGreen, bot.shaders.White);
		Draw.Shader(x-size, y+(size-leng), 2, leng, colorGreen, bot.shaders.White);

		Draw.Shader(x-2, y-2, 4, 4, colorGreen, bot.shaders.White);
	}
}

//==========================================================================
// MISC
//==========================================================================
void Misc()
{
	if (cFuncMiscNoRecoil.bValue) Hook->MemoryWrite((void*)bot.NoRecoil, (void*)"\x75\x2C", 2);
	else Hook->MemoryWrite((void*)bot.NoRecoil, (void*)"\x74\x2C", 2);

	clientInfo_t * ci = AimingAtClient( );
	if( ci)
	{
		if (cFuncVisualTargetInfo.bValue)
		{
			int x = bot.cg->refdef.width/5;
			int y = bot.cg->refdef.height/2;
			int w = 300;
			int h = 80;
			Draw.Box(x, y, w, 20, MainColor);
			Draw.Box(x, y+20, w, h, colorBlack_);
			Draw.Text(x+5, y+20, 0.8, colorWhite, F_LEFT, bot.fonts.Big, "TargetInfo");
			string team;
			if (ci->team == TEAM_ALLIES)
				team = "Allies";
			else if (ci->team == TEAM_AXIS)
				team = "Axis";
			else
				team = "Enemy...";
			Draw.Text(x+5, y+40, 1.2, colorWhite, F_LEFT, bot.fonts.Normal, "^2Name: ^7%s\n^1Num: ^7%i\n^3Team: ^7%s", ci->name, ci->clientNum, team.c_str());
		}
	}
}

void Autoshoot()
{
	if (Targets.empty() || !cFuncAutoShoot.bValue)
		return;

	clientInfo_t * ci = AimingAtClient( );
	if(ci && ci->team < TEAM_SPECTATOR && ( ci->team == TEAM_FREE || ci->team != bot.clientinfo[ bot.cg->clientNum ].team ))
	{
		Shoot = true;
		return;
	}

	for (int i = 0; i < Targets.size(); i++)
	{
		if (!Targets[i].enemy || !Targets[i].visible || !Targets[i].ci->infoValid || !Targets[i].alive)
			continue;

		if (cFuncAimbot.bValue && (int)cFuncAimType.iValue == FILTR_SILENTAIM && (Targets[i].fov_x < cFuncAimFov.iValue) && (Targets[i].fov_y < cFuncAimFov.iValue))
		{
			Shoot = true;
			return;
		}

		vec3_t vOutAnkle, vOutHelmet;
		vec2_t fScreenAnkle, fScreenHelmet;
		GetBoneOriginID(Targets[i].cent, "j_head", vOutHelmet);
		GetBoneOriginID(Targets[i].cent, "j_ankle_ri", vOutAnkle);

		if (WorldToScreen(vOutAnkle, fScreenAnkle) && WorldToScreen(vOutHelmet, fScreenHelmet))
		{
			float RectYoffset = ((fScreenAnkle[1]+35) - fScreenHelmet[1]);
			float RectWidth = (RectYoffset/3);
			float RectWidthPos = (fScreenHelmet[0] - (RectWidth/2));
			int ScreenCenterX = bot.cg->refdef.width/2;
			int ScreenCenterY = bot.cg->refdef.height/2;

			if((ScreenCenterX >= RectWidthPos && ScreenCenterX <= RectWidthPos+RectWidth) && (ScreenCenterY >= fScreenHelmet[1]-(RectYoffset/6) && ScreenCenterY <= fScreenAnkle[1])) {
				if (cFuncAutoShoot.bValue) Shoot = true;
			}
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
	Radar.perform();
	Misc();
	Autoshoot();

	ClearTargets();
}