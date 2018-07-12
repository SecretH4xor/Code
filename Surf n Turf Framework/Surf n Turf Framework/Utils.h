#pragma once
class CDrawing
{
public:

	#define RandomInt(min, max) (rand() % (max - min + 1) + min)

	void Text(bool cent, int font, int x, int y, Color color, wchar_t *pszString);
	void DrawString(int font,bool cent, int x, int y,Color col, const char* pszText, ...);
	void String( int FONT, bool bCenter, int x, int y, Color c, const char *fmt, ... );
	void NormalText(int font,int x,int y,Color c,const char *czText,...);
    void OutlinedRect(int x, int y, int w, int h, Color& color);
	void FillRGBA( int x, int y, int w, int h, Color colour );
	void FillRGBAFade( int x, int y, int w, int h,Color colour, unsigned int alpha0,unsigned alpha1,bool bHorizontal );	
	void Circle( int x, int y, int radius, int segments, Color color );
	int FrustumTransform( const matrix3x4 &worldToSurface, const Vector& point, Vector& screen );
	bool WorldToScreen(Vector &origin, Vector &screen);
	void NormalTextCent(bool cent,int font,int x,int y,Color c,const char *czText,...);
	void DrawLine(int x, int y, int x1, int y1, Color clrColor);
	bool TransformVector( Vector v, Vector &s );
	void DrawCornerBox(int x, int y, int w, int h, int borderPx, Color c);
	RECT GetTextSize(DWORD font, const char* text);
	void DrawRectRainbow(int x, int y, int w, int h, float flSpeed, float &flRainbow);
};
extern CDrawing cDraw;

extern int GetFontIndexByDistance(const float& distance);