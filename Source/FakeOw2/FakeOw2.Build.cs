// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FakeOw2 : ModuleRules
{
	public FakeOw2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
