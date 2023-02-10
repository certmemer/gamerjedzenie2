#include "Cheat.h"

HFont font::esp1;
HFont font::esp2;
HFont font::spec;

void draw::SetupFonts()
{ 

    i::Surface->SetFontGlyphSet(font::esp1 = i::Surface->Create_Font(), "Tahoma", 12, FW_DONTCARE, NULL, NULL, FONTFLAG_DROPSHADOW);
    i::Surface->SetFontGlyphSet(font::esp2 = i::Surface->Create_Font(), "Verdana", 11, 0, NULL, NULL, FONTFLAG_DROPSHADOW);

    

    i::Surface->SetFontGlyphSet(font::spec = i::Surface->Create_Font(), "Fixedsys Regular", 12, FW_DONTCARE, NULL, NULL, FONTFLAG_DROPSHADOW);
}
//const long& xDDDDDDDD 
void draw::DrawString(const HFont& font, int x, int y, const Color& color, short alignment, const char* msg, ...)
{
    va_list va_alist;
    static char buf[128];
    va_start(va_alist, msg);
    _vsnprintf(buf, 128u, msg, va_alist);
    va_end(va_alist);
    static wchar_t wbuf[128];
    MultiByteToWideChar(CP_UTF8, 0UL, buf, -1, wbuf, 128);

    int width, height;
    i::Surface->GetTextSize(font, wbuf, width, height);


    if (alignment & FONT_CENTER) x -= width / 2;
    else if (alignment & FONT_RIGHT) x -= width;

    i::Surface->DrawSetTextFont(font);
    i::Surface->DrawSetTextColor(color);
    i::Surface->DrawSetTextPos(x, y - height / 2);
    i::Surface->DrawPrintText(wbuf, wcslen(wbuf));
}
void draw::DrawString16(const HFont& font, int x, int y, const Color& color, short alignment, const char* msg, ...) //edbug
{
    va_list va_alist;
    static char buf[16];
    va_start(va_alist, msg);
    _vsnprintf(buf, 16u, msg, va_alist);
    va_end(va_alist);
    static wchar_t wbuf[16];
    MultiByteToWideChar(CP_UTF8, 0UL, buf, -1, wbuf, 16);
    int width, height;
    i::Surface->GetTextSize(font, wbuf, width, height);
    if (alignment & FONT_CENTER) x -= width / 2;
    else if (alignment & FONT_RIGHT) x -= width;
    i::Surface->DrawSetTextFont(font);
    i::Surface->DrawSetTextColor(color);
    i::Surface->DrawSetTextPos(x, y - height / 2);
    i::Surface->DrawPrintText(wbuf, wcslen(wbuf));
}
void draw::DrawStringUnicode(HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ...)
{
    int iWidth, iHeight;
    i::Surface->GetTextSize(font, msg, iWidth, iHeight);
    i::Surface->DrawSetTextFont(font);
    i::Surface->DrawSetTextColor(color);
    i::Surface->DrawSetTextPos(!bCenter ? x : x - iWidth * 0.5f, y - iHeight * 0.5f);
    i::Surface->DrawPrintText(msg, wcslen(msg));
}

void draw::DrawRect(int x, int y, int w, int h, Color col)
{
    i::Surface->DrawSetColor(col);
    i::Surface->DrawFilledRect(x, y, x + w, y + h);
}






void draw::DrawOutlinedRect(int x, int y, int w, int h, Color col)
{
    i::Surface->DrawSetColor(col);
    i::Surface->DrawOutlinedRect(x, y, x + w, y + h);
}







bool draw::ScreenTransform(const vector& point, vector& screen) // tots not pasted
{
    const VMatrix& worldToScreen = i::Engine->WorldToScreenMatrix();

    float w;
    screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
    screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
    w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
    screen.z = 0.0f;

    bool behind = false;

    if (w < 0.001f)
    {
        behind = true;
        screen.x *= 100000.f;
        screen.y *= 100000.f;
    }
    else
    {
        behind = false;
        float invw = 1.f / w;
        screen.x *= invw;
        screen.y *= invw;
    }

    return behind;
}

bool draw::w2s(const vector& origin, vector& screen)
{
    if (!ScreenTransform(origin, screen))
    {
        float x = g::screenx * 0.5f;
        float y = g::screeny * 0.5f; //globalne? 
        x += 0.5f * screen.x * g::screenx + 0.5f;
        y -= 0.5f * screen.y * g::screeny + 0.5f;
        screen.x = x;
        screen.y = y;
        return true;
    }

    return false;
}


