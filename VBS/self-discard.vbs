Function discardScript()
        Set objFSO = CreateObject("Scripting.FileSystemObject")
        strScript = Wscript.ScriptFullName
        objFSO.DeleteFile(strScript)
    End Function

discardScript()