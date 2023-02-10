#pragma once
#include "Cheat.h"
#include <vector>
struct GlowObject_t {
	CBaseEntity*	m_pEntity;					// 0
	vector			m_vGlowColor;				// 4
	float			m_flGlowAlpha;				// 16
	unsigned char   junk[16];					// 20
	bool			m_bRenderWhenOccluded;		// 36
	bool			m_bRenderWhenUnoccluded;	// 37
	bool			m_bFullBloomRender;			// 38
	unsigned char   junk2[13];				// 39
};
class CEnvTonemapControllerd;
struct Footstep
{
	Footstep(float a, vector b) : expiration(a), position(b) {}
	float expiration;
	vector position;
};

class c_esp
{
public:
	void Run();
	std::vector<Footstep> footsteps;
    int bttick;
private:

    void draw_player(CBaseEntity* entity);
	void draw_world(CBaseEntity* entity);

    void soundesp();

	void hitmarker();

	void spectator_list();

    void night(CEnvTonemapControllerd* pController);
	void grenade_prediction();




};

class kolorki
{
public:
	float esp_visible[3] = { 0.003f, 0.456f, 0.305f };

	float chams_visible[3] = { 0.003f, 0.456f, 0.305f };
	float chams_hidden[3] = { 0.497f, 0.f, 0.087f };


	float world_esp[3] = { 0.551f, 0.649f, 0.725f };

};
extern kolorki k;