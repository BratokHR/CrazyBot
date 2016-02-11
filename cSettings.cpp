#include "stdafx.h"

cSettingsFile GSettings;

/*AIMBOT*/
CIntCvar cFuncAimbot("Aimbot");
CIntCvar cFuncAimOffsetX("Aimbot offset x");
CIntCvar cFuncAimOffsetY("Aimbot offset y");
CIntCvar cFuncAimBoneTag("Aimbot bone tag");
CIntCvar cFuncAimKey("Aimbot key");
CIntCvar cFuncAimType("Aimbot type");
CIntCvar cFuncAimFilter("Aimbot filter");
CIntCvar cFuncAimFov("Aimbot fov");
/*ESP*/
CIntCvar cFuncESPLines("Esp lines");
CIntCvar cFuncESP2Dbox("Esp 2d box");
CIntCvar cFuncESP3Dbox("Esp 3d box");
CIntCvar cFuncESPNames("Esp names");
CIntCvar cFuncESPDistance("Esp distance");
CIntCvar cFuncESPEnemyVISR("Esp enemy visible R");
CIntCvar cFuncESPEnemyVISG("Esp enemy visible G");
CIntCvar cFuncESPEnemyVISB("Esp enemy visible B");
CIntCvar cFuncESPEnemyUNVISR("Esp enemy unvisible R");
CIntCvar cFuncESPEnemyUNVISG("Esp enemy unvisible G");
CIntCvar cFuncESPEnemyUNVISB("Esp enemy unvisible B");
CIntCvar cFuncESPFriendVISR("Esp friend visible R");
CIntCvar cFuncESPFriendVISG("Esp friend visible G");
CIntCvar cFuncESPFriendVISB("Esp friend visible B");
CIntCvar cFuncESPFriendUNVISR("Esp friend unvisible R");
CIntCvar cFuncESPFriendUNVISG("Esp friend unvisible G");
CIntCvar cFuncESPFriendUNVISB("Esp friend unvisible B");
CIntCvar cFuncESPFilter("Esp filter");
CIntCvar cFuncESPSkeleton("Esp skeleton");
CIntCvar cFuncESPFont("Esp font");
/*VISUAL*/
CIntCvar cFuncVisualWH("Visual wallhack");
CIntCvar cFuncVisualCross("Visual cross");
CIntCvar cFuncVisualGranade("Visual granade indicator");
CIntCvar cFuncVisualMG("Visual mg indicator");
CIntCvar cFuncRadar("Radar");
CIntCvar cFuncVisualTargetInfo("Misc target info");
/*MISC*/
CIntCvar cFuncMiscNoRecoil("Misc no recoil");
CIntCvar cFuncMiscKillSpam("Misc kill spam");
CIntCvar cFuncMiscKillSound("Misc kill sound");
CIntCvar cFuncMiscNameStealer("Misc name stealer");
CIntCvar cFuncAutoVote("Misc auto vote");
CIntCvar cFuncAutoShoot("Misc autoshoot");

void cSettingsFile::SaveSettings()
{
	string cfg = string(bot.path) + "\\crazybot.cfg";
	/*AIMBOT*/
	cFuncAimbot.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimOffsetX.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimOffsetY.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimBoneTag.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimKey.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimType.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimFilter.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimFov.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	/*ESP*/
	cFuncESPLines.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESP2Dbox.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESP3Dbox.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPNames.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPDistance.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyVISR.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyVISG.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyVISB.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISR.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISG.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISB.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendVISR.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendVISG.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendVISB.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISR.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISG.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISB.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFilter.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPSkeleton.SaveCvar("Esp", (LPSTR)cfg.c_str());
	cFuncESPFont.SaveCvar("Esp", (LPSTR)cfg.c_str());
	/*VISUAL*/
	cFuncVisualWH.SaveCvar("Visual", (LPSTR)cfg.c_str());
	cFuncVisualCross.SaveCvar("Visual", (LPSTR)cfg.c_str());
	cFuncVisualGranade.SaveCvar("Visual", (LPSTR)cfg.c_str());
	cFuncVisualMG.SaveCvar("Visual", (LPSTR)cfg.c_str());
	cFuncRadar.SaveCvar("Radar", (LPSTR)cfg.c_str());
	cFuncVisualTargetInfo.SaveCvar("Visual", (LPSTR)cfg.c_str());
	/*MISC*/
	cFuncMiscNoRecoil.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncMiscKillSpam.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncMiscKillSound.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncMiscNameStealer.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncAutoVote.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncAutoShoot.SaveCvar("Misc", (LPSTR)cfg.c_str());
}

void cSettingsFile::LoadSettings()
{
	string cfg = string(bot.path) + "\\crazybot.cfg";
	/*AIMBOT*/
	cFuncAimbot.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimOffsetX.LoadCvar("Aimbot", 50, (LPSTR)cfg.c_str());
	cFuncAimOffsetY.LoadCvar("Aimbot", 50, (LPSTR)cfg.c_str());
	cFuncAimBoneTag.LoadCvar("Aimbot", 2, (LPSTR)cfg.c_str());
	cFuncAimKey.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimType.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimFilter.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimFov.LoadCvar("Aimbot", 360, (LPSTR)cfg.c_str());
	/*ESP*/
	cFuncESPLines.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESP2Dbox.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESP3Dbox.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESPNames.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESPDistance.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESPEnemyVISR.LoadCvar("Esp", 229, (LPSTR)cfg.c_str());
	cFuncESPEnemyVISG.LoadCvar("Esp", 3, (LPSTR)cfg.c_str());
	cFuncESPEnemyVISB.LoadCvar("Esp", 3, (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISR.LoadCvar("Esp", 229, (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISG.LoadCvar("Esp", 197, (LPSTR)cfg.c_str());
	cFuncESPEnemyUNVISB.LoadCvar("Esp", 3, (LPSTR)cfg.c_str());
	cFuncESPFriendVISR.LoadCvar("Esp", 159, (LPSTR)cfg.c_str());
	cFuncESPFriendVISG.LoadCvar("Esp", 229, (LPSTR)cfg.c_str());
	cFuncESPFriendVISB.LoadCvar("Esp", 3, (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISR.LoadCvar("Esp", 3, (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISG.LoadCvar("Esp", 201, (LPSTR)cfg.c_str());
	cFuncESPFriendUNVISB.LoadCvar("Esp", 229, (LPSTR)cfg.c_str());
	cFuncESPFilter.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESPSkeleton.LoadCvar("Esp", 0, (LPSTR)cfg.c_str());
	cFuncESPFont.LoadCvar("Esp", 1, (LPSTR)cfg.c_str());
	/*VISUAL*/
	cFuncVisualWH.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	cFuncVisualCross.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	cFuncVisualGranade.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	cFuncVisualMG.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	cFuncRadar.LoadCvar("Radar", 0, (LPSTR)cfg.c_str());
	cFuncVisualTargetInfo.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	/*MISC*/
	cFuncMiscNoRecoil.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
	cFuncMiscKillSpam.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
	cFuncMiscKillSound.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
	cFuncMiscNameStealer.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
	cFuncAutoVote.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
	cFuncAutoShoot.LoadCvar("Misc", 0, (LPSTR)cfg.c_str());
}

void cSettingsFile::ResetSettings()
{
	//Aimbot
	cFuncAimBoneTag.iValue = 2;
	cFuncAimOffsetX.iValue = 50;
	cFuncAimOffsetY.iValue = 50;
	cFuncAimKey.iValue = 0;
	cFuncAimType.iValue = 0;
	cFuncAimFilter.iValue = 0;
	cFuncAimbot.iValue = false;
	cFuncAimFov.iValue = 360;
	//ESP
	cFuncESPLines.iValue = false;
	cFuncESP2Dbox.iValue = false;
	cFuncESP3Dbox.iValue = false;
	cFuncESPNames.iValue = false;
	cFuncESPDistance.iValue = false;
	cFuncESPEnemyVISR.iValue = 229;
	cFuncESPEnemyVISG.iValue = 3;
	cFuncESPEnemyVISB.iValue = 3;
	cFuncESPEnemyUNVISR.iValue = 229;
	cFuncESPEnemyUNVISG.iValue = 197;
	cFuncESPEnemyUNVISB.iValue = 3;
	cFuncESPFriendVISR.iValue = 159;
	cFuncESPFriendVISG.iValue = 229;
	cFuncESPFriendVISB.iValue = 3;
	cFuncESPFriendUNVISR.iValue = 3;
	cFuncESPFriendUNVISG.iValue = 201;
	cFuncESPFriendUNVISB.iValue = 229;
	cFuncESPFilter.iValue = 0;
	cFuncESPSkeleton.iValue = false;
	cFuncESPFont.iValue = 1;
	//Visual
	cFuncVisualWH.iValue = false;
	cFuncVisualCross.iValue = 0;
	cFuncVisualGranade.iValue = false;
	cFuncVisualMG.iValue = false;
	cFuncRadar.iValue = false;
	cFuncVisualTargetInfo.iValue = false;
	//Misc
	cFuncMiscNoRecoil.iValue = false;
	cFuncMiscKillSpam.iValue = false;
	cFuncMiscKillSound.iValue = false;
	cFuncMiscNameStealer.iValue = false;
	cFuncAutoVote.iValue = false;
	cFuncAutoShoot.iValue = false;
}