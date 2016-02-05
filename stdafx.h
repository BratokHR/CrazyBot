//Global
#include <windows.h>
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

#pragma comment(lib, "winmm")

using namespace std;

//Local
#include "hook.h"
#include "types.h"
#include "maths.h"
#include "draw.h"
#include "cSettings.h"
#include "cControlManager.h"
#include "cRadar.h"
#include "crazybot.h"
#include "main.h"