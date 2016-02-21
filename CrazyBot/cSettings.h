#pragma once

class CBoolCvar
{
public:
	LPCSTR cName;
	BOOL bValue;
	CBoolCvar(PCHAR cCvarName)
	{
		cName = cCvarName;
	}

	BOOL SaveCvar(LPCTSTR lpAppName, LPCTSTR lpFileName)
	{
		BOOL bRet;

		if (bValue == TRUE)
			bRet = WritePrivateProfileString(lpAppName, cName, "On", lpFileName);
		else
			bRet = WritePrivateProfileString(lpAppName, cName, "Off", lpFileName);

		return bRet;
	}
	BOOL  LoadCvar(LPCTSTR lpAppName, BOOL bDefaultValue, LPCTSTR lpFileName)
	{
		BOOL bRet;
		CHAR cResult[256];

		if (bDefaultValue == TRUE)
			bRet = GetPrivateProfileString(lpAppName, cName, "On", cResult, 255, lpFileName);
		else
			bRet = GetPrivateProfileString(lpAppName, cName, "Off", cResult, 255, lpFileName);

		if (strstr(cResult, "On"))
			this->bValue = TRUE;
		else
			this->bValue = FALSE;

		return bRet;
	}


};

class CIntCvar
{
public:
	CIntCvar(PCHAR cCvarName)
	{
		cName = cCvarName;
	}

	BOOL SaveCvar(char* lpAppName, LPCTSTR lpFileName)
	{
		char cValue[256];
		sprintf_s(cValue, "%i", iValue);

		return WritePrivateProfileString(lpAppName, cName, cValue, lpFileName);
	}
	INT LoadCvar(LPCTSTR lpAppName, INT iDefaultValue, LPCTSTR lpFileName)
	{
		BOOL bRet;
		CHAR cResult[256], cDefault[256];

		sprintf_s(cDefault, "%i", iDefaultValue);

		bRet = GetPrivateProfileString(lpAppName, cName, cDefault, cResult, 255, lpFileName);

		this->iValue = (INT)atof(cResult);

		return bRet;
	}

	LPCSTR cName;
	BOOL iValue;
};

class CFloatCvar
{
public:
	CFloatCvar(PCHAR cCvarName)
	{
		cName = cCvarName;
	}

	BOOL SaveCvar(LPCTSTR lpAppName, LPCTSTR lpFileName)
	{
		CHAR cValue[255];
		sprintf_s(cValue, "%.2f", fValue);

		return WritePrivateProfileString(lpAppName, cName, cValue, lpFileName);
	}
	BOOL LoadCvar(LPCTSTR lpAppName, FLOAT fDefaultValue, LPCTSTR lpFileName)
	{
		BOOL bRet;
		CHAR cResult[256], cDefault[256];

		sprintf_s(cDefault, "%f", fDefaultValue);

		bRet = GetPrivateProfileString(lpAppName, cName, cDefault, cResult, 255, lpFileName);

		this->fValue = (FLOAT)atof(cResult);

		return bRet;
	}


	LPCSTR cName;
	FLOAT fValue;
};

class cSettingsFile
{
public:
	void SaveSettings();
	void LoadSettings();
	void ResetSettings();
};

extern cSettingsFile GSettings;

/*AIMBOT*/
extern CBoolCvar cFuncAimbot;
extern CBoolCvar cFuncAimKeyBool;
extern CIntCvar cFuncAimOffsetX;
extern CIntCvar cFuncAimOffsetY;
extern CIntCvar cFuncAimOffsetZ;
extern CIntCvar cFuncAimBoneTag;
extern CIntCvar cFuncAimKey;
extern CIntCvar cFuncAimType;
extern CIntCvar cFuncAimFilter;
extern CIntCvar cFuncAimFov;
extern CFloatCvar cFuncAimSpeed;
/*ESP*/
extern CBoolCvar cFuncESPLines;
extern CBoolCvar cFuncESP2Dbox;
extern CBoolCvar cFuncESP3Dbox;
extern CBoolCvar cFuncESPNames;
extern CBoolCvar cFuncESPSkeleton;
extern CBoolCvar cFuncESPDistance;
extern CIntCvar cFuncESPEnemyVISR;
extern CIntCvar cFuncESPEnemyVISG;
extern CIntCvar cFuncESPEnemyVISB;
extern CIntCvar cFuncESPEnemyUNVISR;
extern CIntCvar cFuncESPEnemyUNVISG;
extern CIntCvar cFuncESPEnemyUNVISB;
extern CIntCvar cFuncESPFriendVISR;
extern CIntCvar cFuncESPFriendVISG;
extern CIntCvar cFuncESPFriendVISB;
extern CIntCvar cFuncESPFriendUNVISR;
extern CIntCvar cFuncESPFriendUNVISG;
extern CIntCvar cFuncESPFriendUNVISB;
extern CIntCvar cFuncESPFilter;
extern CIntCvar cFuncESPFont;
/*VISUAL*/
extern CBoolCvar cFuncVisualWH;
extern CBoolCvar cFuncVisualGranade;
extern CBoolCvar cFuncVisualMG;
extern CBoolCvar cFuncRadar;
extern CBoolCvar cFuncVisualTargetInfo;
extern CIntCvar cFuncVisualCross;
/*MISC*/
extern CBoolCvar cFuncMiscNoRecoil;
extern CBoolCvar cFuncMiscKillSound;
extern CBoolCvar cFuncMiscNameStealer;
extern CBoolCvar cFuncAutoShoot;