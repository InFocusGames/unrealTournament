// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealTournament.h"
#include "UTHUDWidget_WeaponBar.h"
#include "UTWeapon.h"
#include "UTHUDWidgetMessage.h"

UUTHUDWidget_WeaponBar::UUTHUDWidget_WeaponBar(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Position=FVector2D(0.0f, -90.0f);
	Size=FVector2D(0,0);
	ScreenPosition=FVector2D(1.0f, 1.0f);
	Origin=FVector2D(1.0f,1.0f);

	SelectedCellScale=1.1;
	SelectedAnimRate=0.3;
	CellWidth = 90;
}

void UUTHUDWidget_WeaponBar::InitializeWidget(AUTHUD* Hud)
{

	LastGroup = -1;
	LastGroupSlot = -1.0;

	if (CellBackground.Num() < 2)
	{
		CellBackground.SetNumZeroed(2);
	}
	if (CellBorders.Num() < 2)
	{
		CellBorders.SetNumZeroed(2);
	}
	if (GroupHeaderCap.Num() < 2)
	{
		GroupHeaderCap.SetNumZeroed(2);
	}
	if (GroupSpacerBorder.Num() < 2)
	{
		GroupSpacerBorder.SetNumZeroed(2);
	}
	if (HeaderTab.Num() < 2)
	{
		HeaderTab.SetNumZeroed(2);
	}

	Super::InitializeWidget(Hud);
}

/**
 *	We aren't going tor use DrawAllRenderObjects.  Instead we are going to have a nice little custom bit of drawing based on what weapon gropup this 
 *  is.
 **/
void UUTHUDWidget_WeaponBar::Draw_Implementation(float DeltaTime)
{
	TArray<FWeaponGroup> WeaponGroups;

	if (UTCharacterOwner)
	{
		// Handle fading out.
		if (FadeTimer > 0.0f)
		{
			FadeTimer -= DeltaTime;
		}
		else if (Opacity != UTHUDOwner->HUDWidgetWeaponbarInactiveOpacity)
		{
			float Delta = (1.0 - UTHUDOwner->HUDWidgetWeaponbarInactiveOpacity) * DeltaTime;	// 1 second fade
			if (Opacity < UTHUDOwner->HUDWidgetWeaponbarInactiveOpacity) 
			{
				Opacity = FMath::Clamp<float>(Opacity + Delta, 0.0, UTHUDOwner->HUDWidgetWeaponbarInactiveOpacity);
			}
			else
			{
				Opacity = FMath::Clamp<float>(Opacity - Delta, UTHUDOwner->HUDWidgetWeaponbarInactiveOpacity, 1.0);
			}
		}

		AUTWeapon* Weap = UTCharacterOwner->GetWeapon();
		if (Weap)
		{
			if (Weap->Group != LastGroup || Weap->GroupSlot != LastGroupSlot)
			{
				// Weapon has changed.. set everything up.
				Opacity = 1.0;
				FadeTimer = 1.0;

				LastGroup = Weap->Group;
				LastGroupSlot = Weap->GroupSlot;
			}
		}
	}

	CollectWeaponData(WeaponGroups, DeltaTime);

	float DesiredOpacity = Opacity;

	if (WeaponGroups.Num() > 0)
	{
		// Draw the Weapon Groups

		float YPosition = 0.0;

		AUTWeapon* SelectedWeapon = UTCharacterOwner->GetWeapon();
		int32 SelectedGroup = SelectedWeapon ? SelectedWeapon->Group : -1;

		for (int32 GroupIdx = 0; GroupIdx < WeaponGroups.Num(); GroupIdx++)
		{
			// We have no allied all of the animation and we know the biggest anim scale, so we can figure out how wide this group should be.

			float Y2 = YPosition;
			float TextXPosition = 0;

			if (WeaponGroups[GroupIdx].WeaponsInGroup.Num() > 0)
			{
				// Draw the elements.
				for (int32 WeapIdx = 0; WeapIdx < WeaponGroups[GroupIdx].WeaponsInGroup.Num(); WeapIdx++)
				{
					AUTWeapon* CurrentWeapon = WeaponGroups[GroupIdx].WeaponsInGroup[WeapIdx];
					bool bSelected = CurrentWeapon == SelectedWeapon;

					Opacity = bSelected ? 1.0 : DesiredOpacity;

					// Draw the background and the background's border.

					int32 Idx = (WeapIdx == 0) ? 0 : 1;

					float FullIconCellWidth = (CurrentWeapon->Group == SelectedGroup) ? CellWidth * SelectedCellScale : CellWidth;
					float FullCellWidth = FullIconCellWidth + HeaderTab[Idx].GetWidth() + 3 + GroupHeaderCap[Idx].GetWidth();

					float CellScale = bSelected ? SelectedCellScale : 1.0;
					float CellHeight = CellBackground[Idx].GetHeight() * CellScale;

					float IconCellWidth = CellWidth * CellScale;

					float XPosition = (FullCellWidth * -1);
					YPosition -= HeaderTab[Idx].GetHeight() * CellScale;

					// Draw the Tab.
					RenderObj_TextureAt(HeaderTab[Idx], XPosition, YPosition, HeaderTab[Idx].GetWidth(), CellHeight);
					XPosition += HeaderTab[Idx].GetWidth();
					TextXPosition = XPosition;

					// Draw the Stretch bar

					// Calculate the size of the stretch bar.

					float StretchSize = FMath::Abs<float>(XPosition) -IconCellWidth - GroupHeaderCap[Idx].GetWidth();
					RenderObj_TextureAt(GroupSpacerBorder[Idx], XPosition, YPosition, StretchSize, CellHeight);
					XPosition += StretchSize;

					// Draw the cap

					RenderObj_TextureAt(GroupHeaderCap[Idx], XPosition, YPosition, GroupHeaderCap[Idx].GetWidth(), CellHeight);
					XPosition += GroupHeaderCap[Idx].GetWidth();


					// Draw the cell and the icon.

					RenderObj_TextureAt(CellBackground[Idx], XPosition, YPosition, IconCellWidth, CellHeight);
					RenderObj_TextureAt(CellBorders[Idx], XPosition, YPosition, IconCellWidth, CellHeight);

					// Draw the Weapon Icon

					if (CurrentWeapon)

					WeaponIcon.UVs = bSelected ? CurrentWeapon->WeaponBarSelectedUVs : CurrentWeapon->WeaponBarInactiveUVs;

					float WeaponY = (CellHeight * 0.5) - (WeaponIcon.UVs.VL * CellScale * 0.5);
					RenderObj_TextureAt(WeaponIcon, -10, YPosition + WeaponY, WeaponIcon.UVs.UL * CellScale, WeaponIcon.UVs.VL * CellScale);

					// Draw the ammo bars

					if (BarTexture)
					{
						float AmmoPerc = CurrentWeapon->MaxAmmo > 0 ? float(CurrentWeapon->Ammo) / float(CurrentWeapon->MaxAmmo) : 0.0;
						float BarHeight = CellHeight - 16;
						float Width = bSelected ? 4.0 : 2.0;
						float X = (Width * -1) - 2;
						float Y = YPosition + 8;
						DrawTexture(BarTexture, X, Y, Width, BarHeight, BarTextureUVs.U, BarTextureUVs.V, BarTextureUVs.UL, BarTextureUVs.VL, bSelected ? 1.0 : 0.5, FLinearColor::Black);

						Y = Y + BarHeight - (BarHeight * AmmoPerc);
						BarHeight *= AmmoPerc;

						DrawTexture(BarTexture, X, Y, Width, BarHeight, BarTextureUVs.U, BarTextureUVs.V, BarTextureUVs.UL, BarTextureUVs.VL, bSelected ? 1.0 : 0.5, FLinearColor::White);
					}
				}
			}
			else
			{
				Opacity = DesiredOpacity;

				// Draw the background and the background's border.

				float FullIconCellWidth = CellWidth;
				float FullCellWidth = FullIconCellWidth + HeaderTab[0].GetWidth() + 3 + GroupHeaderCap[0].GetWidth();

				float CellScale = 1.0;
				float CellHeight = CellBackground[0].GetHeight() * CellScale;

				float IconCellWidth = CellWidth * CellScale;

				float XPosition = (FullCellWidth * -1);
				YPosition -= HeaderTab[0].GetHeight() * CellScale;

				// Draw the Tab.
				RenderObj_TextureAt(HeaderTab[0], XPosition, YPosition, HeaderTab[0].GetWidth(), CellHeight);
				XPosition += HeaderTab[0].GetWidth();
				TextXPosition = XPosition;

				// Draw the Stretch bar

				// Calculate the size of the stretch bar.

				float StretchSize = FMath::Abs<float>(XPosition) -IconCellWidth - GroupHeaderCap[0].GetWidth();
				RenderObj_TextureAt(GroupSpacerBorder[0], XPosition, YPosition, StretchSize, CellHeight);
				XPosition += StretchSize;

				// Draw the cap

				RenderObj_TextureAt(GroupHeaderCap[0], XPosition, YPosition, GroupHeaderCap[0].GetWidth(), CellHeight);
				XPosition += GroupHeaderCap[0].GetWidth();

				// Draw the cell and the icon.

				RenderObj_TextureAt(CellBackground[0], XPosition, YPosition, IconCellWidth, CellHeight);
				RenderObj_TextureAt(CellBorders[0], XPosition, YPosition, IconCellWidth, CellHeight);
			}


			GroupText.Text = FText::AsNumber(WeaponGroups[GroupIdx].Group);
			RenderObj_TextAt(GroupText, TextXPosition + GroupText.Position.X, YPosition + ((Y2 - YPosition) * 0.5) + GroupText.Position.Y);

			YPosition -= 10;
		}

	}
}

void UUTHUDWidget_WeaponBar::CollectWeaponData(TArray<FWeaponGroup> &WeaponGroups, float DeltaTime)
{
	if (UTCharacterOwner)
	{
		// Parse over the character and see what weapons they have.

		if (RequiredGroups >= 0)
		{
			for (int i=RequiredGroups;i>=0;i--)
			{
				FWeaponGroup G = FWeaponGroup(i, NULL);
				WeaponGroups.Add(G);
			}
		}

		for (TInventoryIterator<AUTWeapon> It(UTCharacterOwner); It; ++It)
		{
			AUTWeapon* Weapon = *It;

			int32 GroupIndex = -1;
			for (int32 i=0;i<WeaponGroups.Num();i++)
			{
				if (WeaponGroups[i].Group == Weapon->Group)
				{
					GroupIndex = i;
					break;
				}
			}
	
			if (GroupIndex < 0)
			{
				FWeaponGroup G = FWeaponGroup(Weapon->Group, Weapon);

				int32 InsertPosition = -1;
				for (int32 i=0;i<WeaponGroups.Num();i++)
				{
					if ( WeaponGroups[i].Group < G.Group)
					{
						InsertPosition = i;
						break;
					}
				}

				if (InsertPosition <0)
				{
					WeaponGroups.Add(G);
				}
				else
				{
					WeaponGroups.Insert(G,InsertPosition);
				}

			}
			else
			{
				WeaponGroups[GroupIndex].WeaponsInGroup.Add(Weapon);
			}
		}
	}
}

float UUTHUDWidget_WeaponBar::GetDrawScaleOverride()
{
	return UTHUDOwner->HUDWidgetScaleOverride * UTHUDOwner->HUDWidgetWeaponBarScaleOverride;
}
