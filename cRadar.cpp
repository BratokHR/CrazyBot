#include "stdafx.h"

cRadar::cRadar(void)
{
	this->xOffset = cg->refdef.width/6;
	this->yOffset = cg->refdef.height/3;
	this->width = 200;
	this->height = 200;
	this->titleHeight = 20;
	this->sizeElemets = 30;
	this->rage = 2000;
}

void cRadar::perform()
{
	if ((bool)cFuncRadar.iValue)
	{
		drawRadar();
		keyDown();
	}
}

void cRadar::drawRadar()
{
	if (!this->init)
		initialization();

	float x = this->xOffset;
	float y = this->yOffset;
	float w = this->width;
	float h = this->height;
	float range = this->rage;

	Draw.Draw_Box(x, y, w, this->titleHeight, MainColor);
	Draw.Draw_Text(x+5, y+this->titleHeight, 0.8, colorWhite, F_LEFT, bot.fonts.Big, "Radar");
	Draw.Draw_Box(x, y+this->titleHeight, w, h, colorBlack_);
	Draw.Draw_Border(x+5, y+this->titleHeight+5, w-10, h-10, 1, colorWhite);
	Draw.Draw_Box(x+(w/2)-10, y+this->titleHeight+(h/2)-0.5, 20, 1, colorWhite);
	Draw.Draw_Box(x+(w/2)-0.5, y+this->titleHeight+(h/2)-10, 1, 20, colorWhite);

	if (!Targets.empty())
	{
		for (int i = 0; i < Targets.size(); i++)
		{
			if (!Targets[i].alive)
				continue;

			float *	TargetOrigin	= Targets[i].cent->lerpOrigin;

			vec3_t	res;
			VectorSubtract( TargetOrigin, cg->refdef.vieworg, res );

			float	dx				= DotProduct( res, cg->refdef.viewaxis[1] );
			float	dy				= DotProduct( res, cg->refdef.viewaxis[0] );

			float	Xpos			= ( x + ( w / 2.0f ) ) - ( dx * ( ( w / 2.0f ) / range ) );
			float	Ypos			= ( y + ( h / 2.0f ) ) - ( dy * ( ( h / 2.0f ) / range) );

			if( Xpos >= ( this->xOffset + this->width - 1.0f ) || Xpos <= ( this->xOffset + 1.0f ) || Ypos >= ( this->yOffset+this->titleHeight + this->height - 1.0f ) || Ypos <= ( this->yOffset+this->titleHeight + 1.0f ) )
				continue;

			if (Targets[i].enemy)
				Draw.Draw_ShaderRotate(Xpos-6.0f, Ypos+12.0f, 12.0f, 12.0f, colorRed, bot.shaders.RadarEnemy, 0);
			else
				Draw.Draw_ShaderRotate(Xpos-6.0f, Ypos+12.0f, 12.0f, 12.0f, colorGreen, bot.shaders.RadarEnemy, 0);
		}
	}
}

void cRadar::keyDown()
{
	POINT mousepos;
	GetCursorPos(&mousepos);
	ScreenToClient(GetForegroundWindow(), &mousepos);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (!this->mouseLeftDown)
		{
			if (mousepos.x >= this->xOffset && mousepos.x <= (this->xOffset + this->width) && mousepos.y >= this->yOffset && mousepos.y<= (this->yOffset + this->height))
			{
				this->mouseLeftDown = true;
				this->movingX = mousepos.x-this->xOffset;
				this->movingY = mousepos.y-this->yOffset;
			}
		}
	}
	else
	{
		this->mouseLeftDown = false;
		this->movingX = -1;
		this->movingY = -1;
	}

	if (this->movingX >= 0 && this->movingY >= 0)
	{
		this->xOffset = mousepos.x - this->movingX;
		this->yOffset = mousepos.y - this->movingY;
	}
}

void cRadar::initialization()
{
	this->init = true;
}