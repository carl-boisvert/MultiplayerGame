// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiplayerLobby : ModuleRules
{
	public MultiplayerLobby(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay"
		, "OnlineSubsystem", "OnlineSubsystemNull"
		, "UMG"
		, "Http", "Json", "JsonUtilities"
		,"Slate", "SlateCore"
		,"GameLiftServerSDK"
		});
	}
}
