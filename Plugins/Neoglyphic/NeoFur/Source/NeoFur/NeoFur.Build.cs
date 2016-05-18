// Some copyright should be here...

using UnrealBuildTool;
using System;
using System.IO;

public class NeoFur : ModuleRules
{
	public NeoFur(TargetInfo Target)
	{

		PublicIncludePaths.AddRange(
			new string[] {
				"NeoFur/Public"

				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				"NeoFur/Private",

				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore", "RHI", "Renderer", "RenderCore", "ShaderCore"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject", "Engine", "Slate", "SlateCore"
				// ... add private dependencies that you statically link with here ...
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{

				// ... add any modules that your module loads dynamically here ...
			}
			);

	}
}
