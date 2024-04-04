// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectTop : ModuleRules
{
	public ProjectTop(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "LevelSequence", "MovieScene", "UMG", "InventoryCppStudy"});
        PrivateDependencyModuleNames.AddRange(new string[] { "InventoryCppStudy" });
    }
}
