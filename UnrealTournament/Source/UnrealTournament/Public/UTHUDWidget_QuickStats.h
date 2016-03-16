// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UTHUDWidget_QuickStats.generated.h"

class AUTWeapon;

USTRUCT()
struct FQStatLayoutInfo
{
	GENERATED_USTRUCT_BODY()

	// The tag for this layout.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	FName Tag;

	// Where should the health widget go.  In Pixels based on 1080p
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	bool bHorizontalBorder;

	// Where should the health widget go.  In Pixels based on 1080p
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	FVector2D HealthOffset;

	// Where should the armor widget go.  In Pixels based on 1080p
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	FVector2D ArmorOffset;

	// Where should the Ammo widget go.  In Pixels based on 1080p
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout")
	FVector2D AmmoOffset;

	//TODO: Add powerups and flag
};

struct FStatInfo
{
	int32 Value;
	int32 LastValue;
	FLinearColor BackgroundColor;
	float Scale;
	bool bInfinite;
	bool bAltIcon;
};

UCLASS()
class UNREALTOURNAMENT_API UUTHUDWidget_QuickStats : public UUTHUDWidget
{
	GENERATED_UCLASS_BODY()

	virtual void InitializeWidget(AUTHUD* Hud);
	virtual void Draw_Implementation(float DeltaTime) override;
	virtual void PreDraw(float DeltaTime, AUTHUD* InUTHUDOwner, UCanvas* InCanvas, FVector2D InCanvasCenter);
	virtual bool ShouldDraw_Implementation(bool bShowScores);



protected:

	// the image to use for the background when the widget is in the horizontal layout mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	TArray<FQStatLayoutInfo> Layouts;

	// the image to use for the background when the widget is in the horizontal layout mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FHUDRenderObject_Texture HorizontalBackground;

	// the image to use for the background when the widget is in the vertical layout mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Background")
	FHUDRenderObject_Texture VerticalBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Texture HealthIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Texture ArmorIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Texture ArmorIconWithShieldBelt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Texture AmmoIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Texture InfiniteIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Icons")
	FHUDRenderObject_Text TextTemplate;

private:
	FName CurrentLayoutTag;
	int32 CurrentLayoutIndex;
	bool bHorizBorders;

	FStatInfo HealthInfo;
	FStatInfo ArmorInfo;
	FStatInfo AmmoInfo;

	AUTWeapon* LastWeapon;

	FLinearColor GetStatColor(float Perc, float WarnPerc, float DangerPerc);
	FLinearColor InterpColor(FLinearColor DestinationColor, float Delta);
	FVector2D CalcDrawLocation(float DistanceInPixels, float Angle);
	float DrawAngle;

	void DrawStat(FVector2D StatOffset, FStatInfo& StatInfo, FLinearColor TextColor, FHUDRenderObject_Texture Icon);

};