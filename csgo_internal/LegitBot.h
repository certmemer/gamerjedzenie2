#pragma once

#include "Cheat.h"
#include "ConVar.h"
#include "IVModelInfo.h"

class c_legitbot
{
public:
	void	run();
private:
	void	get_settings();
	bool	find_target(vector& hitbox, float fov);
	bool	get_closest_hitbox(CBaseEntity* entity, vector& hitbox_pos, float fov);

	bool	get_hitbox_pos(int hitbox, vector& output, CBaseEntity* entity, const studiohdr_t* hdr);
	bool	goes_thru_smoke(const vector& pos2);
	bool	is_visible(const vector& end, CBaseEntity* entity);

	QAngle	randomized_recoil();
	QAngle	randomized_angles();
private:
	float	m_fov;
	float	m_smooth;
	float	m_rcs;
	float	m_rand;
	int		m_hitbox;
	bool	m_hitscan;
	bool	m_sniper = false;
	vector	eye_position;
	matrix3x4a_t bones_legit[128];
	ConVar* recoil_scale = nullptr;
};
extern c_legitbot legitbot;



inline vector angle_vector(const vector& meme)
{
	auto sy = sin(meme.y / 180.f * M_PI_F);
	auto cy = cos(meme.y / 180.f * M_PI_F);

	auto sp = sin(meme.x / 180.f * M_PI_F);
	auto cp = cos(meme.x / 180.f* M_PI_F);

	return vector(cp*cy, cp*sy, -sp);
}
inline float distance_point_to_line(const vector& Point, const vector& LineOrigin, const vector& Dir)
{
	auto PointDir = Point - LineOrigin;

	auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
	if (TempOffset < 0.000001f)
		return FLT_MAX;

	auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);

	return (Point - PerpendicularPoint).Length();
}


struct backtrackData
{
	backtrackData() {}
	backtrackData(float simtimed, vector head_posd)
		: simtime(simtimed), head_pos(head_posd)
	{
	//	simtime = simtimed;
		//head_pos = head_posd;
		//memcpy(matrix->Base(), this->matrixd->Base(), 48u); //sizeof(float) * 3 * 4);

	}
	float simtime;
	vector head_pos;
	//matrix3x4a_t matrixd[128];
};

class BackTrack
{
public:
	void GetHitboxPosition2(CBaseEntity* entity, vector& pos);
	void legitBackTrack(CUserCmd * cmd);
};


extern backtrackData headPositions[65][12];
extern BackTrack backtracking;