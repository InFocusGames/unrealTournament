// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#include "UnrealTournament.h"
#include "UTFlagRunScoreboard.h"
#include "UTCTFRoundGameState.h"

#include "StatNames.h"

UUTFlagRunScoreboard::UUTFlagRunScoreboard(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CH_Powerup = NSLOCTEXT("UTFlagRunScoreboard", "ColumnHeader_Powerups", "PU");

	ColumnHeaderPowerupX = 0.715f;
	ColumnHeaderPowerupEndX = ColumnHeaderPowerupX + 0.0575f;
}

void UUTFlagRunScoreboard::DrawScoreHeaders(float RenderDelta, float& YOffset)
{
	float XOffset = ScaledEdgeSize;
	float Height = 23.f*RenderScale;

	for (int32 i = 0; i < 2; i++)
	{
		// Draw the background Border
		DrawTexture(UTHUDOwner->ScoreboardAtlas, XOffset, YOffset, ScaledCellWidth, Height, 149, 138, 32, 32, 1.0, FLinearColor(0.72f, 0.72f, 0.72f, 0.85f));
		DrawText(CH_PlayerName, XOffset + (ScaledCellWidth * ColumnHeaderPlayerX), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Left, ETextVertPos::Center);
		if (UTGameState && UTGameState->HasMatchStarted())
		{
			DrawText(CH_Score, XOffset + (ScaledCellWidth * ColumnHeaderScoreX), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Center, ETextVertPos::Center);
			AUTCTFGameState* CTFState = Cast<AUTCTFGameState>(UTGameState);
			if (CTFState && (CTFState->bAttackerLivesLimited || CTFState->bDefenderLivesLimited))
			{
				DrawText(CH_Powerup, XOffset + (.5f * ScaledCellWidth * (ColumnHeaderPowerupX + ColumnHeaderPowerupEndX)), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Center, ETextVertPos::Center);
				DrawText(NSLOCTEXT("UTScoreboard", "LivesRemaining", "Lives"), XOffset + (ScaledCellWidth * 0.5f*(ColumnHeaderPowerupX + ColumnHeaderPingX)), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Center, ETextVertPos::Center);
			}
			else
			{
				DrawText(CH_Powerup, XOffset + (ScaledCellWidth * 0.5f * (ColumnHeaderPowerupX + ColumnHeaderPowerupEndX)), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Center, ETextVertPos::Center);
			}
		}
		DrawText((GetWorld()->GetNetMode() == NM_Standalone) ?  CH_Skill : CH_Ping, XOffset + (ScaledCellWidth * ColumnHeaderPingX), YOffset + ColumnHeaderY, UTHUDOwner->TinyFont, RenderScale, 1.0f, FLinearColor::Black, ETextHorzPos::Center, ETextVertPos::Center);
		XOffset = Canvas->ClipX - ScaledCellWidth - ScaledEdgeSize;
	}

	YOffset += Height + 4;
}

void UUTFlagRunScoreboard::DrawPlayerScore(AUTPlayerState* PlayerState, float XOffset, float YOffset, float Width, FLinearColor DrawColor)
{
	DrawText(FText::AsNumber(int32(PlayerState->Score)), XOffset + (Width * ColumnHeaderScoreX), YOffset + ColumnY, UTHUDOwner->SmallFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
	AUTCTFGameState* CTFState = Cast<AUTCTFGameState>(UTGameState);
	if (CTFState && (CTFState->bAttackerLivesLimited || CTFState->bDefenderLivesLimited))
	{
		AUTInventory* SelectedPowerup = PlayerState && PlayerState->BoostClass ? PlayerState->BoostClass->GetDefaultObject<AUTInventory>() : nullptr;
		const float LivesXOffset = (Width * 0.5f*(ColumnHeaderPowerupX + ColumnHeaderPingX));

		if (SelectedPowerup)
		{
			const float U = SelectedPowerup->HUDIcon.U;
			const float V = SelectedPowerup->HUDIcon.V;
			const float UL = SelectedPowerup->HUDIcon.UL;
			const float VL = SelectedPowerup->HUDIcon.VL;
				
			const float AspectRatio = UL / VL;
			UTexture* PowerupTexture = SelectedPowerup->HUDIcon.Texture;
			if (PowerupTexture)
			{
				const float TextureSize = (Width * (ColumnHeaderPowerupEndX - ColumnHeaderPowerupX));
				DrawTexture(PowerupTexture, XOffset + (Width * ColumnHeaderPowerupX), YOffset, TextureSize, TextureSize * AspectRatio, U, V, UL, VL);
			}
		}
		else
		{
			DrawText(NSLOCTEXT("UTScoreboard", "Dash", "-"), XOffset + (Width * ColumnHeaderPowerupX), YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
		}

		if (PlayerState->bHasLifeLimit && (PlayerState->RemainingLives >= 0))
		{
			DrawText(FText::AsNumber(PlayerState->RemainingLives), XOffset + LivesXOffset, YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
		}
		else
		{
			DrawText(NSLOCTEXT("UTScoreboard", "Dash", "-"), XOffset + LivesXOffset, YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
		}
	}
	else
	{
		DrawText(FText::AsNumber(PlayerState->FlagCaptures), XOffset + (Width * ColumnHeaderCapsX), YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
		DrawText(FText::AsNumber(PlayerState->Assists), XOffset + (Width * ColumnHeaderAssistsX), YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
		DrawText(FText::AsNumber(PlayerState->FlagReturns), XOffset + (Width * ColumnHeaderReturnsX), YOffset + ColumnY, UTHUDOwner->TinyFont, RenderScale, 1.0f, DrawColor, ETextHorzPos::Center, ETextVertPos::Center);
	}
}



