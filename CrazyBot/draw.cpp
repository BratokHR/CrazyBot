#include "stdafx.h"

void cdraw::Init()
{
	DWORD startaddr = (DWORD)GetModuleHandleA("gfx_d3d_mp_x86_s.dll");
	BYTE bytes_stretchpic[] = { 139, 13, -1, -1, -1, -1, 139, 145, -1, -1, -1, -1, 184, -1, -1, -1, -1, 86, 139, 177, -1, -1, -1, -1, 43, 194, 141, 132, 48, -1, -1, -1, -1, 131, 248, 44, 125, 12, 199, 129, -1, -1, -1, -1, -1, -1, -1, -1, 94, 195 };
	d_DrawStretchPic = Hook->FindPattern(startaddr, 0x128000, bytes_stretchpic, "xx????xx????x????xxx????xxxxx????xxxxxxx????????xx");

	BYTE bytes_rotatedpic[] = { 81, 161, -1, -1, -1, -1, 139, 144, -1, -1, -1, -1, 185, -1, -1, -1, -1, 86 };
	d_DrawRotatedPic = Hook->FindPattern(startaddr, 0x128000, bytes_rotatedpic, "xx????xx????x????x");

	BYTE bytes_stringext[] = { 139, 68, 36, 4, 128, 56, -1, 15, 132, -1, -1, -1, -1, 141, 80, 1, 138, 8, 64, 132, 201, 117, 249, 139, 13, -1, -1, -1, -1, 43, 194, 83, 86, 139, 177, -1, -1, -1, -1, 139, 216, 186, -1, -1, -1, -1, 87 };
	d_DrawStringExt = Hook->FindPattern(startaddr, 0x128000, bytes_stringext, "xxxxxx?xx????xxxxxxxxxxxx????xxxxxx????xxx????x");

	BYTE bytes_regfont[] = { 161, -1, -1, -1, -1, 83, 85, 86, 51, 237, 133, 192, 87, 126, 113, 144 };
	d_RegisterFont = Hook->FindPattern(startaddr, 0x128000, bytes_regfont, "x????xxxxxxxxxxx");

	BYTE bytes_regshader[] = { 139, 68, 36, 4, 128, 56, -1, 117, 6, 161, -1, -1, -1, -1, 195, 139, 76, 36, 12, 81, 232, -1, -1, -1, -1, 131, 196, 4 };
	d_RegisterShader = Hook->FindPattern(startaddr, 0x128000, bytes_regshader, "xxxxxx?xxx????xxxxxxx????xxx");
}

int cdraw::trap_R_RegisterFont(const char * fontName, int pointSize)
{
	return ( ( int (*)( const char * fontName, int pointSize ) )d_RegisterFont )( fontName, pointSize );
}

int cdraw::trap_R_RegisterShader( const char * name, int i1, int i2 )
{
	return ( ( int (*)( const char * name, int, int ) )d_RegisterShader )( name, i1, i2 );
}

void cdraw::trap_R_DrawStretchPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float * colour, LPSTR shader)
{
	( ( void (*)( float x, float y, float width, float height, float s1, float t1, float s2, float t2, float * colour, int shader ) )d_DrawStretchPic )( x, y, width, height, s1, t1, s2, t2, colour, trap_R_RegisterShader((char*)shader, 3, 7) );
}

void cdraw::trap_R_DrawRotatedPic(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float angle, float * colour, LPSTR shader)
{
	( ( void (*)(float x, float y, float width, float height, float s1, float t1, float s2, float t2, float angle, float * colour, int shader) )d_DrawRotatedPic )(x, y, width, height, s1, t1, s2, t2, angle, colour, trap_R_RegisterShader((char*)shader, 3, 7));
}

void cdraw::trap_R_DrawStringExt(const char * text, int type, LPSTR font, float x, float y, float scalex, float scaley, float * colour, int style)
{
	( ( void (*)( const char * text, int type, int font, float x, float y, float scalex, float scaley, float * colour, int style ) )d_DrawStringExt )( text, type, trap_R_RegisterFont((char*)font, 3), x, y, scalex, scaley, colour, style );
}

void cdraw::Text(float x, float y, float size, float *colour, int align, LPSTR font, const char *txtformat, ...)
{
	char szBuffer[512] = "";
	va_list	ap;
	va_start( ap, txtformat );
	_vsnprintf_s( szBuffer, 512, 511, txtformat, ap );
	va_end( ap );

	float sztext = strlen(szBuffer)*10*size;
	if (align == F_CENTER)
		x = x-(sztext/2);
	else if (align == F_RIGHT)
		x = x-sztext;

	vec4_t Black = {0.0f,0.0f,0.0f,1.0f};
	trap_R_DrawStringExt(szBuffer, 0x7FFFFFFF, font, (x+0.5f), (y+0.5f), size, size, Black, 1);
	trap_R_DrawStringExt(szBuffer, 0x7FFFFFFF, font, x, y, size, size, colour, 1);
}

void cdraw::Box(float x, float y, float width, float height, float *colour, float rotate)
{
	trap_R_DrawRotatedPic(x, y, width, height, 0, 0, 0, 1, rotate, colour, bot.shaders.White);
}

void cdraw::Gradient(float x, float y, float width, float height, float *colour1, float *colour2, bool horizontal)
{
	float fAdd = (horizontal?0:width/2-height/2);
	trap_R_DrawRotatedPic( x, y, width, height, 0, 0, 1, 1, 0, colour2, bot.shaders.White );
	trap_R_DrawRotatedPic( x+fAdd, y-fAdd, (horizontal?width:height), (horizontal?height:width), 0.5f, 0, 1, 1, (horizontal ? 0.0f : 90.0f), colour1, bot.shaders.Gradient );
}

void cdraw::Shader(float x, float y, float width, float height, float *colour, LPSTR shader)
{
	trap_R_DrawStretchPic(x, y, width, height, 0, 0, 1, 1, colour, shader);
}

void cdraw::ShaderRotate(float x, float y, float width, float height, float *colour, LPSTR shader, float rotate)
{
	trap_R_DrawRotatedPic(x, y, width, height, 0, 0, 1, 1, rotate, colour, shader);
}

void cdraw::Border(float x, float y, float width, float height, float size, float *colour)
{
	Box(x, (y-size), (width+size), size, colour); 
	Box((x+width), (y-size), size, (height+2*size), colour); 
	Box((x-size), (y+height), (width+2*size), size, colour);
	Box((x-size), (y-size), size, (height+2*size), colour);
}

void cdraw::Line(float startX, float startY, float endX, float endY, float *colour, float width)
{
	float sizeX = endX-startX;
	float sizeY = endY-startY;
	float size = sqrt((sizeX*sizeX)+(sizeY*sizeY));

	float x = (startX+(sizeX/2))-(size/2);
	float y = startY+(sizeY/2);
	float angle = RAD2DEG(atan(sizeY/sizeX));
	trap_R_DrawRotatedPic(x, y, size, width, 2, 2, 0, 0, angle, colour, bot.shaders.White);
}

void cdraw::BorderLine(vec2_t a, vec2_t b, vec2_t c, vec2_t d, float *color, float width)
{
	Line(a[0], a[1], b[0], b[1], color, 1);
	Line(b[0], b[1], c[0], c[1], color, 1);
	Line(c[0], c[1], d[0], d[1], color, 1);
	Line(d[0], d[1], a[0], a[1], color, 1);
}


void  cdraw::render_GUI_CheckBox(float x, float y, float w, float h, float *color)
{
	Box(x, y, w, h, color);
	Border(x, y, w, h, 1, colorBlack);
	Border(x+3, y+3, w-6, h-6, 1, colorBlack);
	
}
void  cdraw::render_GUI_Menu(float x, float y, float w, float h, float *color)
{
	Box(x, y, w, h, color);
	Border(x, y, w, h,1, colorBlack);
	Border(x+2, y+2, w-4, h-4, 1, colorBlack);
}
void  cdraw::render_GUI_Button(float x, float y, float w, float h, float *color)
{
	Box(x, y, w, h, color);
	Border(x, y, w, h, 1, colorBlack);
}

cdraw Draw;

vec4_t				colorWhite			= { 1.0f, 1.0f, 1.0f, 1.0f };
vec4_t				colorBlack			= { 0.0f, 0.0f, 0.0f, 1.0f };
vec4_t				colorRed			= { 1.0f, 0.0f, 0.0f, 1.0f };
vec4_t				colorGreen			= { 0.0f, 1.0f, 0.0f, 1.0f };
vec4_t				colorBlue			= { 0.0f, 0.0f, 1.0f, 1.0f };
vec4_t				colorYellow			= { 1.0f, 1.0f, 0.0f, 1.0f };
vec4_t				colorCyan			= { 0.0f, 1.0f, 1.0f, 1.0f };
vec4_t				colorOrange			= { 1.0f, 0.6f, 0.0f, 1.0f };
vec4_t				colorWhite_			= { 1.0f, 1.0f, 1.0f, 0.5f };
vec4_t				colorBlack_			= { 0.0f, 0.0f, 0.0f, 0.5f };
vec4_t				colorRed_			= { 1.0f, 0.0f, 0.0f, 0.5f };
vec4_t				colorGreen_			= { 0.0f, 1.0f, 0.0f, 0.5f };
vec4_t				colorBlue_			= { 0.0f, 0.0f, 1.0f, 0.5f };
vec4_t				colorYellow_		= { 1.0f, 1.0f, 0.0f, 0.5f };
vec4_t				colorCyan_			= { 0.0f, 1.0f, 1.0f, 0.5f };
vec4_t				colorOrange_		= { 1.0f, 0.6f, 0.0f, 0.5f };
vec4_t              colorGreenish       = { 0.5882f, 0.7843f, 0.7843f, 1.0f };
vec4_t              colorGreenish_      = { 0.5882f, 0.7843f, 0.7843f, 0.3500f };

vec4_t				MainFon				= { 34.0f/255.0f,	34.0f/255.0f,	34.0f/255.0f,		1.0f };
vec4_t				MainColor			= { 2.0f/255.0f,	58.0f/255.0f,	96.0f/255.0f,		1.0f };
vec4_t				MainText			= { 255.0f/255.0f,	255.0f/255.0f,	255.0f/255.0f,		1.0f };
vec4_t				TabColor			= { 52.0f/255.0f,	105.0f/255.0f,	105.0f/255.0f,		1.0f };
vec4_t				clCheckAct			= { 34.0f/255.0f,	34.0f/255.0f,	34.0f/255.0f,		1.0f };
vec4_t				clCheckUnAct		= { 44.0f/255.0f,	44.0f/255.0f,	44.0f/255.0f,		1.0f };
vec4_t				clCheckOK			= { 36.0f/255.0f,	92.0f/255.0f,	100.0f/255.0f,		1.0f };
vec4_t				clGroup				= { 183.0f/255.0f,	183.0f/255.0f,	183.0f/255.0f,		1.0f };
vec4_t				clTab				= { 44.0f/255.0f,	44.0f/255.0f,	44.0f/255.0f,		1.0f };
vec4_t				clDrop				= { 44.0f/255.0f,	44.0f/255.0f,	44.0f/255.0f,		1.0f };
vec4_t				clBut				= { 44.0f/255.0f,	44.0f/255.0f,	44.0f/255.0f,		1.0f };
vec4_t				clCursor			= { 0.0f/255.0f,	129.0f/255.0f,	178.0f/255.0f,		1.0f };
vec4_t				clSliderLine		= { 206.0f/255.0f,	206.0f/255.0f,	206.0f/255.0f,		1.0f };
vec4_t				clSliderBox			= { 168.0f/255.0f,	168.0f/255.0f,	168.0f/255.0f,		1.0f };