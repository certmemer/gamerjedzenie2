#pragma once

struct vars
{
	vars() {}

	struct
	{
		bool 	enabled;
		int		backtrack;

		float 	fov_pist = 3.5f;
		float	smooth_pist = 15.f;
		float 	rcs_pist = 45.f;
		int		hitbox_pist = 0;

		float 	fov_smg = 3.5f;
		float	smooth_smg = 15.f;
		float 	rcs_smg = 45.f;
		int		hitbox_smg = 0;

		float 	fov_rifle = 3.5f;
		float	smooth_rifle = 15.f;
		float 	rcs_rifle = 45.f;
		int		hitbox_rifle = 0;

		float 	fov_shot = 3.5f;
		float	smooth_shot = 15.f;
		float 	rcs_shot = 45.f;
		int		hitbox_shot = 0;

		float 	fov_snip = 3.5f;
		float	smooth_snip = 15.f;
		float 	rcs_snip = 45.f;
		int		hitbox_snip = 0;

		float 	fov_auto = 3.5f;
		float	smooth_auto = 15.f;
		float 	rcs_auto = 45.f;
		int		hitbox_auto = 0;
	} legitbot;

	struct
	{
		bool 	box;

		bool	world_text;
		bool	world_glow;

        bool sound;

		bool	chams_players;
		bool	chams_players_xqz;
	} esp;

	struct {
		bool 	auto_jump;


		bool	nightmode;

		bool	getout;

		bool	clantag;
		bool	clantag_rotate;
		bool	menu;




	} misc;
};

extern vars v;
