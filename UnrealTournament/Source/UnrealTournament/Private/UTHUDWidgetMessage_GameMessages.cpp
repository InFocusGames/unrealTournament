// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealTournament.h"
#include "UTHUDWidgetMessage.h"
#include "UTHUDWidgetMessage_GameMessages.h"
#include "UTGameMessage.h"

UUTHUDWidgetMessage_GameMessages::UUTHUDWidgetMessage_GameMessages(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ManagedMessageArea = FName(TEXT("GameMessages"));
	Position = FVector2D(0.0f, 0.0f);			
	ScreenPosition = FVector2D(0.5f, 0.7f);
	Size = FVector2D(0.0f, 0.0f);			
	Origin = FVector2D(0.0f, 0.0f);				
	bShadowedText=true;
	ShadowDirection=FVector2D(0,1);
	FadeTime = 0.5f;
}

float UUTHUDWidgetMessage_GameMessages::GetTextScale(int32 QueueIndex)
{
	return 0.75;
}

