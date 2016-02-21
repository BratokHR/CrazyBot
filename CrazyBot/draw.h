#pragma once
#define F_LEFT		0
#define F_CENTER	1
#define F_RIGHT		2

class cdraw
{
public:
	void Init();

	DWORD d_RegisterShader;
	DWORD d_DrawStretchPic;
	DWORD d_DrawRotatedPic;
	DWORD d_RegisterFont;
	DWORD d_DrawStringExt;

	void Text(float x, float y, float size, float *colour, int align, LPSTR font, const char *txtformat, ...);
	void Box(float x, float y, float width, float height, float *colour, float rotate = 0.0f);
	void Gradient(float x, float y, float width, float height, float *colour1, float *colour2, bool horizontal);
	void Shader(float x, float y, float width, float height, float *colour, LPSTR shader);
	void ShaderRotate(float x, float y, float width, float height, float *colour, LPSTR shader, float rotate);
	void Border(float x, float y, float width, float height, float size, float *colour);
	void Line(float startX, float startY, float endX, float endY, float *colour, float size = 1.0f);
	void BorderLine(vec2_t a, vec2_t b, vec2_t c, vec2_t d, float *color, float width);

	void render_GUI_CheckBox(float x, float y, float w, float h, float *color);
	void render_GUI_Menu(float x, float y, float w, float h, float *color);
	void render_GUI_Button(float x, float y, float w, float h, float *color);

private:
	void trap_R_DrawStretchPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float * colour, LPSTR shader);
	void trap_R_DrawRotatedPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float angle, float * colour, LPSTR shader);
	void trap_R_DrawStringExt(const char * text, int type, LPSTR font, float x, float y, float scalex, float scaley, float * colour, int style);
	int trap_R_RegisterFont(const char * fontName, int pointSize);
	int trap_R_RegisterShader( const char * name, int i1, int i2 );
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