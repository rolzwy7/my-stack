Set wshShell = CreateObject( "WScript.Shell" )
wshShell.RegWrite "HKCU\Software\Microsoft\Windows\CurrentVersion\Run\OnStartTasks", "<filepath>", "REG_SZ"
Set wshShell = Nothing