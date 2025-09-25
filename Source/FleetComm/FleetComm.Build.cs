// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FleetComm : ModuleRules
{
	public FleetComm(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore", "GameplayTags", "UMG", "CommonUI" });
	}
}
