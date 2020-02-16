// Geometry Sandbox, All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GeometrySandboxEditorTarget : TargetRules
{
    public GeometrySandboxEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange(new string[] { "GeometrySandbox" });
    }
}
