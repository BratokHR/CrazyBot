#include "stdafx.h"

cSettingsFile GSettings;

/*AIMBOT*/
CBoolCvar cFuncAimbot("Aimbot");
CBoolCvar cFuncAimKeyBool("Aimbot key bool");
CIntCvar cFuncAimOffsetX("Aimbot offset x");
CIntCvar cFuncAimOffsetY("Aimbot offset y");
CIntCvar cFuncAimBoneTag("Aimbot bone tag");
CIntCvar cFuncAimKey("Aimbot key");
CIntCvar cFuncAimType("Aimbot type");
CIntCvar cFuncAimFilter("Aimbot filter");
CIntCvar cFuncAimFov("Aimbot fov");
CFloatCvar cFuncAimSpeed("Aimbot speed aiming");
/*ESP*/
CBoolCvar cFuncESPLines("Esp lines");
CBoolCvar cFuncESP2Dbox("Esp 2d box");
CBoolCvar cFuncESP3Dbox("Esp 3d box");
CBoolCvar cFuncESPNames("Esp names");
CBoolCvar cFuncESPDistance("Esp distance");
CBoolCvar cFuncESPSkeleton("Esp skeleton");
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
CIntCvar cFuncESPFont("Esp font");
/*VISUAL*/
CBoolCvar cFuncVisualWH("Visual wallhack");
CBoolCvar cFuncVisualGranade("Visual granade indicator");
CBoolCvar cFuncVisualMG("Visual mg indicator");
CBoolCvar cFuncRadar("Radar");
CBoolCvar cFuncVisualTargetInfo("Misc target info");
CIntCvar cFuncVisualCross("Visual cross");
/*MISC*/
CBoolCvar cFuncMiscNoRecoil("Misc no recoil");
CBoolCvar cFuncMiscKillSound("Misc kill sound");
CBoolCvar cFuncMiscNameStealer("Misc name stealer");
CBoolCvar cFuncAutoShoot("Misc autoshoot");

void cSettingsFile::SaveSettings()
{
	string cfg = string(bot.path) + "\\crazybot.cfg";
	bot.InitSettings = true;

	/*AIMBOT*/
	cFuncAimbot.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimKeyBool.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimOffsetX.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimOffsetY.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimBoneTag.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimKey.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimType.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimFilter.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimFov.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
	cFuncAimSpeed.SaveCvar("Aimbot", (LPSTR)cfg.c_str());
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
	cFuncMiscKillSound.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncMiscNameStealer.SaveCvar("Misc", (LPSTR)cfg.c_str());
	cFuncAutoShoot.SaveCvar("Misc", (LPSTR)cfg.c_str());
}

void cSettingsFile::LoadSettings()
{
	string cfg = string(bot.path) + "\\crazybot.cfg";
	if (access((char*)cfg.c_str(), 0) != -1) bot.InitSettings = true;

	/*AIMBOT*/
	cFuncAimbot.LoadCvar("Aimbot", false, (LPSTR)cfg.c_str());
	cFuncAimKeyBool.LoadCvar("Aimbot", false, (LPSTR)cfg.c_str());
	cFuncAimOffsetX.LoadCvar("Aimbot", 50, (LPSTR)cfg.c_str());
	cFuncAimOffsetY.LoadCvar("Aimbot", 50, (LPSTR)cfg.c_str());
	cFuncAimBoneTag.LoadCvar("Aimbot", 2, (LPSTR)cfg.c_str());
	cFuncAimKey.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimType.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimFilter.LoadCvar("Aimbot", 0, (LPSTR)cfg.c_str());
	cFuncAimFov.LoadCvar("Aimbot", 360, (LPSTR)cfg.c_str());
	cFuncAimSpeed.LoadCvar("Aimbot", 15.0f, (LPSTR)cfg.c_str());
	/*ESP*/
	cFuncESPLines.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
	cFuncESP2Dbox.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
	cFuncESP3Dbox.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
	cFuncESPNames.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
	cFuncESPDistance.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
	cFuncESPSkeleton.LoadCvar("Esp", false, (LPSTR)cfg.c_str());
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
	cFuncESPFont.LoadCvar("Esp", 1, (LPSTR)cfg.c_str());
	/*VISUAL*/
	cFuncVisualWH.LoadCvar("Visual", false, (LPSTR)cfg.c_str());
	cFuncVisualGranade.LoadCvar("Visual", false, (LPSTR)cfg.c_str());
	cFuncVisualMG.LoadCvar("Visual", false, (LPSTR)cfg.c_str());
	cFuncRadar.LoadCvar("Radar", false, (LPSTR)cfg.c_str());
	cFuncVisualTargetInfo.LoadCvar("Visual", false, (LPSTR)cfg.c_str());
	cFuncVisualCross.LoadCvar("Visual", 0, (LPSTR)cfg.c_str());
	/*MISC*/
	cFuncMiscNoRecoil.LoadCvar("Misc", false, (LPSTR)cfg.c_str());
	cFuncMiscKillSound.LoadCvar("Misc", false, (LPSTR)cfg.c_str());
	cFuncMiscNameStealer.LoadCvar("Misc", false, (LPSTR)cfg.c_str());
	cFuncAutoShoot.LoadCvar("Misc", false, (LPSTR)cfg.c_str());
}

void cSettingsFile::ResetSettings()
{
	//Aimbot
	cFuncAimbot.bValue = false;
	cFuncAimKeyBool.bValue = false;
	cFuncAimOffsetX.iValue = 50;
	cFuncAimOffsetY.iValue = 50;
	cFuncAimKey.iValue = 10;
	cFuncAimType.iValue = 0;
	cFuncAimFilter.iValue = 1;
	cFuncAimFov.iValue = 360;
	cFuncAimSpeed.fValue = 15.0f;
	//ESP
	cFuncESPLines.bValue = false;
	cFuncESP2Dbox.bValue = false;
	cFuncESP3Dbox.bValue = false;
	cFuncESPNames.bValue = false;
	cFuncESPDistance.bValue = false;
	cFuncESPSkeleton.bValue = false;
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
	cFuncESPFont.iValue = 1;
	//Visual
	cFuncVisualWH.bValue = false;
	cFuncVisualGranade.bValue = false;
	cFuncVisualMG.bValue = false;
	cFuncRadar.bValue = false;
	cFuncVisualTargetInfo.bValue = false;
	cFuncVisualCross.iValue = 0;
	//Misc
	cFuncMiscNoRecoil.bValue = false;
	cFuncMiscKillSound.bValue = false;
	cFuncMiscNameStealer.bValue = false;
	cFuncAutoShoot.bValue = false;
}