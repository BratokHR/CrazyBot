#pragma once
class cRadar
{
private:
	bool init;
	bool mouseLeftDown;

	float xOffset;
	float yOffset;
	float sizeElemets;
	float rage;
	float width;
	float height;
	float titleHeight;

	int movingX;
	int movingY;

public:
	void drawRadar();
	void initialization();
	void keyDown();
	void perform();
};

extern cRadar Radar;