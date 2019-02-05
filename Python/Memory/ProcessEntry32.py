# from ctypes import POINTER ,WINFUNCTYPE, c_size_t, c_int, windll
# from wintypes import HANDLE, LPCVOID, LPVOID, DWORD

from ctypes import *
from ctypes.wintypes import *
import os

_TH32CS_SNAPPROCESS = 0x00000002
_TH32CS_SNAPMODULE = 0x00000008

class MODULEENTRY32(Structure):
    _fields_ = [
        ('dwSize', DWORD),
        ('th32ModuleID', DWORD),
        ('th32ProcessID', DWORD),
        ('GlblcntUsage', DWORD),
        ('ProccntUsage', DWORD),
        ('modBaseAddr', POINTER(BYTE)),
        ('modBaseSize', DWORD),
        ('hModule', HMODULE),
        ('szModule' , c_char * 260 ),
        ('szExePath' , c_char * 260 ),
        ('dwFlags', DWORD)
    ]
class PROCESSENTRY32(Structure):
    _fields_ = [ ( 'dwSize' , DWORD ) ,
                 ( 'cntUsage' , DWORD) ,
                 ( 'th32ProcessID' , DWORD) ,
                 ( 'th32DefaultHeapID' , POINTER(ULONG)) ,
                 ( 'th32ModuleID' , DWORD) ,
                 ( 'cntThreads' , DWORD) ,
                 ( 'th32ParentProcessID' , DWORD) ,
                 ( 'pcPriClassBase' , LONG) ,
                 ( 'dwFlags' , DWORD) ,
                 ( 'szExeFile' , c_char * 260 ) ]

def getProcessBaseAddress(pid):
    kernel32                 = windll.kernel32
    CreateToolhelp32Snapshot = kernel32.CreateToolhelp32Snapshot
    CloseHandle              = kernel32.CloseHandle
    Module32First            = kernel32.Module32First

    me32 = MODULEENTRY32()
    me32.dwSize = sizeof(MODULEENTRY32)
    hProcessSnap = CreateToolhelp32Snapshot(_TH32CS_SNAPMODULE, pid)

    ret = None
    if Module32First(hProcessSnap, byref(me32)):
        ret = ctypes.addressof(me32.modBaseAddr.contents)
    CloseHandle(hProcessSnap)
    return ret

def getProcessList():
    kernel32                 = windll.kernel32
    CreateToolhelp32Snapshot = kernel32.CreateToolhelp32Snapshot
    Process32First           = kernel32.Process32First
    Process32Next            = kernel32.Process32Next
    CloseHandle              = kernel32.CloseHandle

    hProcessSnap = CreateToolhelp32Snapshot(_TH32CS_SNAPPROCESS, 0)
    pe32 = PROCESSENTRY32()
    pe32.dwSize = sizeof(PROCESSENTRY32)

    if not Process32First(hProcessSnap, byref(pe32)):
        return []

    ret = []
    while Process32Next(hProcessSnap, byref(pe32)):
        ret.append( (pe32.th32ProcessID, pe32.szExeFile) )

    CloseHandle(hProcessSnap)
    return ret

def getPidByName(process_name):
    process_list = getProcessList()
    for process in process_list:
        if process[1].lower() == process_name.lower():
            return process[0]

def getNameByPid(process_pid):
    process_list = getProcessList()
    for process in process_list:
        if process[0] == process_pid:
            return process[1]
