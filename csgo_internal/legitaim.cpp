#include "LegitBot.h"
c_legitbot legitbot;

bool c_legitbot::get_hitbox_pos(int hitbox, vector& output, CBaseEntity* entity, const studiohdr_t* hdr)
{
    auto box = hdr->pHitbox(hitbox, entity->get_hitbox_set());
    if (!box) return false;

    vector min, max;
    math::VectorTransform(box->bbmin, bones_legit[box->bone], min);
    math::VectorTransform(box->bbmax, bones_legit[box->bone], max);
    output = (min + max) * .5f;

    if (output.IsZero()) return false; //?
    return true;
}

bool c_legitbot::goes_thru_smoke(const vector& pos2)
{
    using thru_smoke_fn = bool(__cdecl*)(float, float, float, float, float, float, short);
    static auto yea = (thru_smoke_fn)(offsets.LineGoesThroughSmoke);

    return yea(eye_position.x, eye_position.y, eye_position.z, pos2.x, pos2.y, pos2.z, 1);
}

bool c_legitbot::is_visible(const vector& end, CBaseEntity* entity)
{
    Ray_t ray;
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = g::local_player;

    ray.Init(eye_position, end);
    i::trace->trace_ray(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &trace);

    return (trace.entity == entity);
}

void c_legitbot::run()
{
    if (!g::PressedKeys[0x1]) return;

    if (g::weapon->is_empty() || g::weapon->is_reloading()) return;
    if (i::globals->curtime < g::local_player->get_next_attack()) return;

    get_settings();

    if (m_sniper)
    {
        if (!g::local_player->is_scoped()) return;
        if (i::globals->curtime < g::weapon->get_next_primary_attack()) return; //z auto? lol nwm, ale za to z pistoletami zwyklymi ma sens ;)
    }

    vector hitbox_position;
    if (!find_target(hitbox_position, m_fov)) return;

    auto aim_angle = math::calc_angle(eye_position, hitbox_position).normalize17();

    aim_angle -= randomized_recoil(); //super kopia kurwo zmien na referencje
    aim_angle += randomized_angles();

    auto delta = (g::cmd->viewangles - aim_angle).normalize17();
    if (m_smooth < 1.f) m_smooth = 1.f;
    auto angle = g::cmd->viewangles - (delta / m_smooth);

    g::cmd->viewangles = angle;
}

QAngle c_legitbot::randomized_recoil()
{
    m_rcs = std::clamp(U::exports::RandomFloat(m_rcs - 5.f, m_rcs + 5.f), 1.f, 100.f);

    auto punchAngles = g::local_player->get_aim_punch() * recoil_scale->GetFloat() * (m_rcs * 0.01f);
    return (g::local_player->get_shots_fired() > 1 ? punchAngles : QAngle(0.f, 0.f, 0.f));
}


QAngle c_legitbot::randomized_angles() //fajne malo instrukcji :-DD
{
    QAngle rand_angle(0.f, 0.f, 0.f);

    float rand1 = U::random_float(-m_rand, m_rand);
    float rand2 = U::random_float(-m_rand, m_rand);

    switch (rand() % 2) {
    case 0:
        rand_angle.x = (rand1 * cosf(rand2));
        rand_angle.y = (rand1 * cosf(rand2));
        break;
    case 1:
        rand_angle.x = (rand1 * sinf(rand2));
        rand_angle.y = (rand1 * sinf(rand2));
        break;
    }

    return (g::local_player->get_shots_fired() > 1 ? rand_angle : QAngle(0.f, 0.f, 0.f));
}


bool c_legitbot::get_closest_hitbox(CBaseEntity* entity, vector& hitbox_pos, float fov)
{
    const int hitboxes[] = { HITBOX_HEAD, HITBOX_NECK, HITBOX_CHEST, HITBOX_BODY, HITBOX_THORAX, HITBOX_PELVIS };

    if (m_hitscan)
    {
        bool found = false;
        float best_fov = fov;
        static vector bestangle;

        auto hdr = i::ModelInfo->GetStudioModel(entity->get_model());
        if (!hdr) return false;

        for (auto i{ 0 }; i < 6; ++i)
        {
            static vector temp;
            if (!get_hitbox_pos(hitboxes[i], temp, entity, hdr)) continue;

            if (!is_visible(temp, entity)) continue;
            if (goes_thru_smoke(temp)) continue;

            //-punch?
            float fov = math::get_fov(g::cmd->viewangles, math::calc_angle(eye_position, temp));

            if (fov < best_fov)
            {
                best_fov = fov;
                bestangle = temp;
                found = true;
            }
        }
        if (found)
        {
            hitbox_pos = bestangle;
            return true;
        }
        else return false;
    }
    else
    {
        static vector temp;

        auto hdr = i::ModelInfo->GetStudioModel(entity->get_model());
        if (!hdr) return false;

        if (!get_hitbox_pos(m_hitbox, temp, entity, hdr)) return false;

        if (!is_visible(temp, entity)) return false;
        if (goes_thru_smoke(temp)) return false;

        if (fov > math::get_fov(g::cmd->viewangles, math::calc_angle(eye_position, temp)))
        {
            hitbox_pos = temp;
            return true;
        }
    }

    return false;
}

bool c_legitbot::find_target(vector& hitbox, float fov)
{
    if (!recoil_scale) recoil_scale = i::Cvar->FindVar("weapon_recoil_scale");
    eye_position = g::local_player->get_eye_pos();
    auto viewangles = g::cmd->viewangles + (g::local_player->get_aim_punch() * recoil_scale->GetFloat());

    bool found = false;
    float best_fov = fov;



    for (auto i{ 1 }; i <= 64; ++i)
    {
        auto entity = i::ClientEntList->GetClientEntity(i);
        if (!entity) continue;
        if (!entity->is_player()) continue;
        if (!entity->is_enemy()) continue;
        if (entity->is_dormant()) continue;
        if (!entity->is_alive()) continue;
        if (entity->is_immune()) continue;
        if (!(entity->get_flags() & FL_ONGROUND)) continue;

        entity->setup_bones(bones_legit);
        vector hitbox_pos; 

        if (!get_closest_hitbox(entity, hitbox_pos, fov)) continue;
        
        auto cur_fov = math::get_fov(viewangles, math::calc_angle(eye_position, hitbox_pos)); //fov przez 2 cjuba ?  sprawdz potem

        if (cur_fov < best_fov)
        {
            best_fov = cur_fov;
            hitbox = hitbox_pos;
            found = true;
        }
    }

    return found;
}

void c_legitbot::get_settings()
{
    m_hitscan = false; m_sniper = false;
    auto get_hitbox = [&](int option) -> int {
        switch (option) {
        case 0: return HITBOX_HEAD;
        case 1: return HITBOX_NECK;
        case 2: return HITBOX_CHEST;
        case 3: return HITBOX_BODY;
        case 4: m_hitscan = true; return 0;
        default: return 0;
        }};

    switch (g::weapon->get_weapon_group(g::weapon->get_item_def_index()))
    {
    case wepgr::pistols:
        m_smooth = v.legitbot.smooth_pist; m_rcs = v.legitbot.rcs_pist;
        m_rand = 0.2f; m_fov = v.legitbot.fov_pist;
        m_hitbox = get_hitbox(v.legitbot.hitbox_pist); break;

    case wepgr::smgs:
        m_smooth = v.legitbot.smooth_smg; m_rcs = v.legitbot.rcs_smg;
        m_rand = 0.8f; m_fov = v.legitbot.fov_smg;
        m_hitbox = get_hitbox(v.legitbot.hitbox_smg); break;

    case wepgr::rifles:
        m_smooth = v.legitbot.smooth_rifle; m_rcs = v.legitbot.rcs_rifle;
        m_rand = 0.6f; m_fov = v.legitbot.fov_rifle;
        m_hitbox = get_hitbox(v.legitbot.hitbox_rifle); break;

    case wepgr::shotguns:
        m_smooth = v.legitbot.smooth_shot; m_rcs = v.legitbot.rcs_shot;
        m_rand = 1.f; m_fov = v.legitbot.fov_shot;
        m_hitbox = get_hitbox(v.legitbot.hitbox_shot); break;

    case wepgr::snipers:
        m_smooth = v.legitbot.smooth_snip; m_rcs = v.legitbot.rcs_snip;
        m_rand = 1.f; m_fov = v.legitbot.fov_snip;
        m_hitbox = get_hitbox(v.legitbot.hitbox_snip); m_sniper = true; break;

    case wepgr::autosnipers:
        m_smooth = v.legitbot.smooth_auto; m_rcs = v.legitbot.rcs_auto;
        m_rand = 0.8f; m_fov = v.legitbot.fov_auto;
        m_hitbox = get_hitbox(v.legitbot.hitbox_auto); m_sniper = true; break;
    }
}
