// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GEP_Coursework_Sem2EditorTarget : TargetRules
{
	public GEP_Coursework_Sem2EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("GEP_Coursework_Sem2");
	}
}
