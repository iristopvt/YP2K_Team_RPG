// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Prototype : ModuleRules
{
	public Prototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] { "Prototype" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Paper2D", "NavigationSystem", "UMG", "AIModule", "Niagara" ,"NiagaraCore", "NiagaraShader", "SlateCore", "MovieScene", "LevelSequence", "AnimGraphRuntime" });
    }
}
