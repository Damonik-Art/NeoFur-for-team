// Some copyright should be here...

using UnrealBuildTool;

public class NeoFurEditor : ModuleRules
{
	public NeoFurEditor(TargetInfo Target)
	{

		PublicIncludePaths.AddRange(
			new string[] {
				"NeoFurEditor/Public"

				// ... add public include paths required here ...
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				"NeoFurEditor/Private"

				// ... add other private include paths required here ...
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore", "RHI", "Renderer", "RenderCore", "NeoFur"
			}
			);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject", "Engine", "Slate", "SlateCore",
                "UnrealEd", "NeoFur"
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
