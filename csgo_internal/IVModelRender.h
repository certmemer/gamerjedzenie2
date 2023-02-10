#pragma once

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial *mat);
	bool IsForcedMaterialOverride();
};
typedef void* FileNameHandle_t;
struct SndInfo_t
{
	int m_nGuid;
	FileNameHandle_t m_filenameHandle;
	int m_nSoundSource;
	int m_nChannel;

	int m_nSpeakerEntity;
	float m_flVolume;
	float m_flLastSpatializedVolume;

	float m_flRadius;
	int m_nPitch;
	vector *m_pOrigin;
	vector *m_pDirection;

	bool m_bUpdatePositions;
	bool m_bIsSentence;
	bool m_bDryMix;
	bool m_bSpeaker;
	bool m_bSpecialDSP;
	bool m_bFromServer;
};
class IEngineSound
{
public:
	// Precache a particular sample
	virtual bool PrecacheSound(const char *pSample, bool bPreload = false, bool bIsUISound = false) = 0;
	virtual bool IsSoundPrecached(const char *pSample) = 0;
	virtual void PrefetchSound(const char *pSample) = 0;
	virtual bool IsLoopingSound(const char *pSample) = 0;

	// Just loads the file header and checks for duration (not hooked up for .mp3's yet)
	// Is accessible to server and client though
	virtual float GetSoundDuration(const char *pSample) = 0;

	// Pitch of 100 is no pitch shift.  Pitch > 100 up to 255 is a higher pitch, pitch < 100
	// down to 1 is a lower pitch.   150 to 70 is the realistic range.
	// EmitSound with pitch != 100 should be used sparingly, as it's not quite as
	// fast (the pitchshift mixer is not native coded).

	// NOTE: setting iEntIndex to -1 will cause the sound to be emitted from the local
	// player (client-side only)
	virtual int EmitcSound(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
		float flVolume, float flAttenuation, int nSeed, int iFlags = 0, int iPitch = 0,
		const vector *pOrigin = NULL, const vector *pDirection = NULL, CUtlVector< vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual int EmitcSound(IRecipientFilter& filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample,
		float flVolume, int iSoundlevel, int nSeed, int iFlags = 0, int iPitch = 0,
		const vector *pOrigin = NULL, const vector *pDirection = NULL, CUtlVector< vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual void EmitSentenceByIndex(IRecipientFilter& filter, int iEntIndex, int iChannel, int iSentenceIndex,
		float flVolume, int iSoundlevel, int nSeed, int iFlags = 0, int iPitch = 0,
		const vector *pOrigin = NULL, const vector *pDirection = NULL, CUtlVector< vector >* pUtlVecOrigins = NULL, bool bUpdatePositions = true, float soundtime = 0.0f, int speakerentity = -1) = 0;

	virtual void    StopSound(int iEntIndex, int iChannel, const char *pSample, unsigned int nSoundEntryHash) = 0;
	virtual void    StopAllSounds(bool bClearBuffers) = 0;
	virtual void    SetRoomType(IRecipientFilter& filter, int roomType) = 0;
	virtual void    SetPlayerDSP(IRecipientFilter& filter, int dspType, bool fastReset) = 0;
	virtual int     EmitAmbientSound(const char *pSample, float flVolume, int iPitch = 0, int flags = 0, float soundtime = 0.0f) = 0;
	virtual float   GetDistGainFromSoundLevel(int soundlevel, float dist) = 0;
	virtual int		GetGuidForLastSoundEmitted() = 0;
	virtual bool	IsSoundStillPlaying(int guid) = 0;
	virtual void	StopSoundByGuid(int guid, bool bForceSync) = 0;
	virtual void	SetVolumeByGuid(int guid, float fvol) = 0;
	virtual void	GetActiveSounds(CUtlVector<SndInfo_t>& sndlist) = 0;
	virtual void	PrecacheSentenceGroup(const char *pGroupName) = 0;
	virtual void	NotifyBeginMoviePlayback() = 0;
	virtual void	NotifyEndMoviePlayback() = 0;
	virtual bool	GetSoundChannelVolume(const char* sound, float &flVolumeLeft, float &flVolumeRight) = 0;
	virtual float	GetElapsedTimeByGuid(int guid) = 0;
};
