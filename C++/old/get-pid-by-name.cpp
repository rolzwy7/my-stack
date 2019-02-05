#include <windows.h>
#include <tlhelp32.h>

DWORD getPIDByProcessName(CHAR* Name) {
    PROCESSENTRY32 pe;
	HANDLE Snapshot;
	DWORD ret = 0;
    Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
    if (Snapshot != INVALID_HANDLE_VALUE){
        if (Process32First(Snapshot, &pe)){

            do{
                if (!lstrcmpi(Name, pe.szExeFile)){
                    ret = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(Snapshot, &pe));
        }
        CloseHandle(Snapshot);
    }
    return ret;
}