#include "LegitBot.h"

void BackTrack::GetHitboxPosition2(CBaseEntity* entity, vector& pos) //srodek
{
    studiohdr_t* hdr = i::ModelInfo->GetStudioModel(entity->get_model());
    if (!hdr) return;
    mstudiobbox_t* box = hdr->pHitbox(0, entity->get_hitbox_set());
    if (!box) return;

    matrix3x4a_t ecksdee[128];
    entity->setup_bones(ecksdee);

    vector min, max;
    math::VectorTransform(box->bbmin, ecksdee[box->bone], min);
    math::VectorTransform(box->bbmax, ecksdee[box->bone], max);
    pos = (min + max) * 0.5f;
}

void BackTrack::legitBackTrack(CUserCmd* cmd) //pasta wyjebane
{
    const auto recoil_scale_cvarc = i::Cvar->FindVar("weapon_recoil_scale");
    auto recoil_scalec = recoil_scale_cvarc->GetFloat();

    int bestTargetIndex = -1;
    float bestFov = 100.f;
    auto hehe = cmd->viewangles + (g::local_player->get_aim_punch() * recoil_scalec);
    vector xdxd; xdxd.x = hehe.x; xdxd.y = hehe.y; xdxd.z = hehe.z;
    auto ViewDir = angle_vector(xdxd);

    auto poss = g::local_player->get_eye_pos();
    auto localteam = g::local_player->get_team();
    bool is_64tick = (i::globals->interval_per_tick == 0.015625f);

    bool attacking = (cmd->buttons & IN_ATTACK);
    auto xd = v.legitbot.backtrack  * 0.001f;
    auto ticks = int(xd / 0.015625f); //i?
    auto cmd_num = cmd->command_number % ticks;
    E::esp->bttick = cmd_num;// g::cmd->command_number % 12;



    for (int i = 1; i <= 64; ++i)
    {
        auto entity = i::ClientEntList->GetClientEntity(i);

        if (!entity) continue;
        if (!entity->is_player()) continue;
        if (!entity->is_enemy()) continue;
        if (entity->is_dormant()) continue;
        if (!entity->is_alive()) continue;

        auto simtime = entity->get_simulation_time();
        vector hitboxPos;

        GetHitboxPosition2(entity, hitboxPos);

        if (is_64tick) headPositions[i][cmd_num] = backtrackData{ simtime, hitboxPos };
        else if (cmd->tick_count % 2) headPositions[i][cmd_num] = backtrackData{ simtime, hitboxPos };

        if (attacking) //po co to robic jak nie atakujemy
        {
            auto FOVDistance = distance_point_to_line(hitboxPos, poss, ViewDir);
            if (bestFov > FOVDistance)
            {
                bestFov = FOVDistance;
                bestTargetIndex = i;
            }
        }
    }

    if (attacking && bestTargetIndex != -1)
    {
        float bestTargetSimTime;
        float tempFloat = 100.f;

        for (int t = 0; t < ticks; ++t)
        {
            auto tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].head_pos, poss, ViewDir);
            if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > g::local_player->get_simulation_time() - 1)
            {
                tempFloat = tempFOVDistance;
                bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
            }
        }

        cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
    }
}

backtrackData headPositions[65][12]; //kek