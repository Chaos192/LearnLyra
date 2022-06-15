// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LyraGame : ModuleRules
{
    public LyraGame(ReadOnlyTargetRules Target) : base(Target)
    {
        OptimizeCode = CodeOptimization.InShippingBuildsOnly;

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[]
        {
            "LyraGame"
        });

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "GameplayTags",
            "GameplayTasks",
            "GameplayAbilities",
            "GameFeatures"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "EnhancedInput",
            "CommonUI",
            "CommonInput"
        });
    }
}
