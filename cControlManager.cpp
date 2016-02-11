#include "stdafx.h"

cMenuManager MenuManager;

void cMenuManager::initialize()
{

	if (this->initialized) return;

	cMenu* mainMenu = new cMenu("CrazyBot by BratokHR v1.0", 10, 100, 450, 400,STYLE_CLOSE | STYLE_MINIMIZE); 
	cControlManager* mainTabControl = new CTab(6,6);

	cMenu* AimbotTab = new cMenu("Aimbot", -1, -1, 300, 160, NULL);
	AimbotTab->add(new CGroupBox("Aimbot", 6, 35, 437, 360));

	AimbotTab->add(new CCheckbox("Aimbot", 30, POS(0), &cFuncAimbot.iValue));
	AimbotTab->add(new CSlider("Offset X", 30, POS(3), 0, 100, &cFuncAimOffsetX.iValue));
	AimbotTab->add(new CSlider("Offset Y", 30, POS(5), 0, 100, &cFuncAimOffsetY.iValue));
	AimbotTab->add(new CSlider("Fov", 250, POS(5), 1, 360, &cFuncAimFov.iValue));

	cControlManager* DropAim = new CDropDown("Type", 250, POS(1)-5, &cFuncAimType.iValue);
	  DropAim->addChoice("Crazy aim");
	  DropAim->addChoice("Silent aim");
	  DropAim->addChoice("Aim key");
	 AimbotTab->add(DropAim);

	 cControlManager* DropFilter = new CDropDown("Filter", 250, POS(7), &cFuncAimFilter.iValue);
	  DropFilter->addChoice("Min angles");
	  DropFilter->addChoice("Min distance");
	  DropFilter->addChoice("Max distance");
	 AimbotTab->add(DropFilter);

	 cControlManager* DropBone = new CDropDown("Bone tag", 30, POS(7), &cFuncAimBoneTag.iValue);
	  DropBone->addChoice("Helmet");
	  DropBone->addChoice("Nose");
	  DropBone->addChoice("Jaw");
	  DropBone->addChoice("Chest");
	  DropBone->addChoice("Pelvis");
	 AimbotTab->add(DropBone);

	 AimbotTab->add(new CButton("Key on aimkey", 250, POS(15)-2, 160, 20, (void*)SelectAimKey));

	cMenu* ESPTab = new cMenu("ESP", -1, -1, 388, 365, NULL);
	ESPTab->add(new CGroupBox("ESP", 6, 35, 437, 360));

	ESPTab->add(new CCheckbox("Names", 30, POS(0), &cFuncESPNames.iValue));
	ESPTab->add(new CCheckbox("2D Box", 30, POS(1), &cFuncESP2Dbox.iValue));
	//ESPTab->add(new CCheckbox("3D Box", 30, POS(2), &cFuncESP3Dbox.iValue));
	ESPTab->add(new CCheckbox("Distance", 30, POS(2), &cFuncESPDistance.iValue));
	ESPTab->add(new CCheckbox("Lines", 30, POS(3), &cFuncESPLines.iValue));
	ESPTab->add(new CCheckbox("Skeleton", 30, POS(4), &cFuncESPSkeleton.iValue));

	ESPTab->add(new CGroupBox("Enemies", 145, POS(0)-10, 283, 70));
	ColorSelect("Visible", 150, POS(1), ESPTab, cFuncESPEnemyVISR.iValue, cFuncESPEnemyVISG.iValue, cFuncESPEnemyVISB.iValue);
	ColorSelect("Invisible", 290, POS(1), ESPTab, cFuncESPEnemyUNVISR.iValue, cFuncESPEnemyUNVISG.iValue, cFuncESPEnemyUNVISB.iValue);
	ESPTab->add(new CGroupBox("Friends", 145, POS(5)-10, 283, 70));
	ColorSelect("Visible", 150, POS(6), ESPTab, cFuncESPFriendVISR.iValue, cFuncESPFriendVISG.iValue, cFuncESPFriendVISB.iValue);
	ColorSelect("Invisible", 290, POS(6), ESPTab, cFuncESPFriendUNVISR.iValue, cFuncESPFriendUNVISG.iValue, cFuncESPFriendUNVISB.iValue);

	cControlManager* EspFont = new CDropDown("Font", 145, POS(10), &cFuncESPFont.iValue);
	  EspFont->addChoice("Big");
	  EspFont->addChoice("Normal");
	  EspFont->addChoice("Small");
	  EspFont->addChoice("Bold");
	 ESPTab->add(EspFont);

	cControlManager* EspFilter = new CDropDown("Filter", 290, POS(10), &cFuncESPFilter.iValue);
	  EspFilter->addChoice("All");
	  EspFilter->addChoice("Enemies");
	  EspFilter->addChoice("Friends");
	 ESPTab->add(EspFilter);

	cMenu* VisualTab = new cMenu("Visual", -1, -1, 300, 160, NULL);
	VisualTab->add(new CGroupBox("Visual", 6, 35, 437, 360));

	VisualTab->add(new CCheckbox("Wallhack", 30, POS(0), &cFuncVisualWH.iValue));
	VisualTab->add(new CCheckbox("Grenade indicator", 30, POS(1), &cFuncVisualGranade.iValue));
	VisualTab->add(new CCheckbox("MG indicator", 30, POS(2), &cFuncVisualMG.iValue));
	VisualTab->add(new CCheckbox("Radar", 30, POS(3), &cFuncRadar.iValue));
	VisualTab->add(new CCheckbox("Target info", 30, POS(4), &cFuncVisualTargetInfo.iValue));

	cControlManager* VisualCrossFLTR = new CDropDown("Cross", 220, POS(0), &cFuncVisualCross.iValue);
	  VisualCrossFLTR->addChoice("Off");
	  VisualCrossFLTR->addChoice("Circle");
	  VisualCrossFLTR->addChoice("Square");
	  VisualCrossFLTR->addChoice("Cross");
	 VisualTab->add(VisualCrossFLTR);

	cMenu* MiscTab = new cMenu("Misc", -1, -1, 300, 160, NULL);
	MiscTab->add(new CGroupBox("Misc", 6, 35, 437, 360));

	MiscTab->add(new CCheckbox("NoRecoil", 30, POS(0), &cFuncMiscNoRecoil.iValue));
	MiscTab->add(new CCheckbox("AutoShoot", 30, POS(1), &cFuncAutoShoot.iValue));
	MiscTab->add(new CCheckbox("AutoVote", 30, POS(2), &cFuncAutoVote.iValue));
	MiscTab->add(new CCheckbox("NameStealer", 30, POS(3), &cFuncMiscNameStealer.iValue));
	MiscTab->add(new CCheckbox("KillSpam", 30, POS(4), &cFuncMiscKillSpam.iValue));
	MiscTab->add(new CCheckbox("KillSound", 30, POS(5), &cFuncMiscKillSound.iValue));

	MiscTab->add(new CButton("Open console", 250, POS(15)-2, 160, 20, (void*)OpenConsole));

	this->add(mainMenu);
	mainTabControl->addTab(AimbotTab);
	mainTabControl->addTab(ESPTab);
	mainTabControl->addTab(VisualTab);
	mainTabControl->addTab(MiscTab);
	mainMenu->add(mainTabControl);

	this->setMainMenu(mainMenu); 
	this->setForegroundMenu(mainMenu); 
	this->centerMenu(mainMenu);
	this->initialized = true;
}

void ColorSelect(string Text, int x, int y, cMenu* me, int &R, int &G, int &B)
{	

	me->add(new CSlider(Text, x, y, 0, 255, &R));
	me->add(new CSlider("", x, y+12, 0, 255, &G));
	me->add(new CSlider("", x, y+24, 0, 255, &B));
	me->add(new CSelectColor(x+90, y-12, &R, &G, &B));
}

void KeyAimSelect(cControlManager* hotkeyLabel)
{
	while (cFuncAimKey.iValue == -1)
	{
		for (int i = 0; i < 115; i++)
		{
			if (KEY_DOWN(VirtualKeyTable[i].uiKey))
			{
				if (VirtualKeyTable[i].uiKey == VK_ESCAPE) {
					MenuManager.closeKeySelector();
					break;
				}
				cFuncAimKey.iValue = i;
				char newLabel[50];
				sprintf(newLabel, "Selected: %s", VirtualKeyTable[(int)cFuncAimKey.iValue].szKey);
				hotkeyLabel->label = newLabel;
				break;
			}
		}

		Sleep(20);
	}
	Sleep(2000);

	MenuManager.closeKeySelector();
}
void SelectAimKey()
{
	if (MenuManager.bKeyInitialized || cFuncAimKey.iValue == -1) return;
	cFuncAimKey.iValue = -1;

	MenuManager.keyMenu = new cMenu("HotKey Aim", 50, 50, 150, 100, STYLE_CLOSE);
	//MenuManager.keyMenu->add(new CGroupBox("Key Selector", 10, 10, 130, 90)); //

	cControlManager* hotkeyLabel;
	hotkeyLabel = new CLabel("Press on hotkey", 20, 40, F_LEFT);
	MenuManager.keyMenu->add(hotkeyLabel);

	MenuManager.add(MenuManager.keyMenu); 
	MenuManager.setForegroundMenu(MenuManager.keyMenu);
	MenuManager.centerMenu(MenuManager.keyMenu);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)KeyAimSelect, hotkeyLabel, 0, 0);

	MenuManager.bKeyInitialized = true;
}

void cMenu::add(cControlManager* control)
{
	control->parent = this;
	this->cL.push_back(control);
}

cMenu::cMenu(string title, int x, int y, int w, int h, DWORD style)
{
	this->title = title;
	this->style = style;

	this->minimized = false;
	this->closed = false;
	this->locked = false;

	this->xPosition = x;
	this->yPosition = y;
	this->width = w;
	this->height = h;

	this->cL.clear();
}

void cMenu::setPosition(int x, int y)
{
	this->xPosition = x;
	this->yPosition = y;
}

cMenuManager::cMenuManager()
{
	this->mL.clear();

	this->initialized = false;
	this->bKeyInitialized = false; 
	this->bShowRadWin = false;


	this->menuOpen = false;
	this->menuKey = VK_F8;
	this->titlebarHeight = 20;
	this->titlebarOffset = 0;

	this->mainMenu = NULL;
	this->forcedTopMenu = NULL;
	this->foregroundMenu = NULL;
	this->fgMenuActive = false;
	this->movingMenu = false;
	this->readyForRelease = false;

	this->activeControl = NULL;
	this->controlState = -1;

	this->mouseX = 0;
	this->mouseY = 0;

	this->distanceToX = 0;
	this->distanceToY = 0;
}

void cMenuManager::perform()
{
	this->drawMenus();
	this->handleInput();
}

void cMenuManager::add(cMenu* menu)
{
	this->mL.push_back(menu);
}

void cMenuManager::rem(cMenu* menu)
{
	vector<cMenu*>::iterator it;
	vector<cControlManager*>::iterator it2;
	for (it = this->mL.begin(); it != this->mL.end();)
	{
		if (*it == menu)
		{
			cMenu* menu = *it;

			for (it2 = menu->cL.begin(); it2 != menu->cL.end(); ++it2)
				delete * it2;

			menu->cL.clear();
			delete * it;
			it = this->mL.erase(it);
		}
		else ++it;
	}
}

void cMenuManager::drawMenus()
{
	if (!this->initialized) return;

	short menuListSize = mL.size();
	for (int i = 0; i<menuListSize; ++i)
	{
		cMenu* menu = mL[i];
		if (!menu->locked && !menuOpen) continue;
		if (menu == foregroundMenu || menu->closed) continue;
		drawMenu(menu);
	}

	if (this->forcedTopMenu != NULL && (menuOpen || this->forcedTopMenu->locked))
	{
		int width = cg->refdef.width;
		int height = cg->refdef.height;
		Draw.Draw_Box(0, 0, width+1, height+1, colorBlack);// фон при выпадении MessegeBox
	}

	if (foregroundMenu && (foregroundMenu->locked || menuOpen)) drawMenu(foregroundMenu);

	if(menuOpen) drawCursor();
}

void cMenuManager::drawCursor()
{
	int width = 70;
	Draw.Draw_Shader(mouseX-(width/2), mouseY-(width/2)+1, width, width, clCursor, bot.shaders.Cursor);
}

void cMenuManager::drawMenu(cMenu* menu)
{

	if ((titlebarOffset <= 2 || menu->minimized || menu->style & STYLE_TRANSPARENT) && menuOpen)
		Draw.Draw_Border(menu->xPosition , menu->yPosition, menu->width, titlebarHeight, 1, colorBlack);// рамка заголовка
	if ((menuOpen || menu->locked) && ~menu->style & STYLE_TRANSPARENT)//{}
		Draw.Draw_Border(menu->xPosition, menu->yPosition + titlebarHeight + titlebarOffset, menu->width, menu->height, 1, colorBlack);// рамка основной поверхности
	
	if (!menu->minimized)
	{
		if (~menu->style & STYLE_TRANSPARENT)// основная поверхность
			Draw.render_GUI_Menu(menu->xPosition, menu->yPosition + titlebarHeight + titlebarOffset + 2, menu->width, menu->height, MainFon);
		drawControls(menu);
	}

	if (menu->locked && !menuOpen) return; 

	vec4_t titleBarColour = { 3.0f/255.0f, 97.0f/255.0f, 158.0f/255.0f, 1.0f };// заголовок вне фокуса
	vec4_t titleBarColourText = { 166.0f/255.0f, 166.0f/255.0f, 166.0f/255.0f };
	if (menu == foregroundMenu && fgMenuActive)
	{
		CopyVec4(titleBarColour,MainColor);// заголовок в фокусе
		CopyVec4(titleBarColourText,MainText);
	}
	
	Draw.Draw_Box(menu->xPosition, menu->yPosition, menu->width, titlebarHeight, titleBarColour);//заголовок
	Draw.Draw_Text(menu->xPosition+5, menu->yPosition+titlebarHeight+1, 1, titleBarColourText, F_LEFT, bot.fonts.Big, menu->title.c_str());
}

void cMenuManager::handleInput()
{
	if (!this->initialized) return;

	
	if (GetAsyncKeyState(menuKey) & 1)
	{
		if (!menuOpen) 
		{
			Hook->MemoryWrite((void*)MenuOpen, (void*)"\x74\x7C", 2);
			Hook->MemoryWrite((void*)Attack, (void*)"\xC3", 1);
			char sound[MAX_PATH];
			sprintf(sound, "%ssounds/Open.wav", bot.path);
			PlaySound(sound, NULL, SND_ASYNC);
			menuOpen = true;
		}
		else
		{
			SetCursorPos((cg->refdef.width/2),(cg->refdef.height/2));
			Hook->MemoryWrite((void*)MenuOpen, (void*)"\x75\x7C", 2);
			Hook->MemoryWrite((void*)Attack, (void*)"\x56", 1);
			char sound[MAX_PATH];
			sprintf(sound, "%ssounds/Open.wav", bot.path);
			PlaySound(sound, NULL, SND_ASYNC);
			GSettings.SaveSettings();
			menuOpen = false;
		}
	}

	if (!menuOpen) { resetInput(); return; }

	
	getMousePosition();

	getNewActiveControl();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!movingMenu) getNewForegroundMenu();

		if (foregroundMenu == NULL) return;

		cMenu* menu = foregroundMenu;

		if (!fgMenuActive) return;

		doMovement();
		if ((movingMenu = isMovingMenu()) == true) return;

		if (activeControl == NULL) return;

		cControlManager* control = activeControl;
		if (controlState == STATE_HOVER)
		{
			controlState = STATE_PRESSED;

			if (control->controlType == TYPE_SLIDER)
			{
				int x = control->parent->xPosition + control->xOffset;
				*(int*)control->value = (mouseX - x) * (control->max - control->min) / control->width;

				if (*(int*)control->value > control->max) *(int*)control->value = control->max;
				if (*(int*)control->value < control->min) *(int*)control->value = control->min;

				if (!IsBadReadPtr(control->function, 4))
				{
					DWORD address = (DWORD)control->function;

					__asm(".intel_syntax noprefix\n");
					
					__asm("mov eax, control\n");
					__asm("push eax\n");
					__asm("call address\n");
					__asm("pop ebx\n");
				}

			}
			if (control->controlType == TYPE_SFLIDER)
			{
				int x = control->parent->xPosition + control->xOffset;
				*(float*)control->value = (mouseX - x) * (control->max - control->min) / control->width;

				if (*(float*)control->value > control->max) *(float*)control->value = control->max;
				if (*(float*)control->value < control->min) *(float*)control->value = control->min;

				if (!IsBadReadPtr(control->function, 4))
				{
					DWORD address = (DWORD)control->function;

					__asm(".intel_syntax noprefix\n");
					
					__asm("mov eax, control\n");
					__asm("push eax\n");
					__asm("call address\n");
					__asm("pop ebx\n");
				}

			}

			readyForRelease = true;
			return;
		}

		keybd_event(VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!movingMenu) getNewForegroundMenu();

		if (foregroundMenu == NULL) return;

		cMenu* menu = foregroundMenu;

		if (!fgMenuActive) return;

		keybd_event(VK_RBUTTON, 0, KEYEVENTF_KEYUP, 0);
	}
	else if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
	{
		if (!movingMenu) getNewForegroundMenu();

		if (foregroundMenu == NULL) return;

		cMenu* menu = foregroundMenu;

		if (!fgMenuActive) return;

		if (isOverTitlebar()) menu->minimized = !menu->minimized;

		keybd_event(VK_MBUTTON, 0, KEYEVENTF_KEYUP, 0);
	}
	else
	{
		if (readyForRelease && controlIsInRange(activeControl))
		{
			cMenu* menu = foregroundMenu;
			cControlManager* control = activeControl;
			switch (control->controlType)
			{
			case TYPE_CHECKBOX:
				if (*(bool*)control->value == true)
					*(bool*)control->value = false;
				else
					*(bool*)control->value = true;
				char sound[MAX_PATH];
				sprintf(sound, "%ssounds/Menu_old.wav", bot.path);
				PlaySound(sound, NULL, SND_ASYNC);
				break;
			case TYPE_TAB:
				control->activeTab = getTabAtMousePosition();
				break;
			case TYPE_DROPDOWN:
				control->isDropped = !control->isDropped;

				short choiceListSize = control->cL.size();
				for (int i = 0; i<choiceListSize; ++i)
				{
					int yOffset = (i + 1)*control->height;
					int x = menu->xPosition + control->xOffset;
					int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset + yOffset;
					if (mouseX >= x && mouseX <= x + control->width &&
						mouseY >= y && mouseY <= y + control->height)
					{
						*(int*)control->value = i;
						control->isDropped = false;
						break;
					}
				}

				break;

			}

			if (!IsBadReadPtr(control->function, 4))
			{
				DWORD address = (DWORD)control->function;

				__asm(".intel_syntax noprefix\n");
				
				__asm("mov eax, control\n");
				__asm("push eax");
				__asm("call address\n");
				__asm("pop ebx\n");
			}

		}

		resetInput();
	}
}

void cMenuManager::closeKeySelector()
{
	this->bKeyInitialized = false;
	this->setForcedTopMenu(NULL);
	this->rem(keyMenu);
}

void cMenuManager::resetInput()
{
	movingMenu = false;
	readyForRelease = false;
}

void cMenuManager::getMousePosition()
{

	POINT CursorPos;
	GetCursorPos(&CursorPos);
	ScreenToClient(GetForegroundWindow(), &CursorPos);

	mouseX = CursorPos.x;
	mouseY = CursorPos.y;
}

cMenu* cMenuManager::getMenuAtMousePosition()
{
	if (menuIsInRange(foregroundMenu))
		return foregroundMenu;

	for (int i = 0; i<mL.size(); i++)
	{
		cMenu* menu = mL[i];
		if (menu == foregroundMenu) continue;

		if (menuIsInRange(menu)) return menu;
	}

	return NULL;
}

bool cMenuManager::menuIsInRange(cMenu* menu)
{
	if (!menu) return false;

	if (mouseX >= menu->xPosition && mouseX <= (menu->xPosition + menu->width) &&
		mouseY >= menu->yPosition && mouseY <= (menu->yPosition + menu->height + titlebarHeight + titlebarOffset))
		return true;

	return false;
}

void cMenuManager::getNewActiveControl()
{
	cControlManager* newControl = getControlAtMousePosition();

	if (newControl == NULL)
	{
		controlState = STATE_NORMAL;
		return;
	}

	activeControl = newControl;
	controlState = STATE_HOVER;
}

cControlManager* cMenuManager::getControlAtMousePosition()
{
	if (controlState == STATE_PRESSED) return activeControl;

	for (int i = 0; i<mL.size(); i++)
	{
		cMenu* menu = mL[i];

		if (menu->closed || menu->minimized) continue;

		for (int j = 0; j<menu->cL.size(); j++)
		{
			cControlManager* control = menu->cL[j];

			if (!control->needsInput) continue;

			if (controlIsInRange(control)) return control;

			if (control->tL.size() > 0)
			{
				cMenu* activeTab = control->tL[control->activeTab];
				for (int k = 0; k<activeTab->cL.size(); k++)
				{
					cControlManager* control = activeTab->cL[k];
					if (!control->needsInput) continue;
					if (controlIsInRange(control)) return control;
				}
			}
		}
	}

	return NULL;
}

bool cMenuManager::controlIsInRange(cControlManager* control)
{
	if (!control) return false;

	cMenu* menu = control->parent;
	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;
	int width = control->width;
	int height = control->height;

	if (control->controlType == TYPE_DROPDOWN && control->isDropped)
		height = control->height*(control->cL.size() + 1);

	if (mouseX >= x && mouseX <= (x + width) &&
		mouseY >= y && mouseY <= (y + height))
		return true;

	return false;
}

void cMenuManager::getNewForegroundMenu()
{
	if (forcedTopMenu != NULL) return;
	cMenu* newMenu = getMenuAtMousePosition();

	if (newMenu == NULL)
	{
		fgMenuActive = false;
		return;
	}

	foregroundMenu = newMenu;
	fgMenuActive = true;
}

void cMenuManager::doMovement()
{
	cMenu* menu = foregroundMenu;

	if (movingMenu)
	{
		menu->xPosition = mouseX - distanceToX;
		menu->yPosition = mouseY - distanceToY;
	}
	else
	{
		distanceToX = mouseX - menu->xPosition;
		distanceToY = mouseY - menu->yPosition;
	}
}

bool cMenuManager::isMovingMenu()
{
	if (movingMenu) return true;

	return isOverTitlebar();
}

bool cMenuManager::isOverTitlebar()
{
	cMenu* menu = foregroundMenu;

	if (mouseX >= menu->xPosition && mouseX <= menu->xPosition + menu->width &&
		mouseY >= menu->yPosition && mouseY <= (menu->yPosition + titlebarHeight))
		return true;

	return false;
}

int cMenuManager::getTabAtMousePosition()
{
	for (int i = 0; i<activeControl->tL.size(); i++)
	{
		int w = 107;
		int h = 20;

		int xMultiplier = (w + 3) * i;
		int x = foregroundMenu->xPosition + activeControl->xOffset + xMultiplier;
		int y = foregroundMenu->yPosition + activeControl->yOffset + titlebarHeight + titlebarOffset;

		if (mouseX >= x && mouseX <= (x + w) &&
			mouseY >= y && mouseY <= (y + h))
			return i;
	}

	return activeControl->activeTab;
}

void cMenuManager::drawControls(cMenu* menu)
{
	for (int i = 0; i<menu->cL.size(); i++)
	{
		cControlManager* control = menu->cL[i];
		switch (control->controlType)
		{
		
		case TYPE_LABEL:
			drawLabel(control);
			break;
		case TYPE_GROUPBOX:
			drawGroupBox(control);
			break;
		case TYPE_BUTTON:
			drawButton(control);
			break;
		case TYPE_CHECKBOX:
			drawCheckbox(control);
			break;
		case TYPE_DROPDOWN:
			drawDropDown(control);
			break;
		case TYPE_SFLIDER:
			drawFSlider(control);
			break;
		case TYPE_SLIDER:
			drawSlider(control);
			break;
		case TYPE_SCOLOR:
			drawSelectColor(control);
			break;
		case TYPE_TAB:
			for (int i = 0; i<control->tL.size(); i++)
			{
				cMenu* tab = control->tL[i];
				int w = 107;
				int h = 20;

				int xMultiplier = (w + 3) * i;
				int x = menu->xPosition + control->xOffset + xMultiplier;
				int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

				if (i == control->activeTab)
					Draw.Draw_Box(x + 1, y + 1, w - 1, h - 1, clCheckOK);
				else
					Draw.Draw_Box(x + 1, y + 1, w - 1, h - 1, clTab);
				Draw.Draw_Border(x, y, w, h, 1, colorBlack);

				Draw.Draw_Text(x+2, y+h, 0.8, MainText, F_LEFT, bot.fonts.Big, tab->title.c_str());
			}
			cMenu* tab = control->tL[control->activeTab];
			tab->xPosition = menu->xPosition;
			tab->yPosition = menu->yPosition;

			control->width = (107 + 3) * control->tL.size();
			control->height = 20;

			drawControls(tab);
			break;
		
		}
	}
}

void cMenuManager::drawLabel(cControlManager* control)
{
	cMenu* menu = control->parent;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	Draw.Draw_Text(x, y+8, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());
}

void cMenuManager::drawGroupBox(cControlManager* control)
{
	cMenu* menu = control->parent;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	int stringLength = strlen(control->label.c_str()) * 11;

	Draw.Draw_Box(x, y, 1, control->height, clGroup);
	Draw.Draw_Box(x, y+control->height, control->width, 1, clGroup);
	Draw.Draw_Box(x+control->width, y, 1, control->height+1, clGroup);
	Draw.Draw_Box(x, y, 18, 1, clGroup);
	Draw.Draw_Box(x+10+stringLength, y, control->width-10-stringLength, 1, clGroup);

	Draw.Draw_Text(x+20, y+8, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());
}

void cMenuManager::drawButton(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	vec4_t boxBackground;
	CopyVec4(boxBackground, clBut);
	if (state == STATE_HOVER || state == STATE_PRESSED)
	{
		CopyVec4(boxBackground,clCheckAct);
	}
	Draw.render_GUI_Button(x, y, control->width, control->height, boxBackground);
	Draw.Draw_Text(x+5, y+control->height, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());
}

void cMenuManager::drawCheckbox(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	if (state == STATE_NORMAL)
	{
		Draw.render_GUI_CheckBox(x, y, control->width, control->height, clCheckUnAct);
	}
	else
	if (state == STATE_HOVER || state == STATE_PRESSED)
	{
		Draw.render_GUI_CheckBox(x, y, control->width, control->height, clCheckAct);
	}
	Draw.Draw_Text(x + control->width + 5, y+control->height, 0.8, colorWhite, F_LEFT, bot.fonts.Big, control->label.c_str());
	if (control->value && *(bool*)control->value == true)
		Draw.Draw_Box(x + 4, y + 4, control->width - 7, control->height - 7, clCheckOK);
}

void cMenuManager::drawDropDown(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	if (state == STATE_NORMAL)
		Draw.Draw_Box(x, y, control->width, control->height, clDrop);
	else Draw.Draw_Box(x, y, control->width, control->height, clCheckAct);

	Draw.Draw_Border(x, y, control->width, control->height, 1, colorBlack);

	if (control->value)
	{
		Draw.Draw_Text(x+5, y+control->height, 0.8, MainText, F_LEFT, bot.fonts.Big, control->cL[*(int*)control->value].c_str());
		Draw.Draw_Text(x, y, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());

		if (control->isDropped)
		{
			Draw.Draw_ShaderRotate(x+control->width-20, y+(control->height/2)-7, 15, 15, colorBlack, bot.shaders.Arrow, 0);
			short choiceListSize = control->cL.size();
			for (int i = 0; i<choiceListSize; ++i)
			{
				int yOffset = (i + 1)*control->height;
				Draw.Draw_Box(x+1, y+1+yOffset, control->width-1, control->height, clDrop);
				Draw.Draw_Text(x+5, y+control->height+yOffset, 0.8, MainText, F_LEFT, bot.fonts.Big, control->cL[i].c_str());
			}
		}
		else Draw.Draw_ShaderRotate(x+control->width-20, y+(control->height/2)-7, 15, 15, colorWhite, bot.shaders.Arrow, 180);
	}
}

void cMenuManager::drawSlider(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	Draw.Draw_Box(x, y+(control->height/2), control->width, control->height/4, clSliderLine);

	int valueX = x + ((*(int*)control->value - control->min) * control->width / (control->max - control->min));
	Draw.Draw_Box(valueX, y, 4, control->height, clSliderBox);

	Draw.Draw_Text(x, y+control->height-10, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());
	Draw.Draw_Text(x+control->width+7, y+control->height+1, 0.8, MainText, F_LEFT, bot.fonts.Big, "%i", *(int*)control->value);
}
void cMenuManager::drawFSlider(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition + control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	Draw.Draw_Box(x, y+(control->height/2), control->width, control->height/4, clSliderLine);

	int valueX = x + ((*(int*)control->value - control->min) * control->width / (control->max - control->min));
	Draw.Draw_Box(valueX, y, 4, control->height, clSliderBox);

	Draw.Draw_Text(x, y+control->height-10, 0.8, MainText, F_LEFT, bot.fonts.Big, control->label.c_str());
	Draw.Draw_Text(x+control->width+7, y+control->height+1, 0.8, MainText, F_LEFT, bot.fonts.Big, "%.1f", *(float*)control->value);

}
void cMenuManager::drawSelectColor(cControlManager* control)
{
	cMenu* menu = control->parent;
	int state = STATE_NORMAL;
	if (control == activeControl) state = controlState;

	int x = menu->xPosition+control->xOffset;
	int y = menu->yPosition + control->yOffset + titlebarHeight + titlebarOffset;

	vec4_t color = {*(int*)control->value/255.0f, *(int*)control->value1/255.0f, *(int*)control->value2/255.0f, 1.0f};
	Draw.Draw_Box(x, y, control->width, control->height, color);
}

void cMenuManager::centerMenu(cMenu* menu)
{
	int w = menu->width;
	int h = menu->height;
	int centerX = (cg->refdef.width / 2) - (w / 2);
	int centerY = (cg->refdef.height / 2) - (h / 2);

	menu->xPosition = centerX;
	menu->yPosition = centerY;
}

void closeMB(cControlManager* control)
{
	cMenu* menu = control->parent;
	MenuManager.setForcedTopMenu(NULL);

	MenuManager.rem(menu);
}

void cMenuManager::MessageBox(string title, string message)
{
	cMenu* messageBox = new cMenu(title, 100, 100, 400, 150, NULL);
	messageBox->add(new CLabel(message, 10, 75 - 14, DT_LEFT));
	messageBox->add(new CButton("OK", 150, 115, 100, 20, (void*)closeMB));
	this->add(messageBox);

	setForcedTopMenu(messageBox);
	centerMenu(messageBox);
}

VIRTUALKEY VirtualKeyTable[] =
{
	{ VK_LBUTTON, "LClick" },
	{ VK_RBUTTON, "RClick" },
	{ VK_CANCEL, "Cancel" },
	{ VK_MBUTTON, "MiddleMouse" },
	{ VK_BACK, "Backspace" },
	{ VK_TAB, "TAB" },
	{ VK_CLEAR, "Clear" },
	{ VK_RETURN, "Enter" },
	{ VK_SHIFT, "Shift" },
	{ VK_CONTROL, "Control" },
	{ VK_MENU, "Alt" },
	{ VK_PAUSE, "Pause" },
	{ VK_CAPITAL, "CAPS" },
	{ VK_ESCAPE, "Escape" },
	{ VK_SPACE, "Spacebar" },
	{ VK_PRIOR, "PageUp" },
	{ VK_NEXT, "PageDown" },
	{ VK_END, "End" },
	{ VK_HOME, "Home" },
	{ VK_LEFT, "LArrow" },
	{ VK_UP, "UpArrow" },
	{ VK_RIGHT, "RArrow" },
	{ VK_DOWN, "DownArrow" },
	{ VK_SELECT, "Select" },
	{ VK_PRINT, "Print" },
	{ VK_EXECUTE, "Execute" },
	{ VK_SNAPSHOT, "PrintScreen" },
	{ VK_INSERT, "Insert" },
	{ VK_DELETE, "Delete" },
	{ VK_HELP, "Help" },
	{ 0x30, "0" },
	{ 0x31, "1" },
	{ 0x32, "2" },
	{ 0x33, "3" },
	{ 0x34, "4" },
	{ 0x35, "5" },
	{ 0x36, "6" },
	{ 0x37, "7" },
	{ 0x38, "8" },
	{ 0x39, "9" },
	{ 0x41, "A" },
	{ 0x42, "B" },
	{ 0x43, "C" },
	{ 0x44, "D" },
	{ 0x45, "E" },
	{ 0x46, "F" },
	{ 0x47, "G" },
	{ 0x48, "H" },
	{ 0x49, "I" },
	{ 0x4A, "J" },
	{ 0x4B, "K" },
	{ 0x4C, "L" },
	{ 0x4D, "M" },
	{ 0x4E, "N" },
	{ 0x4F, "O" },
	{ 0x50, "P" },
	{ 0x51, "Q" },
	{ 0x52, "R" },
	{ 0x53, "S" },
	{ 0x54, "T" },
	{ 0x55, "U" },
	{ 0x56, "V" },
	{ 0x57, "W" },
	{ 0x58, "X" },
	{ 0x59, "Y" },
	{ 0x5A, "Z" },
	{ VK_NUMPAD0, "Numpad0" },
	{ VK_NUMPAD1, "Numpad1" },
	{ VK_NUMPAD2, "Numpad2" },
	{ VK_NUMPAD3, "Numpad3" },
	{ VK_NUMPAD4, "Numpad4" }, // 72
	{ VK_NUMPAD5, "Numpad5" },
	{ VK_NUMPAD6, "Numpad6" },
	{ VK_NUMPAD7, "Numpad7" },
	{ VK_NUMPAD8, "Numpad8" },
	{ VK_NUMPAD9, "Numpad9" },
	{ VK_SEPARATOR, "NumpadSeperator" },
	{ VK_SUBTRACT, "NumpadMinus" },
	{ VK_DECIMAL, "NumpadDecimal" },
	{ VK_DIVIDE, "NumpadDivide" },
	{ VK_F1, "F1" },
	{ VK_F2, "F2" },
	{ VK_F3, "F3" },
	{ VK_F4, "F4" },
	{ VK_F5, "F5" },
	{ VK_F6, "F6" },
	{ VK_F7, "F7" },
	{ VK_F8, "F8" },
	{ VK_F9, "F9" },
	{ VK_F10, "F10" },
	{ VK_F11, "F11" },
	{ VK_F12, "F12" },
	{ VK_F13, "F13" },
	{ VK_F14, "F14" },
	{ VK_F15, "F15" },
	{ VK_F16, "F16" },
	{ VK_F17, "F17" },
	{ VK_F18, "F18" },
	{ VK_F19, "F19" },
	{ VK_F20, "F20" },
	{ VK_F21, "F21" },
	{ VK_F22, "F22" },
	{ VK_F23, "F23" },
	{ VK_F24, "F24" },
	{ VK_NUMLOCK, "Numlock" },
	{ VK_SCROLL, "Scroll" },
	{ VK_LSHIFT, "LeftShift" },
	{ VK_RSHIFT, "RightShift" },
	{ VK_LCONTROL, "LeftCtrl" },
	{ VK_RCONTROL, "RightCtrl" },
	{ VK_LMENU, "LeftMenu" },
	{ VK_RMENU, "RightMenu" },
	{ VK_PLAY, "Play" },
	{ VK_ZOOM, "Zoom" },
	{ VK_XBUTTON1, "XBtn1" },
	{ VK_XBUTTON2, "XBtn2" },
};