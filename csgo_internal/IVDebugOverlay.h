#pragma once

#define NDEBUG_PERSIST_TILL_NEXT_SERVER (0.01023f)

#define FMTFUNCTION( a, b )

class OverlayText_t;

class IVDebugOverlay
{
public:
	virtual void            __unkn() = 0;
	virtual void            AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void            AddBoxOverlay(const vector& origin, const vector& mins, const vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
	virtual void            AddSphereOverlay(const vector& vOrigin, float flRadius, int nTheta, int nPhi, int r, int g, int b, int a, float flDuration) = 0;
	virtual void            AddTriangleOverlay(const vector& p1, const vector& p2, const vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void            AddLineOverlay(const vector& origin, const vector& dest, int r, int g, int b, bool noDepthTest, float duration) = 0;
	virtual void            AddTextOverlay(const vector& origin, float duration, const char *format, ...) = 0;
	virtual void            AddTextOverlay(const vector& origin, int line_offset, float duration, const char *format, ...) = 0;
	virtual void            AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
	virtual void            AddSweptBoxOverlay(const vector& start, const vector& end, const vector& mins, const vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration) = 0;
	virtual void            AddGridOverlay(const vector& origin) = 0;
	virtual void            AddCoordFrameOverlay(const matrix3x4a_t& frame, float flScale, int vColorTable[3][3] = NULL) = 0;
	virtual int             ScreenPosition(const vector& point, vector& screen) = 0;
	virtual int             ScreenPosition(float flXPos, float flYPos, vector& screen) = 0;
	virtual OverlayText_t*  GetFirst(void) = 0;
	virtual OverlayText_t*  GetNext(OverlayText_t *current) = 0;
	virtual void            ClearDeadOverlays(void) = 0;
	virtual void            ClearAllOverlays() = 0;
	virtual void            AddTextOverlayRGB(const vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
	virtual void            AddTextOverlayRGB(const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
	virtual void            AddLineOverlayAlpha(const vector& origin, const vector& dest, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
	virtual void            AddBoxOverlay2(const vector& origin, const vector& mins, const vector& max, QAngle const& orientation, const uint8_t* faceColor, const uint8_t* edgeColor, float duration) = 0;
	virtual void            PurgeTextOverlays() = 0;
	virtual void            DrawPill(const vector& mins, const vector& max, float& diameter, int r, int g, int b, int a, float duration) = 0;

private:
	inline void AddTextOverlay(const vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) {} /* catch improper use of bad interface. Needed because '0' duration can be resolved by compiler to NULL format string (i.e., compiles but calls wrong function) */
};