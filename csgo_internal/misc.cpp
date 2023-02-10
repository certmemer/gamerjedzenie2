#include "Cheat.h"


void c_misc::auto_jump()
{
    static bool last_jumped = false;
    static bool should_fake = false;

    if (!last_jumped && should_fake)
    {
        should_fake = false;
        g::cmd->buttons |= IN_JUMP;
    }
    else if (g::cmd->buttons & IN_JUMP)
    {
        if (g::local_player->get_flags() & FL_ONGROUND)
        {
            last_jumped = true;
            should_fake = true;
        }
        else
        {
            last_jumped = false;
            g::cmd->buttons &= ~IN_JUMP;
        }
    }
    else
    {
        last_jumped = false;
        should_fake = false;
    }
}




void c_misc::rank_reveal()
{
    using rank_reveal_fn = bool(__cdecl*)(float*);
    static auto add = U::FindPattern("client.dll", "55 8B EC 8B 0D ? ? ? ? 85 C9 75 28 A1 ? ? ? ? 68 ? ? ? ? 8B 08 8B 01 FF 50 04 85 C0 74 0B 8B C8 E8 ? ? ? ? 8B C8 EB 02 33 C9 89 0D ? ? ? ? 8B 45 08");
    static float aaa[3] = { 0.f, 0.f, 0.f };
    reinterpret_cast<rank_reveal_fn>(add)(aaa);
}


bool odpierdol = false;
void c_misc::clantag_changer()
{
    auto change_tag = [](const char* tag) {
        static auto clantag = U::FindPattern("engine.dll", "53 56 57 8B DA 8B F9 FF 15");
        static auto clantag_fn = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(clantag);
        clantag_fn(tag, ">w<");
    };


    if (v.misc.clantag_rotate)
    {
        std::string strd(g::gamerfoodsuper); //globalne zmienne b potrzebne :)
        static std::string AaAAA(g::gamerfoodsuper);
        static std::string str(g::gamerfoodsuper);

        if (strd != AaAAA) //p
        {
            AaAAA = strd;
            str = strd;
            odpierdol = false;
        }
        if (!odpierdol)
        {
            str += "  ";
            odpierdol = true;
        }

        if (i::globals->tickcount % 32 == 0)
        {
            std::rotate(str.begin(), str.begin() + 1, str.end()); //XDDDDDDDD
            change_tag(str.c_str());
        }
    }
    else if (i::globals->tickcount % 64 == 0) change_tag(g::gamerfoodsuper);
}




 