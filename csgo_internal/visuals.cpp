#include "Cheat.h"
#include "listener.h"




Color Rainbow()
{
    static uint32_t cnt = 25;
    float freq = .02f;// ; //do menu nwm zajebane

    Color color = Color(
        std::sin(freq*cnt + 0) * 127 + 128,
        std::sin(freq*cnt + 2) * 127 + 128,
        std::sin(freq*cnt + 4) * 127 + 128,
        255);

    cnt++;

    return color;
}


void c_esp::Run()
{

    i::Engine->GetScreenSize(g::screenx, g::screeny);

    if (!i::Engine->IsInGame() || !g::local_player || !(g::local_player->get_team() == 2 || g::local_player->get_team() == 3))
    {
        draw::DrawString16(font::esp2, g::screenx - 11, 11, Rainbow(), FONT_RIGHT, "lachen machen");
        hitmarker::singleton()->_curtime = 0.f;
        hitmarker::singleton()->_dmg = 0; //jakis turbo chcek na ten sam mecz po serwer id 
        footsteps.clear(); return;
    }

    if (g::local_player->is_alive() && g::weapon)
    {
        auto weapon_id = g::weapon->get_item_def_index();

        *(bool*)offsets.s_bOverridePostProcessingDisable = true;

        if (g::weapon->is_grenade_id(weapon_id)) grenade_prediction();

        /*
        matrix3x4a_t ecksdee[128];
        g::local_player->setup_bones(ecksdee);

        for (int i = 0; i < 128; i++) {
            draw::DrawString(font::esp1, 350, (i*12), Color::White(), FONT_CENTER, "bone %i -> x: %f | y: %f | z: %f",
                i, ecksdee[i][0][3], ecksdee[i][1][3], ecksdee[i][2][3]);


            static vector w;
            if (!draw::w2s(vector(ecksdee[i][0][3], ecksdee[i][1][3], ecksdee[i][2][3]), w)) continue;
            draw::DrawString(font::esp1, w.x, w.y, Color::White(), FONT_CENTER, "%i",i);


        }*/
    }

    if (!v.esp.world_text)
    {
        auto ents = i::ClientEntList->GetHighestEntityIndex();
        for (int i{ 85 }; i <= ents; ++i) //84 zawsze puste na botach
        {
            auto entity = i::ClientEntList->GetClientEntity(i);
            if (!entity) continue;

            //  if(entity->get_client_class()->m_ClassID == CEnvTonemapController)// test
            //  {
              //    night((CEnvTonemapControllerd*)entity);
                 // break;
             // }

            if (entity->is_dormant()) continue;
            draw_world(entity);
        }
    }

    //nightmode cvarem
    if (v.esp.sound) soundesp();

    if (v.esp.box)
    {
        for (int i{ 1 }; i <= 64; ++i)
        {
            auto entity = i::ClientEntList->GetClientEntity(i);
            if (!entity) continue;
            if (!entity->is_player()) continue;
            if (!entity->is_enemy()) continue;
            if (entity->is_dormant()) continue;
            if (!entity->is_alive()) continue;
            draw_player(entity);
        }
    }

   hitmarker();
     spectator_list();


    const auto textx = Color(255, 255, 255, 150);
    {
        //https://git.estate/scitor/SMod/src/commit/859cd6b469d9f236d3219bb6bfea6922ca88f227/game/client/vgui_netgraphpanel.cpp#L586
        static float last_fps = 58.f;
        auto m_Framerate = .9f * last_fps + .1f * i::globals->absoluteframetime;
        last_fps = m_Framerate;


        //ping
        auto n = i::Engine->GetNetChannelInfo();
        if (!n) return;
        static auto cvar = i::Cvar->FindVar("cl_updaterate");
        if (!cvar) return;

        auto m_AvgLatency = n->GetAvgLatency(FLOW_OUTGOING);
        auto cvarf = cvar->GetFloat();
        if (cvarf > 0.001f)
            m_AvgLatency += -.5f / cvarf;
        m_AvgLatency = max(0, m_AvgLatency);

        auto m_AvgPacketLoss = n->GetAvgLoss(FLOW_INCOMING);

        draw::DrawString(font::esp1, g::screenx / 2, g::screeny - 11, textx, FONT_CENTER, "awootism | fps: %i | rtt: %i | loss: %i",
            (int)(1.f / m_Framerate), (int)(m_AvgLatency * 1000.f), (int)(m_AvgPacketLoss*100.0f));
    }



    draw::DrawString(font::esp1, g::screenx / 2, g::screeny - 22, textx, FONT_CENTER, "dmg to teammates: %i", hitmarker::singleton()->_dmg); //listener na tk - reset po zmianie serwera na odpierdol, do wziecia z henia bo tunewmap sie zjebie


}

void c_esp::draw_player(CBaseEntity* entity)
{

    const auto coll = entity->get_collideable();
    const auto &trans = entity->get_matrix_transform();
    const auto min = coll->OBBMins(); const auto max = coll->OBBMaxs();
    // teehee >///<
    auto trvec = [&trans](const vector& in1) -> vector {
        return { //
            in1.Dot(trans.m_flMatVal[0]) + trans.m_flMatVal[0][3],
            in1.Dot(trans.m_flMatVal[1]) + trans.m_flMatVal[1][3],
            in1.Dot(trans.m_flMatVal[2]) + trans.m_flMatVal[2][3] };
    };

    vector points0(min.x, min.y, min.z), blb;
    if (!draw::w2s(trvec(points0), blb)) return;
    vector points3(max.x, max.y, max.z), flb;
    if (!draw::w2s(trvec(points3), flb)) return;
    vector points1(min.x, max.y, min.z), brb;
    if (!draw::w2s(trvec(points1), brb)) return;
    vector points2(max.x, max.y, min.z), frb;
    if (!draw::w2s(trvec(points2), frb)) return;
    vector points4(min.x, max.y, max.z), frt;
    if (!draw::w2s(trvec(points4), frt)) return;
    vector points5(min.x, min.y, max.z), brt;
    if (!draw::w2s(trvec(points5), brt)) return;
    vector points6(max.x, min.y, min.z), blt;
    if (!draw::w2s(trvec(points6), blt)) return;
    vector points7(max.x, min.y, max.z), flt;
    if (!draw::w2s(trvec(points7), flt)) return;

    vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

    auto left = flb.x; auto top = flb.y;
    auto right = flb.x; auto bottom = flb.y;

    for (int i = 0; i < 8; i++)
    {
        if (left > arr[i].x) left = arr[i].x;
        if (top < arr[i].y) top = arr[i].y;
        if (right < arr[i].x) right = arr[i].x;
        if (bottom > arr[i].y) bottom = arr[i].y;
    }

    int x = std::round(left); int y = std::round(bottom);
    int w = std::round(right - left);
    int h = std::round(top - bottom);

    auto clr_vis = Color::FromFloat(k.esp_visible);
    const auto outline_clr = Color(0, 0, 0, 225);



    i::Surface->DrawSetColor(clr_vis);
    i::Surface->DrawOutlinedRect(x, y, x + w, y + h);



    i::Surface->DrawSetColor(outline_clr);
    draw::DrawRect(x - 4, y + 1, 3, h - 2, outline_clr);

    auto health = entity->get_health();
    if (health < 100)
    {
        int hp = h - (h * health) / 100;

        int clr = health * 2.55f;
        i::Surface->DrawSetColor({ 255 - clr, clr, 10, 255 });
        i::Surface->DrawLine(x - 3, y + hp + 2, x - 3, y + h - 2);

        draw::DrawString16(font::esp2, x - 3, max(y + hp, y + 5), Color::White(), FONT_CENTER, "%i", health);
    }
    else
    {
        i::Surface->DrawSetColor(Color::Green());
        i::Surface->DrawLine(x - 3, y + 2, x - 3, y + h - 2);
        if (health != 100) draw::DrawString16(font::esp2, x - 3, y + 5, Color::White(), FONT_CENTER, "%i", health);
    }




    static player_info_t xd;
    i::Engine->GetPlayerInfo(entity->get_index(), &xd);
    auto center = x + w / 2;
    draw::DrawString(font::esp1, center, y - 6, clr_vis, FONT_CENTER, xd.szName);

    auto weapon = entity->get_weapon();
    if (!weapon) return;


    auto bottom2 = y + h;

    if (weapon->is_gun()) {

        int iClip = weapon->get_clip1();
        int iClipMax = weapon->get_weapon_data()->iMaxClip1;
        int width = (w * iClip) / iClipMax;

        int bary = bottom;
        bary += 2;
        i::Surface->DrawSetColor(outline_clr);
        i::Surface->DrawFilledRect(x + 1, bary, x + w - 1, bary + 3);

        i::Surface->DrawSetColor(185, 47, 65, 255);
        i::Surface->DrawLine(x + 2, bary + 1, x + width - 2, bary + 1);
        bottom2 += 4;
    }

    draw::DrawString16(font::esp2, center, bottom2 + 9, Color::White(), FONT_CENTER, weapon->get_weapon_name());

}

void c_esp::draw_world(CBaseEntity* entity)
{
    auto draw = [&entity](const Color& color, const char* text, bool light = false) {
        if (light)
        {
            static auto m_lifeState = U::NetVars->GetOffset("DT_BaseCSGrenadeProjectile", "m_nExplodeEffectTickBegin");
            if (*(int*)((int)entity + m_lifeState) > 1) return;
        }
        if (entity->GetRenderOrigin().IsZero()) return;
        static vector w;
        if (!draw::w2s(entity->GetRenderOrigin(), w)) return;
        draw::DrawString16(font::esp2, w.x, w.y, { color.r(), color.g(), color.b(), 200 }, FONT_CENTER, text);
        if (light) {
            auto dLight = i::Effects->CL_AllocDlight(entity->get_index());
            dLight->color.r = color.r(); dLight->color.g = color.g(); dLight->color.b = color.b();
            dLight->color.exponent = 5;
            dLight->origin = entity->GetRenderOrigin();;
            dLight->radius = 200.f;
            dLight->die = i::globals->curtime + 0.050f;

            auto eLight = i::Effects->CL_AllocElight(entity->get_index());
            eLight->color.r = color.r(); eLight->color.g = color.g(); eLight->color.b = color.b();
            eLight->color.exponent = 5;
            eLight->origin = entity->GetRenderOrigin();
            eLight->radius = 75;
            eLight->die = i::globals->curtime + 0.10f;
        }
    };

    //dist alpha do spastowania co do henia napisalem
    if (entity->get_owner() == -1) {
        const char* model_name = nullptr;
        switch (entity->get_client_class()->m_ClassID)
        {

        case CAK47: model_name = "ak47"; break;
        case CWeaponAug: model_name = "aug"; break;
        case CWeaponAWP: model_name = "awp"; break;
        case CWeaponBizon: model_name = "bizon"; break;
        case CWeaponElite: model_name = "elite"; break;
        case CWeaponFiveSeven: model_name = "five seven"; break;
        case CWeaponFamas: model_name = "famas"; break;
        case CWeaponGlock: model_name = "glock"; break;
        case CWeaponGalilAR: model_name = "galil"; break;
        case CWeaponG3SG1: model_name = "g3sg1"; break;
        case CWeaponMag7: model_name = "mag7"; break;
        case CWeaponM249: model_name = "m249"; break;
        case CWeaponMAC10: model_name = "mac10"; break;
        case CWeaponMP9: model_name = "mp9"; break;
        case CWeaponNOVA: model_name = "nova"; break;
        case CWeaponNegev: model_name = "negev"; break;
        case CWeaponP90: model_name = "p90"; break;
        case CWeaponSawedoff: model_name = "sawed off"; break;
        case CWeaponSCAR20: model_name = "scar20"; break;
        case CWeaponSG556: model_name = "sg553"; break;
        case CWeaponSSG08: model_name = "scout"; break;
        case CWeaponTec9: model_name = "tec9"; break;
        case CWeaponUMP45: model_name = "ump45"; break;
        case CWeaponXM1014: model_name = "xm1014"; break;
        case CWeaponTaser: model_name = "zeus"; break;
        case CWeaponP250: { model_name = i::ModelInfo->GetModelName(entity->get_model()); //zjebane ale dziala
            if (model_name[22] == 'p') model_name = "p250"; else model_name = "cz75"; break; }
        case CDEagle: { model_name = i::ModelInfo->GetModelName(entity->get_model());
            if (model_name[22] == 'd') model_name = "deagle"; else model_name = "revolver"; break; }
        case CWeaponMP7: {  model_name = i::ModelInfo->GetModelName(entity->get_model());
            if (model_name[23] == '5') model_name = "mp5"; else model_name = "mp7"; break; }
        case CWeaponHKP2000: {  model_name = i::ModelInfo->GetModelName(entity->get_model());
            if (model_name[22] == '2') model_name = "usp"; else model_name = "p2000"; break; }
        case CWeaponM4A1: { model_name = i::ModelInfo->GetModelName(entity->get_model());
            if (model_name[26] == 's') model_name = "m4a1"; else model_name = "m4a4"; break; }

        case CC4: draw(Color::bomb_clr(), "c4"); return;
        case CEconEntity: if (g::local_player->get_team() == 3) draw(Color::defuser_clr(), "defuser"); return;
        case CDecoyGrenade: draw(Color::LightBlue(), "decoy"); return;
        case CFlashbang: draw(Color::Blue(), "flash"); return;
        case CHEGrenade: draw(Color::Red(), "nade"); return;
        case CIncendiaryGrenade: draw(Color::Orange(), "incendiary"); return;
        case CMolotovGrenade: draw(Color::Orange(), "molotov"); return;
        case CSensorGrenade: draw(Color::Purple(), "tactical"); return;
        case CSmokeGrenade: draw(Color::Green(), "smoke"); return;


        default: return;
        }

        draw(Color::FromFloat(k.world_esp), model_name);
    }
    else //custom :_D
    {
        auto drxaw = [&entity](const Color& color, const char* text) {
            if (entity->GetRenderOrigin().IsZero()) return;
            static vector w;
            if (!draw::w2s(entity->GetRenderOrigin(), w)) return;
            auto owner = i::ClientEntList->GetClientEntity(entity->get_owner() & 0xFFF);
            if (owner) {
                if (owner->is_enemy())  draw::DrawString16(font::esp2, w.x, w.y, { color.r(), color.g(), color.b(), 200 }, FONT_CENTER, text);
                else {
                    w.y = std::roundf(w.y);
                    draw::DrawString16(font::esp2, w.x, w.y - 4, { color.r(), color.g(), color.b(), 200 }, FONT_CENTER, text);
                    static player_info_t woah; i::Engine->GetPlayerInfo(owner->get_index(), &woah);
                    draw::DrawString(font::esp2, w.x, w.y + 4, { color.r(), color.g(), color.b(), 200 }, FONT_CENTER, woah.szName); //nie 16 bo decoy xDD
                }
            }
        };
        switch (entity->get_client_class()->m_ClassID)
        {
        case CPlantedC4: {
            if (entity->bomb_ticking())
            {
                auto timer = entity->bomb_timer();
                if (timer > 0.f)
                {
                    static vector vScreen;
                    if (draw::w2s(entity->GetRenderOrigin(), vScreen))
                        draw::DrawString16(font::esp2, vScreen.x, vScreen.y, { 255,255,255,200 }, FONT_CENTER, "c4: %.2fs", timer);
                }
            }
            break;
        }
        case CBaseCSGrenadeProjectile: {
            auto name = i::ModelInfo->GetModelName(entity->get_model());
            if (name[21] == 'r')
                draw(Color::Red(), "nade", true);
            else draw(Color::Blue(), "flash", true); //blue do zmiany bo brzydko wyglada
            break;
        }
        case CMolotovProjectile: {
            auto name = i::ModelInfo->GetModelName(entity->get_model());
            if (name[20] == 'm') draw(Color::Orange(), "molotov", true);
            else draw(Color::Orange(), "incendiary", true);
            break;
        }
        case CSensorGrenadeProjectile: draw(Color::Purple(), "tactical", true); break; //130 ta lecacy
        case CSmokeGrenadeProjectile: draw(Color::Green(), "smoke", true); break; //134 smoke dymiacy

        case CDecoyProjectile: drxaw(Color::LightBlue(), "decoy"); break;
        case CInferno:
        {
            auto time = *(float*)((long)entity + 0x00000020); //m_nFireEffectTickBegin

            const auto molotov_throw_detonate_timea = i::Cvar->FindVar("inferno_flame_lifetime");
            auto fire = 7.f;
            if (molotov_throw_detonate_timea) fire = molotov_throw_detonate_timea->GetFloat();
            auto rem = (time + fire) - (i::globals->curtime);

            static vector vScreen;
            if (draw::w2s(entity->GetRenderOrigin(), vScreen))
                draw::DrawString16(font::esp2, vScreen.x, vScreen.y - 20, { 255,255,255,200 }, FONT_CENTER, "c4: %.2fs", rem);

            drxaw(Color::Red(), "fire"); break; //88 inc/molo palace
        }
        default: break;
        }
    }
}

int GetObserverMode()
{
    static auto m_lifeState = U::NetVars->GetOffset("DT_BasePlayer", "m_iObserverMode");

    return *(int*)((uintptr_t)g::local_player + m_lifeState);
    //OBS_MODE_IN_EYE	4	First person cam
    //OBS_MODE_CHASE	5	Chase cam, 3rd person cam, free rotation around the spectated target
}

void c_esp::spectator_list()
{
    // if (!g::local_player->is_alive())
      //   return;
     //if spec mode on person i nie zyjesz po prostu patrz kto obserwuje te osobe tez lkol jedna linie w ifie pod target

    bool alive = g::local_player->is_alive();
    //  bool observing = (!alive && (GetObserverMode() == 4 || GetObserverMode() == 5)); na koncu rundy jak kazdy zdechnie pokazuje wszystkich :cringe:
    bool observing = (!alive && GetObserverMode() == 4);
    auto localtarget = i::ClientEntList->GetClientEntityFromHandle(g::local_player->get_spec_target());


    int gowno{};
    static player_info_t xdxd;

    for (auto i{ 1 }; i <= 64; ++i)
    {
        auto entity = i::ClientEntList->GetClientEntity(i);
        if (!entity) continue;
        if (!entity->is_player()) continue;
        if (entity->is_alive()) continue;
        if (entity->is_dormant()) continue;

        if (alive)
        {
            auto target = i::ClientEntList->GetClientEntityFromHandle(entity->get_spec_target());
            if (g::local_player != target) continue;
        }
        else if (observing)
        {
            auto target = i::ClientEntList->GetClientEntityFromHandle(entity->get_spec_target());
            if (localtarget != target) continue;

        }


        i::Engine->GetPlayerInfo(i, &xdxd);
        draw::DrawString(font::esp1, g::screenx - 4, 23 + (10 * gowno++), Color::White(), FONT_RIGHT, xdxd.szName);
    }

}

void c_esp::grenade_prediction() //z uc zajebane, dodaj isbreakable i trace na ogien
{
    auto GetGrenadeDetonateTime = [](int item) {
        switch (item) {
        case weapon_flashbang: return 1.63f; //+interval po prostu ale psrawdzic na 128
        case weapon_hegrenade: return 1.63f;
        case weapon_tagrenade: return 5.13f;
        case weapon_incgrenade:
        case WEAPON_FIREBOMB:
        case weapon_molotov: {
            static auto molotov_throw_detonate_time = i::Cvar->FindVar("molotov_throw_detonate_time");
            return molotov_throw_detonate_time->GetFloat() + 0.13f;
        }
        default: return 3.13f;
        }
    };
    auto DrawLine = [&](const vector& start, const vector& end)
    {
        static vector startw2s; if (!draw::w2s(start, startw2s)) return;
        static vector endw2s; if (!draw::w2s(end, endw2s)) return;
        static auto clr = Color(255, 255, 255, 200);
        i::Surface->DrawSetColor(clr); //104, 151, 153
        i::Surface->DrawLine(std::round(startw2s.x), std::round(startw2s.y), std::round(endw2s.x), std::round(endw2s.y));
    };
    auto PhysicsClipVelocity = [](const vector& in, const vector& normal, vector& out, float overbounce) {
        int blocked = 0; float angle = normal[2];
        if (angle > 0) blocked |= 1; // floor
        if (!angle) blocked |= 2; // step
        float backoff = in.Dot(normal) * overbounce;
        for (int i = 0; i < 3; i++) {
            out[i] = in[i] - (normal[i] * backoff);
            if (out[i] > -0.1f && out[i] < 0.1f) out[i] = 0;
        }
        return blocked;
    };
    // draw::DrawString(font::esp1, 720, 370, Color::White(), FONT_RIGHT, "%f", g::weapon->grenade_throw_strength());

    if (!g::weapon->grenade_pin_pulled()) return;
    // if (g::weapon->grenade_throw_time() != 0.f) return;

    auto weapon_data = g::weapon->get_weapon_data();
    if (!weapon_data) return;
    auto item_index = g::weapon->get_item_def_index();
    QAngle viewangles;
    i::Engine->GetViewAngles(viewangles);
    viewangles.x = std::remainderf(viewangles.x, 360.f);
    viewangles.x -= (90.f - fabsf(viewangles.x)) * 0.11111111f;
    vector forward; math::angle_vectors(viewangles, &forward);
    auto throw_strength = g::weapon->grenade_throw_strength();
    auto throw_velocity = fmin(fmax(weapon_data->flThrowVelocity * 0.9f, 15.f), 750.f);
    auto throw_height = (throw_strength * 12.f) - 12.f;
    auto v68 = throw_velocity * ((.7f * throw_strength) + .3f);
    vector startPos = g::local_player->get_eye_pos() + vector(0, 0, throw_height), endPos = startPos + (forward * 22.f);
    CTraceFilter filter;// (g::local_player, 0);
    filter.pSkip = g::local_player;
    trace_t trace;
    Ray_t lol;
    const vector hull_min(-2.f, -2.f, -2.f);
    const vector hull_max(2.f, 2.f, 2.f);
    lol.Init(startPos, endPos, hull_min, hull_max);
    i::trace->trace_ray(lol, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);
    endPos = trace.endpos - (forward * 6.f);
    auto throwPos = (g::local_player->get_velocity() * 1.25f) + (forward * v68);
    DrawLine(startPos, endPos);
    static auto sv_gravity = i::Cvar->FindVar("sv_gravity");
    float gravity = (sv_gravity->GetFloat() * .4f);
    auto interval = i::globals->interval_per_tick;
    bool draw_first = false;
    for (int ticks = TIME_TO_TICKS(GetGrenadeDetonateTime(item_index)); ticks >= 0; --ticks)
    {
        auto throwDir = vector(throwPos.x, throwPos.y, (throwPos.z + (throwPos.z - (gravity * interval))) * .5f);
        auto temp = throwDir * interval;
        throwPos.z -= gravity * interval;
        auto src = endPos, end = endPos + temp;
        Ray_t kurdee;
        kurdee.Init(src, end, hull_min, hull_max);
        i::trace->trace_ray(kurdee, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);
        if (trace.allsolid) throwPos = vector(0.f, 0.f, 0.f);
        endPos = trace.endpos;
        if (draw_first)
            DrawLine(src, endPos);
        if (trace.fraction != 1.f)
        {
            draw_first = true;
            static vector endw2s;
            if (draw::w2s(endPos, endw2s))
            {
                i::Surface->DrawSetColor(Color::Red());//  
                int x = std::round(endw2s.x);
                int y = std::round(endw2s.y);
                i::Surface->DrawOutlinedRect(x - 2, y - 2, x + 3, y + 3);
            }
            float surfaceElasticity = 1.f;
            vector throwPos2;
            PhysicsClipVelocity(throwPos, trace.plane.normal, throwPos2, 2.f);
            throwPos2 *= std::clamp(surfaceElasticity * .45f, 0.f, .9f);
            end = endPos + (throwPos2 * ((1.f - trace.fraction) * interval));
            if (item_index == weapon_molotov || item_index == weapon_incgrenade) //if do ziemi <= ~130 narysuj linie w dol
            {
                static auto weapon_molotov_maxdetonateslope = i::Cvar->FindVar("weapon_molotov_maxdetonateslope");
                if (!weapon_molotov_maxdetonateslope) return;
                if (trace.plane.normal.z >= cos(DEG2RAD(weapon_molotov_maxdetonateslope->GetFloat()))) return;
            }
            if (item_index == weapon_tagrenade) return;
            Ray_t jabab;
            jabab.Init(endPos, end, hull_min, hull_max);
            i::trace->trace_ray(jabab, MASK_SOLID | CONTENTS_CURRENT_90, &filter, &trace);
            DrawLine(endPos, end);
            endPos = trace.endpos;
            throwPos = throwPos2;
        }
    }
}

void c_esp::hitmarker()
{
    static auto alpha = 0.f;
    auto step = 600.f * i::globals->frametime;
    if (hitmarker::singleton()->_curtime + .2f >= i::globals->curtime) alpha = 150.f;
    else alpha -= step;
    if (alpha < 0.f) return;

    static auto screenCenterX = g::screenx / 2, screenCenterY = g::screeny / 2;
    i::Surface->DrawSetColor(255, 255, 255, alpha);
    i::Surface->DrawLine(screenCenterX - 4, screenCenterY - 4, screenCenterX - 2, screenCenterY - 2);
    i::Surface->DrawLine(screenCenterX - 4, screenCenterY + 4, screenCenterX - 2, screenCenterY + 2);
    i::Surface->DrawLine(screenCenterX + 4, screenCenterY - 4, screenCenterX + 2, screenCenterY - 2);
    i::Surface->DrawLine(screenCenterX + 4, screenCenterY + 4, screenCenterX + 2, screenCenterY + 2);
}

void c_esp::soundesp()
{
    if (footsteps.empty()) return;
    Color playerColor = Color::White();
    vector pos2d;
    for (unsigned int i = 0; i < footsteps.size(); ++i)
    {
        auto diff = i::globals->curtime - footsteps[i].expiration;
        if (diff > .7f) {
            footsteps.erase(footsteps.begin() + i); continue;
        }

        if (!draw::w2s(footsteps[i].position, pos2d)) continue;

        auto percent = diff / .7f;

        playerColor.SetAlpha((1.f - percent) * 188);

        draw::DrawString16(font::esp2, pos2d.x, pos2d.y, playerColor, FONT_CENTER, "?");
    }
}

void c_esp::night(CEnvTonemapControllerd* pController)
{
  
    pController->IsUseCustomAutoExposureMin() = true;
    pController->IsUseCustomAutoExposureMax() = true;
    pController->GetCustomAutoExposureMin() = v.legitbot.fov_rifle;
    pController->GetCustomAutoExposureMax() = v.legitbot.fov_rifle;

}