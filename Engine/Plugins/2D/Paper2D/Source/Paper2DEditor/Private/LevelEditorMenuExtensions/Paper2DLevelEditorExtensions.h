// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// Integrate Paper2D actions into the level editor context menu
class FPaperLevelEditorMenuExtensions
{
public:
	static void InstallHooks();
	static void RemoveHooks();
};
