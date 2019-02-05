Set wshShell = CreateObject( "WScript.Shell" )
Strup = wshShell.ExpandEnvironmentStrings( "%USERPROFILE%" )
WScript.Echo Strup