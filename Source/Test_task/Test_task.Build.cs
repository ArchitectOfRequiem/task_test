// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Test_task : ModuleRules
{
	public Test_task(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OnlineSubsystem", "Slate", "SlateCore"});

		PrivateDependencyModuleNames.AddRange(new string[] {"OnlineSubsystemUtils","OnlineSubsystemNull" });
	}
}
