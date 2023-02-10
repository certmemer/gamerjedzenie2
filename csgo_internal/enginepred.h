#pragma once

class CMoveData {
public:
    bool			m_bFirstRunOfFunctions : 1;
    bool			m_bGameCodeMovedPlayer : 1;
    bool			m_bNoAirControl : 1;

    unsigned long	m_nPlayerHandle;
    int				m_nImpulseCommand;
    QAngle			m_vecViewAngles;
    QAngle			m_vecAbsViewAngles;
    int				m_nButtons;
    int				m_nOldButtons;
    float			m_flForwardMove;
    float			m_flSideMove;
    float			m_flUpMove;

    float			m_flMaxSpeed;
    float			m_flClientMaxSpeed;

    vector			m_vecVelocity;
    vector			m_vecOldVelocity;
    float			somefloat;
    QAngle			m_vecAngles;
    QAngle			m_vecOldAngles;

    float			m_outStepHeight;
    vector			m_outWishVel;
    vector			m_outJumpVel;

    vector			m_vecConstraintCenter;
    float			m_flConstraintRadius;
    float			m_flConstraintWidth;
    float			m_flConstraintSpeedFactor;
    bool			m_bConstraintPastRadius;

    void			SetAbsOrigin(const vector &vec);
    const vector	&GetAbsOrigin() const;

private:
    vector			m_vecAbsOrigin;		// edict::origin
};

class IMoveHelper {
private:
    virtual void UnknownVirtual() = 0;
public:
    virtual void SetHost(CBaseEntity* host) = 0;
};

extern IMoveHelper* g_pMoveHelper;

class IPrediction2 {
    // Construction
public:

    virtual ~IPrediction2(void) = 0;//

    virtual void Init(void) = 0;//
    virtual void Shutdown(void) = 0;//

                                    // Implement IPrediction
public:

    virtual void Update
    (
        int startframe, // World update ( un-modded ) most recently received
        bool validframe, // Is frame data valid
        int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
        int outgoing_command // Last command (most recent) sent to server (un-modded)
    );//

    virtual void PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);//
    virtual void PostEntityPacketReceived(void);//5
    virtual void PostNetworkDataReceived(int commands_acknowledged);//

    virtual void OnReceivedUncompressedPacket(void);//

                                                    // The engine needs to be able to access a few predicted values
    virtual void GetViewOrigin(vector& org);//
    virtual void SetViewOrigin(vector& org);//
    virtual void GetViewAngles(vector& ang);//10
    virtual void SetViewAngles(vector& ang);//

    virtual void GetLocalViewAngles(vector& ang);//
    virtual void SetLocalViewAngles(vector& ang);//

    virtual bool InPrediction(void) const;//14
    virtual bool IsFirstTimePredicted(void) const;//

    virtual int GetLastAcknowledgedCommandNumber(void) const;//

#if !defined( NO_ENTITY_PREDICTION )
    virtual int GetIncomingPacketNumber(void) const;//
#endif

    virtual void CheckMovingGround(IClientEntity* player, double frametime);//
    virtual void RunCommand(IClientEntity* player, CUserCmd* cmd, IMoveHelper* moveHelper);//

    virtual void SetupMove(CBaseEntity* player, CUserCmd* cmd, IMoveHelper* pHelper, CMoveData* move);//20
    virtual void FinishMove(CBaseEntity* player, CUserCmd* cmd, CMoveData* move);//
    virtual void SetIdealPitch(int nSlot, IClientEntity* player, const vector& origin, const vector& angles, const vector& viewheight);//

    virtual void CheckError(int nSlot, IClientEntity* player, int commands_acknowledged);//

public:
    virtual void _Update
    (
        int nSlot,
        bool received_new_world_update,
        bool validframe,            // Is frame data valid
        int incoming_acknowledged,  // Last command acknowledged to have been run by server (un-modded)
        int outgoing_command        // Last command (most recent) sent to server (un-modded)
    );

    // Actually does the prediction work, returns false if an error occurred
    bool PerformPrediction(int nSlot, IClientEntity* localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

    void ShiftIntermediateDataForward(int nSlot, int slots_to_remove, int previous_last_slot);

    void RestoreEntityToPredictedFrame(int nSlot, int predicted_frame);

    int ComputeFirstCommandToExecute(int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

    void DumpEntity(IClientEntity* ent, int commands_acknowledged);

    void ShutdownPredictables(void);

    void ReinitPredictables(void);

    void RemoveStalePredictedEntities(int nSlot, int last_command_packet);

    void RestoreOriginalEntityState(int nSlot);

    void RunSimulation(int current_command, float curtime, CUserCmd* cmd, IClientEntity* localPlayer);

    void Untouch(int nSlot);

    void StorePredictionResults(int nSlot, int predicted_frame);

    bool ShouldDumpEntity(IClientEntity* ent);

    void SmoothViewOnMovingPlatform(IClientEntity* pPlayer, vector& offset);

    void ResetSimulationTick();

    void ShowPredictionListEntry(int listRow, int showlist, IClientEntity* ent, int& totalsize, int& totalsize_intermediate);

    void FinishPredictionList(int listRow, int showlist, int totalsize, int totalsize_intermediate);

    void CheckPredictConvar();

#if !defined( NO_ENTITY_PREDICTION )

#endif
};

extern IPrediction2* g_pPrediction;

class CPredictionSystem {
public:
    void StartPrediction(CUserCmd* cmd);
    void EndPrediction();
    int backup_flags;


private:
    int backup_buttons;
    float backup_curtime;
    float backup_frametime;
    int backup_tickbase;

    CMoveData m_MoveData;

    int* m_pPredictionRandomSeed;
    int* m_pSetPredictionPlayer;
};

class IGameMovement {
public:
    virtual			~IGameMovement(void) {}

    virtual void	ProcessMovement(CBaseEntity *pPlayer, CMoveData *pMove) = 0;
    virtual void	Reset(void) = 0;
    virtual void	StartTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
    virtual void	FinishTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
    virtual void	DiffPrint(char const *fmt, ...) = 0;

    virtual vector const&	GetPlayerMins(bool ducked) const = 0;
    virtual vector const&	GetPlayerMaxs(bool ducked) const = 0;
    virtual vector const&   GetPlayerViewOffset(bool ducked) const = 0;

    virtual bool			IsMovingPlayerStuck(void) const = 0;
    virtual CBaseEntity*	GetMovingPlayer(void) const = 0;
    virtual void			UnblockPusher(CBaseEntity* pPlayer, CBaseEntity *pPusher) = 0;

    virtual void SetupMovementBounds(CMoveData *pMove) = 0;
};

extern IGameMovement* g_pGameMovement;