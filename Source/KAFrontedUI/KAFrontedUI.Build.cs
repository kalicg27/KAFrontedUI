// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KAFrontedUI : ModuleRules
{
	public KAFrontedUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"GameplayTags",
			"UMG",
            "CommonInput",
            "PropertyPath"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	}
}
