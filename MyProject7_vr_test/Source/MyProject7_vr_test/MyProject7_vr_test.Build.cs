// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject7_vr_test : ModuleRules
{
	public MyProject7_vr_test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "WebSockets", "ImageWrapper" });
	}
}
