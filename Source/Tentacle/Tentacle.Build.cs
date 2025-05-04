// © 2024 Backside4Charter & Deadsun. All rights reserved.

using UnrealBuildTool;

public class Tentacle : ModuleRules
{
	public Tentacle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PrecompileForTargets = PrecompileTargetsType.Any;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		PublicIncludePaths.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new string[] { });

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"GameplayAbilities",
			"HTTP",
			"TentacleWebSocket"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"AIModule",
			"CoreUObject",
			"Engine",
			"FunctionalTesting",
			"Json",
			"JsonUtilities",
			"MassEntity"
		});
		
		if (Target.bBuildEditor == true)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"UnrealEd"
			});
		}

		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
