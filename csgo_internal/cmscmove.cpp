#include "Cheat.h"
#include "enginepred.h"


CreateMoveFn oCreateMove;
CPredictionSystem PredictionSystem;
BackTrack backtracking;

int edgeflag;


bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* cmd)
{
    g::cmd = cmd;
    g::local_player = i::ClientEntList->GetClientEntity(i::Engine->GetLocalPlayer());
    if (g::local_player) g::weapon = g::local_player->get_weapon();

    if (cmd->command_number == 0) //na koncu i tak widac, nie wiem czy na halftime
    {
        if (g::local_player && g::local_player->is_alive())
            i::Engine->SetViewAngles(&g::cmd->viewangles);

        return oCreateMove(flInputSampleTime, cmd);
    }

    if (g::local_player && i::Engine->IsInGame())
    {
        if (!(g::local_player->get_movetype() & MOVETYPE_NOCLIP) && !(g::local_player->get_movetype() & MOVETYPE_LADDER))
        {
            if (v.misc.auto_jump) E::Misc->auto_jump();
            cmd->buttons |= IN_BULLRUSH;
        }

        if (g::PressedKeys[0x9]) E::Misc->rank_reveal();
        if (v.misc.clantag) E::Misc->clantag_changer();


        if (g::local_player->is_alive() && g::weapon)
        {
            if (v.misc.getout && cmd->tick_count % 32 == 0) i::Engine->ClientCmd_Unrestricted("getout");


            edgeflag = g::local_player->get_flags();

            PredictionSystem.StartPrediction(cmd);

            


             if (v.legitbot.enabled)
            {
                if (v.legitbot.backtrack > 19) backtracking.legitBackTrack(cmd);
                if (g::weapon->is_gun() && !v.misc.menu)
                {
                    legitbot.run();
                }
            }


            //   if (g::PressedKeys[0x2] && edgeflag & FL_ONGROUND && !(g::local_player->get_flags() & FL_ONGROUND)) //edge
                  // cmd->buttons |= IN_JUMP;

           


            PredictionSystem.EndPrediction();


        }

        cmd->viewangles.normalize17(); // test przy jakich while loop sie wypierdala
        cmd->sidemove = std::clamp(cmd->sidemove, -450.f, 450.f);
        cmd->forwardmove = std::clamp(cmd->forwardmove, -450.f, 450.f);

        i::Engine->SetViewAngles(&g::cmd->viewangles);
        return true;
    }
    else return oCreateMove(flInputSampleTime, cmd);
}

