// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.


#pragma once
#include "Audio.h"
#include "Sound/SoundAttenuation.h"

#include "AudioComponent.generated.h"

/** called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early */
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAudioFinished );
/** shadow delegate declaration for above */
DECLARE_MULTICAST_DELEGATE_OneParam( FOnAudioFinishedNative, class UAudioComponent* );
/** Called when subtitles are sent to the SubtitleManager.  Set this delegate if you want to hijack the subtitles for other purposes */
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnQueueSubtitles, const TArray<struct FSubtitleCue>&, Subtitles, float, CueDuration );

/**
 *	Struct used for storing one per-instance named parameter for this AudioComponent.
 *	Certain nodes in the SoundCue may reference parameters by name so they can be adjusted per-instance.
 */
USTRUCT()
struct FAudioComponentParam
{
	GENERATED_USTRUCT_BODY()

	// Name of the parameter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AudioComponentParam)
	FName ParamName;

	// Value of the parameter when used as a float
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AudioComponentParam)
	float FloatParam;

	// Value of the parameter when used as a boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AudioComponentParam)
	bool BoolParam;
	
	// Value of the parameter when used as an integer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AudioComponentParam)
	int32 IntParam;

	// Value of the parameter when used as a sound wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AudioComponentParam)
	class USoundWave* SoundWaveParam;


	FAudioComponentParam()
		: FloatParam(0)
		, BoolParam(false)
		, IntParam(0)
		, SoundWaveParam(NULL)
	{
	}

};

/**
 * AudioComponent is used to play a Sound
 *
 * @see https://docs.unrealengine.com/latest/INT/Audio/Overview/index.html
 * @see USoundBase
 */
UCLASS(ClassGroup=(Audio, Common), hidecategories=(Object, ActorComponent, Physics, Rendering, Mobility, LOD), ShowCategories=Trigger, meta=(BlueprintSpawnableComponent))
class ENGINE_API UAudioComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()

	/** The sound to be played */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	class USoundBase* Sound;

	/** Array of per-instance parameters for this AudioComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound, AdvancedDisplay)
	TArray<struct FAudioComponentParam> InstanceParameters;

	/** Optional sound group this AudioComponent belongs to */
	UPROPERTY(EditAnywhere, Category=Sound, AdvancedDisplay)
	USoundClass* SoundClassOverride;

	/** Auto destroy this component on completion */
	UPROPERTY()
	uint32 bAutoDestroy:1;

	/** Stop sound when owner is destroyed */
	UPROPERTY()
	uint32 bStopWhenOwnerDestroyed:1;

	/** Whether the wave instances should remain active if they're dropped by the prioritization code. Useful for e.g. vehicle sounds that shouldn't cut out. */
	UPROPERTY()
	uint32 bShouldRemainActiveIfDropped:1;

	/** Is this audio component allowed to be spatialized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation)
	uint32 bAllowSpatialization:1;

	/** Should the Attenuation Settings asset be used (false) or should the properties set directly on the component be used for attenuation properties */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation)
	uint32 bOverrideAttenuation:1;

	/** Whether or not this sound plays when the game is paused in the UI */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	uint32 bIsUISound : 1;

	/** The lower bound to use when randomly determining a pitch multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Modulation)
	float PitchModulationMin;

	/** The upper bound to use when randomly determining a pitch multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Modulation)
	float PitchModulationMax;

	/** The lower bound to use when randomly determining a volume multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Modulation)
	float VolumeModulationMin;

	/** The upper bound to use when randomly determining a volume multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Modulation)
	float VolumeModulationMax;

	/** A volume multiplier to apply to sounds generated by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	float VolumeMultiplier;

	/** A priority value that scales against final ouput volume and is used to determine a sound's play priority. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	float VolumeWeightedPriorityScale;

	/** A pitch multiplier to apply to sounds generated by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Sound)
	float PitchMultiplier;

	/** A multiplier to apply to the high frequency gain for sounds generated by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Modulation)
	float HighFrequencyGainMultiplier;

	/** If bOverrideSettings is false, the asset to use to determine attenuation properties for sounds generated by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation, meta=(EditCondition="!bOverrideAttenuation"))
	class USoundAttenuation* AttenuationSettings;

	/** If bOverrideSettings is true, the attenuation properties to use for sounds generated by this component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation, meta=(EditCondition="bOverrideAttenuation"))
	struct FAttenuationSettings AttenuationOverrides;

	/** while playing, this component will check for occlusion from its closest listener every this many seconds */
	float OcclusionCheckInterval;

	/** called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early */
	UPROPERTY(BlueprintAssignable)
	FOnAudioFinished OnAudioFinished;

	/** shadow delegate for non UObject subscribers */
	FOnAudioFinishedNative OnAudioFinishedNative;

	/** Called when subtitles are sent to the SubtitleManager.  Set this delegate if you want to hijack the subtitles for other purposes */
	UPROPERTY()
	FOnQueueSubtitles OnQueueSubtitles;

	// Set what sound is played by this component
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetSound( USoundBase* NewSound );

	/**
	 * This can be used in place of "play" when it is desired to fade in the sound over time.
	 *
	 * If FadeTime is 0.0, the change in volume is instant.
	 * If FadeTime is > 0.0, the multiplier will be increased from 0 to FadeVolumeLevel over FadeIn seconds.
	 *
	 * @param FadeInDuration how long it should take to reach the FadeVolumeLevel
	 * @param FadeVolumeLevel the percentage of the AudioComponents's calculated volume to fade to
	 */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void FadeIn(float FadeInDuration, float FadeVolumeLevel = 1.f, float StartTime = 0.f);

	/**
	 * This is used in place of "stop" when it is desired to fade the volume of the sound before stopping.
	 *
	 * If FadeTime is 0.0, this is the same as calling Stop().
	 * If FadeTime is > 0.0, this will adjust the volume multiplier to FadeVolumeLevel over FadeInTime seconds
	 * and then stop the sound.
	 *
	 * @param FadeOutDuration how long it should take to reach the FadeVolumeLevel
	 * @param FadeVolumeLevel the percentage of the AudioComponents's calculated volume in which to fade to
	 */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void FadeOut(float FadeOutDuration, float FadeVolumeLevel);

	/** Start a sound playing on an audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void Play(float StartTime = 0.f);

	/** Stop an audio component playing its sound cue, issue any delegates if needed */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void Stop();

	/** @return true if this component is currently playing a SoundCue. */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	bool IsPlaying() const;

	/** This will allow one to adjust the volume of an AudioComponent on the fly */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void AdjustVolume(float AdjustVolumeDuration, float AdjustVolumeLevel);

	/**  Set a float instance parameter for use in sound cues played by this audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetFloatParameter(FName InName, float InFloat);

	/**  Set a sound wave instance parameter for use in sound cues played by this audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetWaveParameter(FName InName, class USoundWave* InWave);

	/** Set a boolean instance parameter for use in sound cues played by this audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio", meta=(DisplayName="Set Boolean Parameter"))
	void SetBoolParameter(FName InName, bool InBool);
	
	/** Set an integer instance parameter for use in sound cues played by this audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio", meta=(DisplayName="Set Integer Parameter"))
	void SetIntParameter(FName InName, int32 InInt);

	/** Set a new volume multiplier */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetVolumeMultiplier(float NewVolumeMultiplier);

	/** Set a new pitch multiplier */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetPitchMultiplier(float NewPitchMultiplier);

	/** Set whether sounds generated by this audio component should be considered UI sounds */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void SetUISound(bool bInUISound);

	/** Modify the attenuation settings of the audio component */
	UFUNCTION(BlueprintCallable, Category="Audio|Components|Audio")
	void AdjustAttenuation(const FAttenuationSettings& InAttenuationSettings);

	/** Called by the ActiveSound to inform the component that playback is finished */
	void PlaybackCompleted(bool bFailedToStart);

public:

	/** If true, subtitles in the sound data will be ignored. */
	uint32 bSuppressSubtitles:1;

	/** Whether this audio component is previewing a sound */
	uint32 bPreviewComponent:1;

	/** If true, this sound will not be stopped when flushing the audio device. */
	uint32 bIgnoreForFlushing:1;

	/** Whether audio effects are applied */
	uint32 bEQFilterApplied:1;

	/** Whether to artificially prioritize the component to play */
	uint32 bAlwaysPlay:1;

	/** Whether or not this audio component is a music clip */
	uint32 bIsMusic:1;

	/** Whether or not the audio component should be excluded from reverb EQ processing */
	uint32 bReverb:1;

	/** Whether or not this sound class forces sounds to the center channel */
	uint32 bCenterChannelOnly:1;

	/** Used by the subtitle manager to prioritize subtitles wave instances spawned by this component. */
	float SubtitlePriority;

	// Begin UObject interface.
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR
	virtual FString GetDetailedInfoInternal() const override;
	// End UObject interface.

	// Begin USceneComponent Interface
	virtual void Activate(bool bReset=false) override;
	virtual void Deactivate() override;
	virtual void OnUpdateTransform(bool bSkipPhysicsMove) override;
	// do nothing! on purpose
	virtual void UpdateNavigationData() override {}
	// End USceneComponent Interface

	// Begin ActorComponent interface.
#if WITH_EDITORONLY_DATA
	virtual void OnRegister() override;
#endif
	virtual void OnUnregister() override;
	virtual const UObject* AdditionalStatObject() const override;
	// End ActorComponent interface.

	/** Returns a pointer to the attenuation settings to be used (if any) for this audio component dependent on the SoundAttenuation asset or overrides set. */
	const FAttenuationSettings* GetAttenuationSettingsToApply() const;

	/** Collects the various attenuation shapes that may be applied to the sound played by the audio component for visualization in the editor or via the in game debug visualization. */
	void CollectAttenuationShapesForVisualization(TMultiMap<EAttenuationShape::Type, FAttenuationSettings::AttenuationShapeDetails>& ShapeDetailsMap) const;

	/** Returns the active audio device to use for this component based on whether or not the component is playing in a world. */
	FAudioDevice* GetAudioDevice() const;

private:
	
#if WITH_EDITORONLY_DATA
	/** Utility function that updates which texture is displayed on the sprite dependent on the properties of the Audio Component. */
	void UpdateSpriteTexture();
#endif

	/** Utility function called by Play and FadeIn to start a sound playing. */
	void PlayInternal(const float StartTime = 0.f, const float FadeInDuration = 0.f, const float FadeVolumeLevel = 1.f);
};



