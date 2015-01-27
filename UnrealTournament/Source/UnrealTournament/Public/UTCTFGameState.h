// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UTCTFFlagBase.h"
#include "UTCTFGameState.generated.h"

/** used to store a player in recorded match data so that we're guaranteed to have a valid name (use PlayerState if possible, string name if not) */
USTRUCT()
struct FSafePlayerName
{
	GENERATED_USTRUCT_BODY()

	friend uint32 GetTypeHash(const FSafePlayerName& N);

	UPROPERTY()
	AUTPlayerState* PlayerState;
protected:
	UPROPERTY()
	FString PlayerName;
public:
	/* FIXME: disabled because of engine level assertion
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		UObject* Data = PlayerState;
		bool bWriteName = !Map->SerializeObject(Ar, AUTPlayerState::StaticClass(), Data) || Data == NULL;
		PlayerState = Cast<AUTPlayerState>(Data);
		Ar << bWriteName;
		if (bWriteName)
		{
			Ar << PlayerName;
		}
		return true;
	}*/

	FSafePlayerName()
	: PlayerState(NULL)
	{}
	FSafePlayerName(AUTPlayerState* InPlayerState)
	: PlayerState(InPlayerState), PlayerName(InPlayerState != NULL ? InPlayerState->PlayerName : TEXT(""))
	{}

	inline bool operator==(const FSafePlayerName& Other) const
	{
		if (PlayerState != NULL || Other.PlayerState != NULL)
		{
			return PlayerState == Other.PlayerState;
		}
		else
		{
			return PlayerName == Other.PlayerName;
		}
	}

	FString GetPlayerName() const
	{
		return (PlayerState != NULL) ? PlayerState->PlayerName : PlayerName;
	}
};
/* FIXME: disabled because of engine level assertion
template<>
struct TStructOpsTypeTraits<FSafePlayerName> : public TStructOpsTypeTraitsBase
{
	enum
	{
		WithNetSerializer = true
	};
};*/
inline uint32 GetTypeHash(const FSafePlayerName& N)
{
	return GetTypeHash(N.PlayerName) + GetTypeHash(N.PlayerState);
}

USTRUCT()
struct FCTFScoringPlay
{
	GENERATED_USTRUCT_BODY()

	/** team that got the cap */
	UPROPERTY()
	AUTTeamInfo* Team;
	UPROPERTY()
	FSafePlayerName ScoredBy;
	UPROPERTY()
	TArray<FSafePlayerName> Assists;
	/** elapsed time in seconds when the cap happened */
	UPROPERTY()
	int32 ElapsedTime;
	/** period in which the cap happened (0 : first half, 1 : second half, 2+: OT) */
	UPROPERTY()
	uint8 Period;

	FCTFScoringPlay()
	: Team(NULL), ElapsedTime(0), Period(0)
	{}
	FCTFScoringPlay(const FCTFScoringPlay& Other) = default;

	inline bool operator==(const FCTFScoringPlay& Other) const
	{
		return (Team == Other.Team && ScoredBy == Other.ScoredBy && Assists == Other.Assists && ElapsedTime == Other.ElapsedTime && Period == Other.Period);
	}
};

UCLASS()
class UNREALTOURNAMENT_API AUTCTFGameState: public AUTGameState
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly,Replicated,Category = CTF)
	uint32 bSecondHalf : 1;

	UPROPERTY(BlueprintReadOnly,Replicated,ReplicatedUsing=OnHalftimeChanged, Category = CTF)
	uint32 bHalftime : 1;

	UPROPERTY(BlueprintReadOnly,Replicated,Category = CTF)
	uint32 bAllowSuddenDeath : 1;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = CTF)
	TArray<AUTCTFFlagBase*> FlagBases;

	/** Will be true if the game is playing advantage going in to half-time */
	UPROPERTY(Replicated)
	uint32 bPlayingAdvantage : 1;

	UPROPERTY(Replicated)
	uint8 AdvantageTeamIndex;

	/** Sets the # of teams.  This will also Pre-seed FlagsBases */
	virtual void SetMaxNumberOfTeams(int TeamCount);

	/** Cache a flag by in the FlagBases array */
	virtual void CacheFlagBase(AUTCTFFlagBase* BaseToCache);

	/** Returns the current state of a given flag */
	virtual FName GetFlagState(uint8 TeamNum);

	virtual AUTPlayerState* GetFlagHolder(uint8 TeamNum);
	virtual AUTCTFFlagBase* GetFlagBase(uint8 TeamNum);

	virtual void ResetFlags();

	/** Find the current team that is in the lead */
	virtual AUTTeamInfo* FindLeadingTeam();

	virtual bool IsMatchInProgress() const;
	virtual bool IsMatchInOvertime() const;

	UFUNCTION(BlueprintCallable, Category = GameState)
	virtual bool IsMatchInSuddenDeath() const;
	
	UFUNCTION(BlueprintCallable, Category = GameState)
	bool IsMatchAtHalftime() const;

	virtual FName OverrideCameraStyle(APlayerController* PCOwner, FName CurrentCameraStyle);
	
	UFUNCTION()
	virtual void OnHalftimeChanged();
private:
	/** list of scoring plays
	 * replicating dynamic arrays is dangerous for bandwidth and performance, but the alternative in this case is some painful code so we're as safe as possible by tightly restricting access
	 */
	UPROPERTY(Replicated)
	TArray<FCTFScoringPlay> ScoringPlays;

public:
	inline const TArray<const FCTFScoringPlay>& GetScoringPlays() const
	{
		return *(const TArray<const FCTFScoringPlay>*)&ScoringPlays;
	}
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Scoring)
	virtual void AddScoringPlay(const FCTFScoringPlay& NewScoringPlay);

	virtual FText GetGameStatusText();

};