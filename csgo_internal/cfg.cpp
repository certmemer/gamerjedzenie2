#include "Cheat.h"
#include <shlobj.h>

void CConfig::Setup()
{
    /////////////////////////////////////////////////////////////////////////////////// //skrocic nazwy ;D
    SetupValue(v.legitbot.enabled, false, "legitbot", "enabled");
    SetupValue(v.legitbot.backtrack, false, "legitbot", "backtrack");

    SetupValue(v.legitbot.fov_pist, 2.f, "legitbot", "fov_pist");
    SetupValue(v.legitbot.smooth_pist, 1.f, "legitbot", "smooth_pist");
    SetupValue(v.legitbot.rcs_pist, 30.f, "legitbot", "rcs_pist");
    SetupValue(v.legitbot.hitbox_pist, 0, "legitbot", "hitbox_pist");

    SetupValue(v.legitbot.fov_smg, 3.5f, "legitbot", "fov_smg");
    SetupValue(v.legitbot.smooth_smg, 35.f, "legitbot", "smooth_smg");
    SetupValue(v.legitbot.rcs_smg, 75.f, "legitbot", "rcs_smg");
    SetupValue(v.legitbot.hitbox_smg, 4, "legitbot", "hitbox_smg");

    SetupValue(v.legitbot.fov_rifle, 3.f, "legitbot", "fov_rifle");
    SetupValue(v.legitbot.smooth_rifle, 50.f, "legitbot", "smooth_rifle");
    SetupValue(v.legitbot.rcs_rifle, 60.f, "legitbot", "rcs_rifle");
    SetupValue(v.legitbot.hitbox_rifle, 4, "legitbot", "hitbox_rifle");

    SetupValue(v.legitbot.fov_shot, 3.5f, "legitbot", "fov_shot");
    SetupValue(v.legitbot.smooth_shot, 15.f, "legitbot", "smooth_shot");
    SetupValue(v.legitbot.rcs_shot, 50.f, "legitbot", "rcs_shot");
    SetupValue(v.legitbot.hitbox_shot, 2, "legitbot", "hitbox_shot");

    SetupValue(v.legitbot.fov_snip, 2.f, "legitbot", "fov_snip");
    SetupValue(v.legitbot.smooth_snip, 0.4f, "legitbot", "smooth_snip");
    SetupValue(v.legitbot.rcs_snip, 50.f, "legitbot", "rcs_snip");
    SetupValue(v.legitbot.hitbox_snip, 4, "legitbot", "hitbox_snip");

    SetupValue(v.legitbot.fov_auto, 3.5f, "legitbot", "fov_auto");
    SetupValue(v.legitbot.smooth_auto, 15.f, "legitbot", "smooth_auto");
    SetupValue(v.legitbot.rcs_auto, 50.f, "legitbot", "rcs_auto");
    SetupValue(v.legitbot.hitbox_auto, 3, "legitbot", "hitbox_auto");
    ///////////////////////////////////////////////////////////////////////////////////

    SetupValue(v.esp.box, false, "esp", "box");


    SetupValue(v.esp.world_text, false, "esp", "world_text");
    SetupValue(v.esp.world_glow, false, "esp", "world_glow");

    SetupValue(v.esp.chams_players, false, "esp", "chams_players");
    SetupValue(v.esp.chams_players_xqz, false, "esp", "chams_players_xqz");
    ///////////////////////////////////////////////////////////////////////////////////
    SetupValue(v.misc.auto_jump, false, "misc", "auto_jump");




    SetupValue(v.misc.nightmode, false, "misc", "nightmode");

    SetupValue(v.misc.getout, false, "misc", "getout");
    ///////////////////////////////////////////////////////////////////////////////////
    SetupValue(k.esp_visible[0], 0.533f, "colors", "esp_visible_r");
    SetupValue(k.esp_visible[1], 0.086f, "colors", "esp_visible_g");
    SetupValue(k.esp_visible[2], 0.086f, "colors", "esp_visible_b");

    SetupValue(k.chams_visible[0], 0.533f, "colors", "chams_visible_r");
    SetupValue(k.chams_visible[1], 0.086f, "colors", "chams_visible_g");
    SetupValue(k.chams_visible[2], 0.086f, "colors", "chams_visible_b");
    SetupValue(k.chams_hidden[0], 0.f, "colors", "chams_hidden_r");
    SetupValue(k.chams_hidden[1], 0.22f, "colors", "chams_hidden_g");
    SetupValue(k.chams_hidden[2], 0.153f, "colors", "chams_hidden_b");


    SetupValue(k.world_esp[0], 0.7215f, "colors", "world_esp_r");
    SetupValue(k.world_esp[1], 0.0070f, "colors", "world_esp_g");
    SetupValue(k.world_esp[2], 0.3176f, "colors", "world_esp_b");
    ///////////////////////////////////////////////////////////////////////////////////
}

void CConfig::SetupValue(int &value, int def, std::string category, std::string name)
{
    value = (int)def;
    ints.push_back(new ConfigValue<int>(category, name, &value));
}

void CConfig::SetupValue(float &value, float def, std::string category, std::string name)
{
    value = (float)def;
    floats.push_back(new ConfigValue<float>(category, name, &value));
}

void CConfig::SetupValue(bool &value, bool def, std::string category, std::string name)
{
    value = (bool)def;
    bools.push_back(new ConfigValue<bool>(category, name, &value));
}

void CConfig::Save(int i)
{
    static TCHAR path[MAX_PATH];
    std::string folder, file;

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
    {
        folder = std::string(path) + ("\\kek\\");

        switch (i)
        {
        case 0: file = folder + ("1.loli"); break;
        case 1: file = folder + ("2.loli"); break;
        case 2: file = folder + ("3.loli"); break;
        }
    }
    else return;

    CreateDirectory(folder.c_str(), NULL);

    for (auto value : ints)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

    for (auto value : floats)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

    for (auto value : bools)
        WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load(int i)
{
    static TCHAR path[MAX_PATH];
    std::string folder, file;

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, 0, path)))
    {
        folder = std::string(path) + ("\\kek\\");

        switch (i)
        {
        case 0: file = folder + ("1.loli"); break;
        case 1: file = folder + ("2.loli"); break;
        case 2: file = folder + ("3.loli"); break;
        }
    }
    else return;

    CreateDirectory(folder.c_str(), NULL);

    auto has_any_digits = [](const std::string& s) {
        return std::any_of(s.begin(), s.end(), ::isdigit);
    };

    for (auto value : ints)
    {
        char value_ld[64] = {};
        GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "0", value_ld, 64, file.c_str());

        auto data = std::string(value_ld);
        if (data.empty() || !has_any_digits(data)) *value->value = 0;
        else *value->value = std::stoi(data);
    }

    for (auto value : floats)
    {
        char value_lf[64] = {};
        GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "0.000", value_lf, 64, file.c_str());

        auto data = std::string(value_lf);
        if (data.empty() || !has_any_digits(data)) *value->value = 0.f;
        else *value->value = std::stof(data);
    }

    for (auto value : bools)
    {
        char value_lb[64] = {};
        GetPrivateProfileStringA(value->category.c_str(), value->name.c_str(), "false", value_lb, 64, file.c_str());

        auto data = std::string(value_lb);

        if (data.empty() || has_any_digits(data)) *value->value = false;
        else *value->value = !strcmp(value_lb, "true");
    }
}

CConfig* Config = new CConfig();
vars v;
