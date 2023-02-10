#pragma once

namespace font
{
	extern HFont esp1;
	extern HFont esp2;
	extern HFont spec;
}

namespace draw
{
	extern void SetupFonts( );
	extern void DrawString(const HFont& font, int x, int y, const Color& color, short alignment, const char* msg, ...);
	extern void DrawString16(const HFont& font, int x, int y, const Color& color, short alignment, const char* msg, ...);

	extern void DrawStringUnicode( HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ... );
	extern void DrawRect( int x, int y, int w, int h, Color col );
	extern void DrawRectRainbow( int x, int y, int w, int h, float flSpeed, float &flRainbow );
	extern void DrawRectGradientVertical( int x, int y, int w, int h, Color color1, Color color2 );
	extern void DrawRectGradientHorizontal( int x, int y, int w, int h, Color color1, Color color2 );
	extern void DrawPixel( int x, int y, Color col );
	extern void DrawOutlinedRect( int x, int y, int w, int h, Color col );
	extern void DrawFilledCircle(Vector2D center, Color color, Color outline, float radius, float points);
	extern void DrawOutlinedCircle( int x, int y, int r, Color col );
	extern void DrawLine( int x0, int y0, int x1, int y1, Color col );
	extern void DrawCorner( int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw );
	extern void DrawRoundedBox( int x, int y, int w, int h, int r, int v, Color col );
	extern void DrawPolygon( int count, Vertex_t* Vertexs, Color color );
	extern bool ScreenTransform( const vector &point, vector &screen );
	extern bool w2s( const vector &origin, vector &screen );
	extern int GetStringWidth( HFont font, const char* msg, ... );
	extern void Draw3DBox( vector* boxVectors, Color color );
	extern void DrawCircle( float x, float y, float r, float s, Color color );
}