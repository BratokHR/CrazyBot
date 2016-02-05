#pragma once
#define F_LEFT		0
#define F_CENTER	1
#define F_RIGHT		2

class cdraw
{
public:
	cdraw(void);

	DWORD d_RegisterShader;
	DWORD d_DrawStretchPic;
	DWORD d_DrawRotatedPic;
	DWORD d_RegisterFont;
	DWORD d_DrawStringExt;

	void Draw_Text(float x, float y, float size, float *colour, int align, LPSTR font, const char *txtformat, ...);
	void Draw_Box(float x, float y, float width, float height, float *colour, float rotate = 0.0f);
	void Draw_Gradient(float x, float y, float width, float height, float *colour1, float *colour2, bool horizontal);
	void Draw_Shader(float x, float y, float width, float height, float *colour, LPSTR shader);
	void Draw_ShaderRotate(float x, float y, float width, float height, float *colour, LPSTR shader, float rotate);
	void Draw_Border(float x, float y, float width, float height, float size, float *colour);
	void Draw_Line(float startX, float startY, float endX, float endY, float *colour, float size = 1.0f);

	int trap_R_RegisterFont(const char * fontName, int pointSize);
	int trap_R_RegisterShader( const char * name, int i1, int i2 );

	char* FPS(void);
	void  render_GUI_CheckBox(float x, float y, float w, float h, float *color);
	void  render_GUI_Menu(float x, float y, float w, float h, float *color);
	void  render_GUI_Button(float x, float y, float w, float h, float *color);

private:
	void trap_R_DrawStretchPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float * colour, LPSTR shader);
	void trap_R_DrawRotatedPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float angle, float * colour, LPSTR shader);
	void trap_R_DrawStringExt(const char * text, int type, LPSTR font, float x, float y, float scalex, float scaley, float * colour, int style);
};

extern cdraw Draw;
extern vec4_t			colorWhite;
extern vec4_t			colorBlack;
extern vec4_t			colorRed;
extern vec4_t			colorGreen;
extern vec4_t			colorBlue;
extern vec4_t			colorYellow;
extern vec4_t			colorCyan;
extern vec4_t			colorOrange;
extern vec4_t			colorWhite_;
extern vec4_t			colorBlack_;
extern vec4_t			colorRed_;
extern vec4_t			colorGreen_;
extern vec4_t			colorBlue_;
extern vec4_t			colorYellow_;
extern vec4_t			colorCyan_;
extern vec4_t			colorOrange_;
extern vec4_t           colorGreenish;
extern vec4_t           colorGreenish_;

extern vec4_t				MainFon;
extern vec4_t				MainColor;
extern vec4_t				MainText;
extern vec4_t				TabColor;
extern vec4_t				clCheckAct;
extern vec4_t				clCheckUnAct;
extern vec4_t				clGroup;
extern vec4_t				clTab;
extern vec4_t				clDrop;
extern vec4_t				clBut;
extern vec4_t				clCursor;
extern vec4_t				clCheckOK;
extern vec4_t				clSliderLine;
extern vec4_t				clSliderBox;