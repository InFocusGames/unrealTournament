// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UnrealTournament.h"
#include "UTHUD_DM.h"
#include "StatNames.h"
#include "UTMcpUtils.h"
#include "UTDMGameMode.h"


AUTDMGameMode::AUTDMGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	HUDClass = AUTHUD_DM::StaticClass();
	DisplayName = NSLOCTEXT("UTGameMode", "DM", "Deathmatch");
	XPMultiplier = 3.0f;
	bGameHasImpactHammer = false;
	bPlayersStartWithArmor = false;
}


void AUTDMGameMode::UpdateSkillRating()
{
	ReportRankedMatchResults(NAME_DMSkillRating.ToString());
}

void AUTDMGameMode::PrepareRankedMatchResultGameCustom(FRankedMatchResult& MatchResult)
{	
	// report the social party initial size
	MatchResult.RedTeam.SocialPartySize = 1;

	// In DM, all players go on the red team and IndividualScores is filled out
	for (int32 PlayerIdx = 0; PlayerIdx < UTGameState->PlayerArray.Num(); PlayerIdx++)
	{
		AUTPlayerState* PS = Cast<AUTPlayerState>(UTGameState->PlayerArray[PlayerIdx]);
		if (PS && !PS->bOnlySpectator)
		{
			FRankedTeamMemberInfo RankedMemberInfo;
			RankedMemberInfo.AccountId = PS->StatsID;
			RankedMemberInfo.IsBot = PS->bIsABot;
			if (PS->bIsABot)
			{
				RankedMemberInfo.AccountId = PS->PlayerName;
			}
			RankedMemberInfo.Score = PS->Score;
			MatchResult.RedTeam.Members.Add(RankedMemberInfo);
			MatchResult.RedTeam.SocialPartySize = FMath::Max(MatchResult.RedTeam.SocialPartySize, PS->PartySize);
		}
	}

	for (int32 PlayerIdx = 0; PlayerIdx < InactivePlayerArray.Num(); PlayerIdx++)
	{
		AUTPlayerState* PS = Cast<AUTPlayerState>(InactivePlayerArray[PlayerIdx]);
		if (PS && !PS->bOnlySpectator)
		{
			FRankedTeamMemberInfo RankedMemberInfo;
			RankedMemberInfo.AccountId = PS->StatsID;
			RankedMemberInfo.IsBot = PS->bIsABot;
			if (PS->bIsABot)
			{
				RankedMemberInfo.AccountId = PS->PlayerName;
			}
			RankedMemberInfo.Score = PS->Score;
			MatchResult.RedTeam.Members.Add(RankedMemberInfo);
			MatchResult.RedTeam.SocialPartySize = FMath::Max(MatchResult.RedTeam.SocialPartySize, PS->PartySize);
		}
	}
}

uint8 AUTDMGameMode::GetNumMatchesFor(AUTPlayerState* PS, bool InbRankedSession) const
{
	return PS ? PS->DMMatchesPlayed : 0;
}

int32 AUTDMGameMode::GetEloFor(AUTPlayerState* PS, bool InbRankedSession) const
{
	return PS ? PS->DMRank : Super::GetEloFor(PS, InbRankedSession);
}

void AUTDMGameMode::SetEloFor(AUTPlayerState* PS, bool InbRankedSession, int32 NewEloValue, bool bIncrementMatchCount)
{
	if (PS)
	{
		PS->DMRank = NewEloValue;
		if (bIncrementMatchCount && (PS->DMMatchesPlayed < 255))
		{
			PS->DMMatchesPlayed++;
		}
	}
}