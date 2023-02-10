#pragma once
#include "Cheat.h"
#include "Global.h"
class hitmarker //pasta z uc bo wyjebane
{
    class player_hurt_listener
        : public IGameEventListener2
    {
    public:
        void start()
        {
            i::Events->AddListener(this, "player_hurt", false);
            i::Events->AddListener(this, "game_newmap", false);
            i::Events->AddListener(this, "item_purchase", false);
            i::Events->AddListener(this, "round_start", false);
            i::Events->AddListener(this, "player_footstep", false);
        }
        void stop()
        {
            i::Events->RemoveListener(this);
        }
        void FireGameEvent(IGameEvent *event) override
        {
            hitmarker::singleton()->on_fire_event(event);
        }
        int GetEventDebugID(void) override
        {
            return 0x2a /*0x2A*/;
        }
    };
public:
    static hitmarker* singleton() { static hitmarker* instance = new hitmarker; return instance; }
    void initialize() { _listener.start(); }
    void remove() { _listener.stop(); }
    void on_fire_event(IGameEvent* event)
    {
        auto name = event->GetName();

        switch (name[0])
        {
        case 'i':
        {
            if (g::local_player && g::local_player->get_team() != event->GetInt("team"))
            {
                std::string asd2 = event->GetString("weapon");
                if (asd2[0] == 'i') break; //jebac itemki


                U::ConColorMsg(Color::Purple(), "[awoo] ");
                auto userid = i::Engine->GetPlayerForUserID(event->GetInt("userid"));
                static player_info_t info;
                i::Engine->GetPlayerInfo(userid, &info);
                std::string asd = info.szName; asd += " bought ";
                asd += asd2.substr(7);
                U::ConColorMsg(Color::text_clr(), "%s \n", asd.c_str());
            }
            break;
        }
        case 'p':
        {
            if (name[7] == 'h') //player hit?
            {
                auto local = i::Engine->GetLocalPlayer();
                auto attacker = i::Engine->GetPlayerForUserID(event->GetInt("attacker"));

                if (attacker == local)
                {
                    auto victim = i::Engine->GetPlayerForUserID(event->GetInt("userid"));

                    if (victim != local)
                    {
                        i::Engine->ClientCmd_Unrestricted("playvol buttons\\arena_switch_press_02.wav 0.1");
                        _curtime = i::globals->curtime;

                        {
                            auto ent = i::ClientEntList->GetClientEntity(victim);

                            if (ent && !ent->is_enemy())
                                _dmg += event->GetInt("dmg_health");
                        }
                    }
                }
            }
            else if (v.esp.sound && g::local_player) //nie wiem player footstep lol
            {
                auto local = i::Engine->GetLocalPlayer();
                auto entity = i::Engine->GetPlayerForUserID(event->GetInt("userid"));
                if (entity != local)
                {
                    auto ent = i::ClientEntList->GetClientEntity(entity);

                    if (ent && !ent->is_dormant() && ent->is_enemy())
                        E::esp->footsteps.emplace_back(Footstep(i::globals->curtime, ent->GetRenderOrigin()));
                }
            }
            break;
        }
        case 'r':
        {
            FLASHWINFO fi;
            fi.cbSize = sizeof(FLASHWINFO);
            fi.hwnd = g::Window;
            fi.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
            fi.uCount = 0;
            fi.dwTimeout = 0;
            FlashWindowEx(&fi);
            break;
        }
        case 'g':
        {
            newmap = true;
            break;
        }
        }
    }

public:
    float _curtime = 0.f;
    bool newmap = false;
    int	  _dmg = 0;
private:
    player_hurt_listener    _listener;
};



