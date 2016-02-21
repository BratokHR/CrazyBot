//Глобальные переменные
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <xstring>
#include <fstream>
#include <string>
#include <detours.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <mmsystem.h>
#include <io.h>
#include <regex>

#pragma comment(lib, "winmm")

using namespace std;

//Локальные переменные
#include "cPrintinEngine.h"
#include "hook.h"
#include "types.h"
#include "cRadar.h"
#include "maths.h"
#include "draw.h"
#include "cSettings.h"
#include "cControlManager.h"
#include "detours.h"
#include "crazybot.h"