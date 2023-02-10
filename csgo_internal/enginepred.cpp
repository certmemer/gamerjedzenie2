#include "cheat.h"
#include "enginepred.h"

typedef UINT(__cdecl* MD5_PseudoRandom_t)(UINT);
static auto MD5_PseudoRandom = (MD5_PseudoRandom_t)U::FindPattern("client.dll", "55 8B EC 83 E4 F8 83 EC 70 6A 58");


void CPredictionSystem::StartPrediction(CUserCmd* cmd)
{
    static bool bInit = false;
    if (!bInit)
    {
        m_pPredictionRandomSeed = *(int**)(U::FindPattern("client.dll", "8B 0D ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 83 C4 04") + 2);
        m_pSetPredictionPlayer = *(int**)(U::FindPattern("client.dll", "89 35 ? ? ? ? F3 0F 10 48 20") + 2); //runcmd + 0x2d
        if (m_pPredictionRandomSeed && m_pSetPredictionPlayer)
            bInit = true;
    }

    backup_flags = g::local_player->get_flags();

    g::local_player->SetCurrentCommand(cmd);

    backup_curtime = i::globals->curtime;
    backup_frametime = i::globals->frametime;

    static CUserCmd* last_cmd;
    static int flTickBase;
    if (last_cmd) //??
    {
        if (last_cmd->hasbeenpredicted)
            flTickBase = g::local_player->get_tickbase();
        else
            ++flTickBase;
    }
    else
    {
        flTickBase = g::local_player->get_tickbase();
    }
    last_cmd = cmd;

    g_pMoveHelper->SetHost(g::local_player);
    auto reeeeee = MD5_PseudoRandom(cmd->command_number) & 0x7fffffff;
    *m_pPredictionRandomSeed = reeeeee;
    *m_pSetPredictionPlayer = (long)g::local_player;

    i::globals->curtime = flTickBase * i::globals->interval_per_tick;
    i::globals->frametime = i::globals->interval_per_tick;

    cmd->buttons |= *reinterpret_cast<byte*>(long(g::local_player) + 0x3310);
    if (cmd->impulse) *reinterpret_cast<byte*>(long(g::local_player) + 0x31EC) = cmd->impulse;

    m_MoveData.m_nButtons = cmd->buttons;
    int buttonsChanged = cmd->buttons ^ *reinterpret_cast<int*>(long(g::local_player) + 0x31E8);
    *reinterpret_cast<int*>(long(g::local_player) + 0x31DC) = (long(g::local_player) + 0x31E8);
    *reinterpret_cast<int*>(long(g::local_player) + 0x31E8) = cmd->buttons;
    *reinterpret_cast<int*>(long(g::local_player) + 0x31E0) = cmd->buttons & buttonsChanged;
    *reinterpret_cast<int*>(long(g::local_player) + 0x31E4) = buttonsChanged & ~cmd->buttons;

    g_pGameMovement->StartTrackPredictionErrors(g::local_player);

    backup_tickbase = g::local_player->get_tickbase();


    memset(&m_MoveData, 0, 184u);


    g_pPrediction->SetupMove(g::local_player, g::cmd, g_pMoveHelper, &m_MoveData);
    g_pGameMovement->ProcessMovement(g::local_player, &m_MoveData);
    g_pPrediction->FinishMove(g::local_player, g::cmd, &m_MoveData);
}

void CPredictionSystem::EndPrediction()
{
    *(int*)((long)this + offsets.m_nTickBase) = backup_tickbase;

    g_pGameMovement->FinishTrackPredictionErrors(g::local_player);


    g::local_player->SetCurrentCommand(nullptr);
    *m_pPredictionRandomSeed = -1;
    *m_pSetPredictionPlayer = 0;
    g_pMoveHelper->SetHost(nullptr);

    i::globals->curtime = backup_curtime;
    i::globals->frametime = backup_frametime;

    *g::local_player->SetFlags() = backup_flags;
}


/* movehelper 
.text:10283F48                 mov     ecx, dword_14F8CAF8 // movehelper +2 sig
.text:10283F4E                 mov     eax, [esi+8]
.text:10283F51                 push    offset aPlayer_swim ; "Player.Swim"
*/
/* m_pPredictionRandomSeed 
.text:1017AF7D                 mov     ecx, dword_10A65C04 // m_pPredictionRandomSeed +2 sig
.text : 1017AF83               mov     edx, offset aSelectweighted; "SelectWeightedSequence"
*/
/*MD5_PseudoRandom 
"CMemoryStack unattributed" i do gory
.text:106EDD41                 mov     ebp, esp <-
.text:106EDD43                 and     esp, 0FFFFFFF8h
*/