// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class PackageContent : ModuleRules
	{
        public PackageContent(TargetInfo Target)
		{
            PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
				    "BlueprintGraph",
					"CoreUObject",
					"Engine",
                    "InputCore",
					"ImageWrapper",
					"DesktopPlatform",
					"LevelEditor",
					"Slate",
                    "EditorStyle",
				    "AssetTools",
                    "UnrealTournament",
				}
			);	// @todo Mac: for some reason CoreUObject and Engine are needed to link in debug on Mac

            PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"OnlineSubSystem",
					"SlateCore",
					"UnrealEd",
				}
			);

			PrivateIncludePathModuleNames.AddRange(
				new string[]
				{
					"MainFrame",
				}
			);

            DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
					"ImageWrapper",
					"LevelEditor",
					"MainFrame"
				}
			);
		}
	}
}