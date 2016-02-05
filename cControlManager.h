#pragma once
#define STYLE_CLOSE			0x00010
#define STYLE_MINIMIZE		0x00100
#define STYLE_RESIZABLE		0x01000
#define STYLE_TRANSPARENT	0x10000


#define TYPE_LABEL			0
#define TYPE_GROUPBOX		1
#define TYPE_BUTTON			2
#define TYPE_CHECKBOX		3
#define TYPE_DROPDOWN		5
#define TYPE_SLIDER			6
#define TYPE_CUSTOM			7
#define TYPE_TAB			8
#define TYPE_SFLIDER		9
#define TYPE_SCOLOR        10

#define STATE_NORMAL		0
#define STATE_HOVER			1
#define STATE_PRESSED		2

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#define CopyVec4(a,b) (a[0]=b[0],a[1]=b[1],a[2]=b[2],a[3]=b[3])
#define CopyVec3(a,b) (a[0]=b[0],a[1]=b[1],a[2]=b[2])
#define CatVec4(a,b) (a[0]=a[0]+b[0],a[1]=a[1]+b[1],a[2]=a[2]+b[2],a[3]=a[3]+b[3])
#define POS(Y) 70+19*Y

class cMenuManager;
extern cMenuManager MenuManager;

class cMenu;

class cControlManager
{
public:
	void addTab(cMenu* menu) { tL.push_back(menu); }
	void addChoice(string choice) { cL.push_back(choice); }
	void* customDrawing;
	
	string label;
	int xOffset;
	int yOffset;
	int width;
	int height;

	void* value;
	void* value1;
	void* value2;
	void* function;

	float min;
	float max;
	int off;

	int controlType;

	DWORD align; 
	int group;

	int activeTab; 
	typedef vector<cMenu*> tabList; 
	tabList tL;

	typedef vector<string> choiceList; 
	choiceList cL;
	bool isDropped; 


	bool needsInput;

	cMenu* parent;
}; 

class CLabel : public cControlManager
{
public:
	CLabel(string label, int xOffset, int yOffset, DWORD align)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 0;
		this->height = 0;
		this->function = NULL;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_LABEL;
		this->needsInput = false;

		this->align = align;
	};
};

class CGroupBox : public cControlManager
{
public:
	CGroupBox(string label, int xOffset, int yOffset, int width, int height)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
		this->function = NULL;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_GROUPBOX;
		this->needsInput = false;
	};
};

class CButton : public cControlManager
{
public:
	CButton(string label, int xOffset, int yOffset, int width, int height, void* function)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
		this->function = function;
		this->value = 0;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_BUTTON;
		this->needsInput = true;
	};
};

class CCheckbox : public cControlManager
{
public:
	CCheckbox(string label, int xOffset, int yOffset, void* value)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 16;// 12;
		this->height = 16;// 12;
		this->function = NULL;
		this->value = value;
		this->min = 0;
		this->max = 1;
		this->off = 0;
		this->controlType = TYPE_CHECKBOX;
		this->needsInput = true;
	};
};

class CDropDown : public cControlManager
{
public:
	CDropDown(string label, int xOffset, int yOffset, void* value)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 130;
		this->height = 20;
		this->function = NULL;
		this->value = value;
		this->min = 0;
		this->max = 0;
		this->off = 0;
		this->controlType = TYPE_DROPDOWN;
		this->needsInput = true;

		this->isDropped = false;
	};
};

class CSlider : public cControlManager
{
public:
	CSlider(string label, int xOffset, int yOffset, int min, int max, void* value)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 100;
		this->height = 10;
		this->function = NULL;
		this->value = value;
		this->min = min;
		this->max = max;
		this->off = 0;
		this->controlType = TYPE_SLIDER;
		this->needsInput = true;

		*(int*)this->value = min;
	};
};
class CFSlider : public cControlManager
{
public:
	CFSlider(string label, int xOffset, int yOffset, float min, float max, void* value)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 100;
		this->height = 10;
		this->function = NULL;
		this->value = value;
		this->min = min;
		this->max = max;
		this->off = 0;
		this->controlType = TYPE_SFLIDER;
		this->needsInput = true;

		*(float*)this->value = min;
	};
};
class CSelectColor : public cControlManager
{
public:
	CSelectColor( int xOffset, int yOffset,  void* R, void* G, void* B)
	{
		this->label = label;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 10;
		this->height = 10;
		this->function = NULL;
		this->value = R;
		this->value1 = G;
		this->value2 = B;
		this->min = 8;
		this->max = 8;
		this->off = 0;
		this->controlType = TYPE_SCOLOR;
		this->needsInput = true;
	};
};
class CTab : public cControlManager
{
public:
	CTab(int xOffset, int yOffset)
	{
		this->label = "";
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = 10;
		this->height = 10;
		this->function = NULL;
		this->value = value;
		this->min = min;
		this->max = max;
		this->off = 0;
		this->controlType = TYPE_TAB;
		this->needsInput = true;

		this->activeTab = 0;
	};
};


class cMenu
{
public:
	cMenu(string title) { cMenu(title, 100, 100, 100, 100, NULL); }
	cMenu(string title, int x, int y) { cMenu(title, x, y, 100, 100, NULL); }
	cMenu(string title, int x, int y, int w, int h) { cMenu(title, x, y, w, h, NULL); }
	cMenu(string title, int x, int y, int w, int h, DWORD style);
	//cMenu(string title, int x, int y, int r, int g, int b);
	void setPosition(int x, int y);
	void add(cControlManager* control);

	void addControl(cControlManager* control);

	string title;
	DWORD style;

	bool minimized;
	bool closed;
	bool locked;

	float xPosition;
	float yPosition;
	float width;
	float height;

	typedef vector<cControlManager*> controlList;
	controlList cL;
};
class cMenuManager
{
public:
	typedef vector<cMenu*> menuList;
	menuList mL;

	bool initialized;


	bool menuOpen;
	short menuKey;
	int titlebarHeight;
	int titlebarOffset;

	cMenu* mainMenu;
	cMenu* forcedTopMenu;
	cMenu* foregroundMenu;
	bool fgMenuActive;
	bool movingMenu;
	bool readyForRelease;

	cControlManager* activeControl;
	int controlState;

	int mouseX;
	int mouseY;

	int distanceToX;
	int distanceToY;


	void drawMenus();
	void drawMenu(cMenu* menu);
	void drawControls(cMenu* menu);
	void drawGroupBox(cControlManager* control);
	void drawLabel(cControlManager* control);
	void drawButton(cControlManager* control);
	void drawCheckbox(cControlManager* control);
	void drawSlider(cControlManager* control);
	void drawDropDown(cControlManager* control);
	void drawFSlider(cControlManager* control);
	void drawSelectColor(cControlManager* control);
	void drawCursor();

	
	void handleInput();
	void resetInput();
	void getMousePosition();

	cMenu* getMenuAtMousePosition();
	cControlManager* getControlAtMousePosition();
	int getTabAtMousePosition();

	bool menuIsInRange(cMenu* menu);
	bool controlIsInRange(cControlManager* control);

	void getNewForegroundMenu();
	void getNewActiveControl();

	bool isMovingMenu();
	bool isOverTitlebar();
	void doMovement();

public:
	cMenuManager();
	void add(cMenu* menu);
	void rem(cMenu* menu);

	void setMainMenu(cMenu* menu) { mainMenu = menu; }
	cMenu* getMainMenu() { return mainMenu; }

	void setForegroundMenu(cMenu* menu) { foregroundMenu = menu; (!IsBadReadPtr(menu, 4)) ? fgMenuActive = true : fgMenuActive = false; }

	void setForcedTopMenu(cMenu* menu) { forcedTopMenu = menu; foregroundMenu = forcedTopMenu; (!IsBadReadPtr(menu, 4)) ? fgMenuActive = true : fgMenuActive = false; }

	void closeMenu(cMenu* menu, bool close = true)
	{ menu->closed = close; }

	void mimimizeMenu(cMenu* menu, bool minimize = true)
	{ menu->minimized = minimize; }

	void centerMenu(cMenu* menu);

	void MessageBox(string title, string message);

	int getMenuAmount() { return mL.size(); }

	void initialize();
	void perform();

	void closeKeySelector();

	cMenu* keyMenu;
	cMenu* radMenu;
	cMenu* statMenu;

	bool bKeyInitialized;
	string vKey;

	bool bShowRadWin;
	bool bShowStatWin;
};

struct VIRTUALKEY
{
	UINT uiKey;
	PCHAR szKey;
};
extern VIRTUALKEY VirtualKeyTable[];

void KeyAimSelect(cControlManager* hotkeyLabel);
void SelectAimKey();

void ColorSelect(string Text, int x, int y, cMenu* me, int &R, int &G, int &B);
void Delet();
void Save();