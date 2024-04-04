// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InventoryCppStudy : ModuleRules
{
	public InventoryCppStudy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "LevelSequence", "MovieScene", "UMG", "ProjectTop" });
        PrivateDependencyModuleNames.AddRange(new string[] { "ProjectTop" });
    }
}
