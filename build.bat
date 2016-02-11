@ECHO OFF
i686-w64-mingw32-gcc -oS -s -mwindows -static -Wno-write-strings main.cpp -o CrazyBotInject.exe
i686-w64-mingw32-g++ -oS -s -shared -mwindows -static -masm=intel -Wno-write-strings -Wno-endif-labels cControlManager.cpp cRadar.cpp crazybot.cpp cSettings.cpp dllmain.cpp draw.cpp hook.cpp maths.cpp types.cpp -o CrazyBot.dll
pause