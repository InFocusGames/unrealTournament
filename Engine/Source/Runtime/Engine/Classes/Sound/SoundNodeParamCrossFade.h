// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Sound/SoundNodeDistanceCrossFade.h"
#include "SoundNodeParamCrossFade.generated.h"

/** 
 * Crossfades between different sounds based on a parameter
 */
UCLASS(editinlinenew, MinimalAPI, meta=( DisplayName="Crossfade by Param" ))
class USoundNodeParamCrossFade : public USoundNodeDistanceCrossFade
{
	GENERATED_UCLASS_BODY()

public:

	/* Parameter controlling cross fades. */
	UPROPERTY(EditAnywhere, Category=CrossFade )
	FName ParamName;

	virtual float GetCurrentDistance(FAudioDevice* AudioDevice, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams) const override;
	virtual bool AllowCrossfading(FActiveSound& ActiveSound) const override;
	virtual float MaxAudibleDistance(float CurrentMaxDistance) override;

};
