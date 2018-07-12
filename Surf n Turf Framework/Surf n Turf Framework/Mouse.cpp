#include "Main.h"

cMouse aMouse;
tagPOINT mPos;

cMouse::cMouse()
{
	mouse1pressed = false;
	mouse1released = false;
}

void cMouse::DrawMouse(int x, int y){
		cDraw.FillRGBA(x + 1, y, 1, 17, Color(0,0,0,255));
	for(int i = 0; i < 11; i++)
		cDraw.FillRGBA(x + 2 + i, y + 1 + i, 1, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 8, y + 12, 5, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 8, y + 13, 1, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 9, y + 14, 1, 2, Color(0,0,0,25));
	cDraw.FillRGBA(x + 10, y + 16, 1, 2, Color(0,0,0,255));
	cDraw.FillRGBA(x + 8, y + 18, 2, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 7, y + 16, 1, 2, Color(0,0,0,255));
	cDraw.FillRGBA(x + 6, y + 14, 1, 2, Color(0,0,0,255));
	cDraw.FillRGBA(x + 5, y + 13, 1, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 4, y + 14, 1, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 3, y + 15, 1, 1, Color(0,0,0,255));
	cDraw.FillRGBA(x + 2, y + 16, 1, 1, Color(0,0,0,255));
	for(int i = 0; i < 4; i++)
		cDraw.FillRGBA(x + 2 + i, y + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4), 255));
	cDraw.FillRGBA(x + 6, y + 6, 1, 8, Color(235, 235, 235, 255));
	cDraw.FillRGBA(x + 7, y + 7, 1, 9, Color(231, 231, 231, 255));
	for(int i = 0; i < 4; i++)
		cDraw.FillRGBA(x + 8 + i, y + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4), 255));
	cDraw.FillRGBA(x + 8, y + 14, 1, 4, Color(207, 207, 207, 255));
	cDraw.FillRGBA(x + 9, y + 16, 1, 2, Color(203, 203, 203, 255));
}

bool cMouse::IsOver(int x,int y,int w,int h)
{
	if( mPos.x > x		&& 
		mPos.x < x+w	&& 
		mPos.y > y		&& 
		mPos.y < y+h	)
		return true;
	else
		return false;
}

void cMouse::ClickHandler()
{
	if(bMenu){
		if((GetAsyncKeyState(VK_LBUTTON)))
		{
			this->mouse1pressed = true;
		}
		else if(!(GetAsyncKeyState(VK_LBUTTON)))
		{
			if(this->mouse1pressed)
				this->mouse1released = true;
			else 
			{
				this->mouse1released = false;
			}
			this->mouse1pressed = false;
		}
	}
}

bool cMouse::CheckPos(int x, int y, int w, int h)
{
	int position[VECTOR2D] = { (m_info[X]), (m_info[Y]) };
	return(position[X] > x && w + x > position[X] && position[Y] > y && h + y > position[Y]);
}

void cMouse::UpdatePos()
{

	GetCursorPos(&mPos);

	aMouse.myPos = mPos;

	aMouse.DrawMouse((LONG)mPos.x, (LONG)mPos.y);

}

bool cMouse::LeftClick(int x, int y,int w,int h){

	if( mouse1released &&
		mPos.x > x  && 
		w+x > mPos.x&& 
		mPos.y > y  && 
		h+y > mPos.y )
		return true;
	else
		return false;
}