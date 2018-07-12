#include "Main.h"

CDrawing cDraw;

__forceinline int GetFontIndexByDistance(const float& distance)
{
	float copy = max(min(distance, 1000.f), 1.f);

	return (5 * (int)(copy / 1000.f));
}

void CDrawing::Text(bool cent, int font, int x, int y, Color color, wchar_t *pszString)
{
	if(cent)
	{
		int wide, tall;
		pSurface->GetTextSize(font, pszString, wide, tall);
		x -= wide / 2;
		y -= tall / 2;
	}
	pSurface->DrawSetTextColor( color );
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextPos(x, y);
	pSurface->DrawPrintText(pszString, (int)wcslen(pszString), FONT_DRAW_DEFAULT);
}

void CDrawing::DrawString(int FONT, bool bCenter, int x, int y, Color c, const char *fmt, ...) 
{
	wchar_t *pszStringWide = reinterpret_cast< wchar_t* >(malloc((strlen(fmt) + 1) * sizeof(wchar_t)));
	
	mbstowcs(pszStringWide, fmt, (strlen(fmt) + 1) * sizeof(wchar_t));

	Text(bCenter, FONT, x, y, c, pszStringWide);

	free(pszStringWide);
}

void CDrawing::String(int FONT, bool bCenter, int x, int y, Color c, const char *fmt, ... )
{
	va_list va_alist;
	char szBuffer[1024] = { '\0' };
	wchar_t wbuf[1024] = { '\0' };
	va_start( va_alist, fmt );
	vsprintf( szBuffer, fmt, va_alist );
	va_end( va_alist );
	wsprintfW( wbuf, L"%S", szBuffer );
	int iWidth, iHeight;
	pSurface->GetTextSize( FONT, wbuf, iWidth, iHeight );
	pSurface->DrawSetTextFont( FONT );
	pSurface->DrawSetTextColor(c);
	pSurface->DrawSetTextPos( x - ( bCenter ? iWidth / 2 : 0 ), y );
	pSurface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void CDrawing::NormalText(int font,int x,int y,Color c,const char *czText,...)
{
	if(czText == NULL)
		return;

	va_list va_alist;
	char buffer[1024] = { '\0' };
	wchar_t string[1024] = { '\0' };

	va_start(va_alist,czText);
	vsprintf(buffer,czText,va_alist);
	va_end(va_alist);

	MultiByteToWideChar( CP_UTF8, 0, buffer, 1024, string, 1024 );

	pSurface->DrawSetTextPos(x,y);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextColor(c);
	pSurface->DrawPrintText(string,wcslen(string));
}

void CDrawing::NormalTextCent(bool cent,int font,int x,int y,Color c,const char *czText,...)
{
	if(czText == NULL)
		return;

	va_list va_alist;
	char buffer[1024] = { '\0' };
	wchar_t string[1024] = { '\0' };

	va_start(va_alist,czText);
	vsprintf(buffer,czText,va_alist);
	va_end(va_alist);

	MultiByteToWideChar( CP_UTF8, 0, buffer, 1024, string, 1024 );

		if(cent)
	{
		int wide, tall;
		pSurface->GetTextSize2(font, czText, wide, tall);
		x -= wide / 2;
		y -= tall / 2;
	}

	pSurface->DrawSetTextPos(x,y);
	pSurface->DrawSetTextFont(font);
	pSurface->DrawSetTextColor(c);
	pSurface->DrawPrintText(string,wcslen(string));
}

void CDrawing::OutlinedRect(int x, int y, int w, int h, Color& color)
{
	pSurface->DrawSetColor(color);
	pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDrawing::FillRGBA( int x, int y, int w, int h, Color colour )
{
	pSurface->DrawSetColor( colour );
	pSurface->DrawFilledRect( x, y, x + w, y + h );
}

void CDrawing::FillRGBAFade( int x, int y, int w, int h,Color colour,unsigned int alpha0,unsigned alpha1,bool bHorizontal )
{
    pSurface->DrawSetColor( colour );
    pSurface->Fadenz( x, y, x + w, y + h,alpha0,alpha1,bHorizontal );
}

void CDrawing::Circle( int x, int y, int radius, int segments, Color color )
{
	pSurface->DrawSetColor(color); 
	pSurface->DrawOutlinedCircle( x, y, radius, segments );
}

int CDrawing::FrustumTransform( const matrix3x4 &worldToSurface, const Vector& point, Vector& screen )
{
	// UNDONE: Clean this up some, handle off-screen vertices
	float w;

	screen.x= worldToSurface[0][0] * point.x + worldToSurface[0][1] * point.y + worldToSurface[0][2] * point.z+ worldToSurface[0][3];
	screen.y = worldToSurface[1][0] * point.x + worldToSurface[1][1] * point.y + worldToSurface[1][2] * point.z + worldToSurface[1][3];
	//z = worldToSurface[2][0] * point[0] + worldToSurface[2][1] * point[1] + worldToSurface[2][2] * point[2] + worldToSurface[2][3];
	w = worldToSurface[3][0] * point.x + worldToSurface[3][1] * point.y + worldToSurface[3][2] * point.z + worldToSurface[3][3];

	// Just so we have something valid here
	screen.z = 0.0f;

	bool behind;
	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool CDrawing::WorldToScreen(Vector &origin, Vector &screen)
{
	bool bRet = false;
	float screenx, screeny;
	if (!cDraw.FrustumTransform(pEngine->WorldToScreenMatrix(),origin, screen))
	{
		int width, height;
		pEngine->GetScreenSize(width, height);

		screenx = width / 2;
		screeny = height / 2;

		screenx += 0.5f * screen.x * width + 0.5f;
		screeny -= 0.5f * screen.y * height + 0.5f;

		screen.x = screenx;
		screen.y = screeny;

		bRet = true;
	}

	return bRet;
}

bool CDrawing::TransformVector( Vector v, Vector &s ){
	if( cDraw.FrustumTransform(pEngine->WorldToScreenMatrix(), v, s ) == false ){
		int sw, sh;
		pEngine->GetScreenSize( sw, sh );
		float x = sw / 2;
		float y = sh / 2;
		x += 0.5 * s.x * sw + 0.5;
		y -= 0.5 * s.y * sh + 0.5;
		s.x = x;
		s.y = y;
		return true;
	}
	return false;
}

void CDrawing::DrawLine(int x, int y, int x1, int y1, Color clrColor)
{
	pSurface->DrawSetColor(clrColor);
	pSurface->DrawLine(x, y, x1, y1);
}

void CDrawing::DrawCornerBox(int x, int y, int w, int h, int borderPx, Color c)
{
	//Blackborder
	if(pCvars.BoxOutlineESP){
		FillRGBA((x - (w / 2)) - 1, (y - h + borderPx) - 1, (w / 3) + 2, borderPx + 2,Color( 0, 0, 0, 255)); //top
		FillRGBA((x - (w / 2) + w - w / 3) - 1, (y - h + borderPx) - 1, w / 3, borderPx + 2, Color( 0, 0, 0, 255)); //top
		FillRGBA(x - (w / 2) - 1, (y - h + borderPx), borderPx + 2, (w / 3) + 1, Color( 0, 0, 0, 255)); //left 
		FillRGBA(x - (w / 2) - 1, ((y - h + borderPx) + h - w / 3) - 1, borderPx + 2, (w / 3) + 2, Color( 0, 0, 0, 255)); //left 
		FillRGBA(x - (w / 2), y - 1, (w / 3) + 1, borderPx + 2, Color( 0, 0, 0, 255)); //bottom 
		FillRGBA(x - (w / 2) + w - (w / 3 + 1), y - 1, (w / 3) + 2, borderPx + 2, Color( 0, 0, 0, 255)); //bottom 
		FillRGBA((x + w - borderPx) - (w / 2) - 1, (y - h + borderPx) - 1, borderPx + 2, w / 3 + 2, Color( 0, 0, 0, 255)); //right 
		FillRGBA((x + w - borderPx) - (w / 2) - 1, ((y - h + borderPx) + h - w / 3) - 1, borderPx + 2, (w / 3) + 2, Color( 0, 0, 0, 255)); //right 
	}
	//Color
	FillRGBA(x - (w / 2), (y - h + borderPx), w / 3, borderPx, c); //top
	FillRGBA(x - (w / 2) + w - w / 3, (y - h + borderPx), w / 3, borderPx, c); //top
	FillRGBA(x - (w / 2), (y - h + borderPx), borderPx, w / 3, c); //left 
	FillRGBA(x - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3, c); //left 
	FillRGBA(x - (w / 2), y, w / 3, borderPx, c); //bottom 
	FillRGBA(x - (w / 2) + w - w / 3, y, w / 3, borderPx, c); //bottom 
	FillRGBA((x + w - borderPx) - (w / 2), (y - h + borderPx), borderPx, w / 3,c); //right 
	FillRGBA((x + w - borderPx) - (w / 2), (y - h + borderPx) + h - w / 3, borderPx, w / 3,c); //right 
}

RECT CDrawing::GetTextSize(DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	RECT rect; int x, y;
	pSurface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}

void CDrawing::DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
{
	Color colColor(0, 0, 0);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		FillRGBA(x + i, y, 1, height, colRainbow);
	}
}