#pragma once
enum
{
	X,
	Y,
	VECTOR2D
};
enum
{
	W = 2,
	H,
	RECTANGLE
};


class cMouse
{
public:
	cMouse();
	void DrawMouse(int x, int y);
	bool LeftClick(int x, int y,int w,int h);
	bool CheckPos(int x, int y, int w, int h);
	void UpdatePos();
	void ClickHandler();
	bool IsOver(int x,int y,int w,int h);


	POINT myPos;
	bool mouse1pressed;
	bool mouse1released;
	int m_info[RECTANGLE];
};
extern cMouse aMouse;