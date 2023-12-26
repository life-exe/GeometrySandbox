// Geometry Sandbox, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GeometrySandboxTarget : TargetRules
{
    public GeometrySandboxTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        DefaultBuildSettings = BuildSettingsVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "GeometrySandbox" });
    }
}
