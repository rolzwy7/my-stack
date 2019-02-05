#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <tlhelp32.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

using namespace std;

volatile sig_atomic_t show_status_stop;

void inthand(int signum) {
    show_status_stop = 1;
}

DWORD PIDByName(LPCSTR Name){
    PROCESSENTRY32 pe;
	HANDLE Snapshot;
	DWORD ret = 0;
    Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
    if (Snapshot != INVALID_HANDLE_VALUE){
        if (Process32First(Snapshot, &pe)){
            do{
                if (!lstrcmpi(Name, pe.szExeFile)){
                    ret = pe.th32ProcessID;break;
                }
            } while (Process32Next(Snapshot, &pe));
        }
    CloseHandle(Snapshot);
    }
    return ret;
}

DWORD GetProcessBaseAddress(int pid) {
    MODULEENTRY32 me32  = { sizeof( MODULEENTRY32 ) };
    HANDLE hSnapshot    = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pid );

    if (hSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    if (Module32First( hSnapshot, &me32 ))
    {
        CloseHandle( hSnapshot );
        return (DWORD)me32.modBaseAddr;
    }

    CloseHandle( hSnapshot );
    return 0;
}

int read_mem(LPCVOID address,HANDLE hProcess){
    int buffer;
    ReadProcessMemory(hProcess,(LPVOID)address, &buffer, sizeof(buffer), NULL);
    return buffer;
}

int write_mem(LPCVOID address,HANDLE hProcess,int value){ // Do poprawy
    LPVOID lpFunction = (LPVOID)address;
    DWORD memloc = (DWORD)lpFunction;
    DWORD datasize = sizeof(value);
    if(WriteProcessMemory(hProcess, (LPVOID)address, &value, datasize, NULL)){
        printf("\r[+] 0x%.8X -> %d    ",address,value);
        Sleep(500);
    } else {
        return -1;
    }
    return 0;
}

class Isaac {

public:
    string proc_name;
    DWORD ProcessId;
    HANDLE hProcess;
    LPCVOID BaseAddress;
    LPCVOID BaseAddress_StaticEntry;

    LPCVOID coins_address;
    unsigned short coins;

    LPCVOID bombs_address ;
    unsigned short bombs;

    LPCVOID keys_address;
    unsigned short keys;

    LPCVOID red_hearts_fill_address;
    unsigned short red_hearts_fill;

    LPCVOID red_hearts_cont_address;
    unsigned short red_hearts_cont;

    LPCVOID blue_hearts_fill_address;
    unsigned short blue_hearts_fill;

public:
    Isaac();

    void max_out_pick_ups() {
        write_mem(coins_address,hProcess,99);
        write_mem(bombs_address,hProcess,99);
        write_mem(keys_address,hProcess,99);
    }

    void full_red_hearts() {
        write_mem(blue_hearts_fill_address,hProcess,2);
        write_mem(red_hearts_cont_address,hProcess,24);
        write_mem(red_hearts_fill_address,hProcess,24);
        write_mem(blue_hearts_fill_address,hProcess,0);
    }

    void full_blue_hearts() {
        write_mem(blue_hearts_fill_address,hProcess,2);
        write_mem(red_hearts_cont_address,hProcess,0);
        write_mem(red_hearts_fill_address,hProcess,0);
        write_mem(blue_hearts_fill_address,hProcess,24);
    }

    void super_regeneration(int interval) {
        full_red_hearts();
        write_mem(red_hearts_fill_address,hProcess,2);
        system("cls");
        signal(SIGINT, inthand);
        int current_filled_hearts;
        while(!show_status_stop){
            Sleep(interval);
            printf("\r[ :^) ] Interval: %dms | [ Ctrl + C to stop super regeneration ]",interval);
            gather_stats();
            if(red_hearts_fill<red_hearts_cont){
                red_hearts_fill++;
                write_mem(red_hearts_fill_address,hProcess,red_hearts_fill);
            }
        }
    }


    void show_addresses() {
        printf("\nBaseAddress              : 0x%.8X\n",this->BaseAddress);
        printf("BaseAddress_StaticEntry  : 0x%.8X\n",this->BaseAddress_StaticEntry);
        printf("coins_address            : 0x%.8X\n",this->coins_address);
        printf("bombs_address            : 0x%.8X\n",this->bombs_address);
        printf("keys_address             : 0x%.8X\n",this->keys_address);
        printf("red_hearts_fill_address  : 0x%.8X\n",this->red_hearts_fill_address);
        printf("red_hearts_cont_address  : 0x%.8X\n",this->red_hearts_cont_address);
        printf("blue_hearts_fill_address : 0x%.8X\n\n",this->blue_hearts_fill_address);
    }

    void gather_stats(){
        LPCVOID static_hook = (LPCVOID)BaseAddress_StaticEntry; // Static hook

        // Calculate coin,key,bomb address and assign to class fields
        int coins_pointers[] = {0xB7D8,0x0,0x1B58};
        LPCVOID coins_address_buff = (LPCVOID)static_hook;
        for( int i=0;i<3;i++ ){ coins_address_buff = read_mem((LPCVOID)coins_address_buff,hProcess)+(LPCVOID)coins_pointers[i]; }

        this->coins_address = (LPCVOID)coins_address_buff;
        this->bombs_address = (LPCVOID)(coins_address - 0x4);
        this->keys_address = (LPCVOID)(bombs_address - 0x8);

        this->coins = read_mem(coins_address,hProcess);
        this->bombs = read_mem(bombs_address,hProcess);
        this->keys = read_mem(keys_address,hProcess);

        // Calculate red hearts fill address and assign to class fields
        int red_hearts_fill_pointers[] = {0xB7D8,0x0,0x1B34};
        LPCVOID red_hearts_fill_buff = (LPCVOID)static_hook;
        for( int i=0;i<3;i++ ){ red_hearts_fill_buff = read_mem((LPCVOID)red_hearts_fill_buff,hProcess)+(LPCVOID)red_hearts_fill_pointers[i]; }

        this->red_hearts_fill_address = red_hearts_fill_buff;
        this->red_hearts_fill = read_mem(red_hearts_fill_address,hProcess);

        this->red_hearts_cont_address = (LPCVOID)(red_hearts_fill_address - 0x4);
        this->red_hearts_cont = read_mem(red_hearts_cont_address,hProcess);

        this->blue_hearts_fill_address = (LPCVOID)(red_hearts_fill_address + 0x8);
        this->blue_hearts_fill = read_mem(blue_hearts_fill_address,hProcess);
    }

    int update_isaac(){
        this->ProcessId = PIDByName(proc_name.c_str());
        this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, this->ProcessId);
        this->BaseAddress = (LPCVOID)GetProcessBaseAddress(ProcessId);
        this->BaseAddress_StaticEntry = this->BaseAddress+0x2EC554;

        printf("[*] Isaac process : %s (pid=%d)\n",proc_name.c_str(),ProcessId);
        printf("[+] Process Base Address : 0x%.8X\n",this->BaseAddress);
        printf("[+] Static Entry : 0x%.8X + 0x2EC554 = 0x%.8X\n",this->BaseAddress,this->BaseAddress_StaticEntry);

        return this->ProcessId;
    }

    int keep_alive(){
        this->ProcessId = PIDByName(proc_name.c_str());
        return this->ProcessId;
    }

    int show_stats(){
        signal(SIGINT, inthand);
        while(!show_status_stop){
        printf(" [ Ctrl+C to quit ]\n\n");
        if(!keep_alive()){
                system("cls");
                printf("\r[-] Isaac process has been aborted.\n\n");
                return -1;
        }

        //turn_on_cheats();

        gather_stats(); // refresh
        string red_hearts_bar = "";
        if(red_hearts_fill > 0 && red_hearts_fill <= 24 &&
           red_hearts_cont > 0 && red_hearts_cont <= 24){
            for(unsigned int i=0;i<red_hearts_fill;i++){ red_hearts_bar+="M"; }
            for(unsigned int i=0;i<red_hearts_cont-red_hearts_fill;i++){ red_hearts_bar+="_"; }
            printf(" Red Hearts  : ");
            printf("%s",red_hearts_bar.c_str());
            printf(" %d/%d\n",red_hearts_fill,red_hearts_cont);
        } else {
            printf(" Red Hearts: %d/%d\n",red_hearts_fill,red_hearts_cont);
        }

        if(blue_hearts_fill > 0 && blue_hearts_fill <= 24){
            printf(" Blue Hearts : ");
            for(unsigned int i=0;i<blue_hearts_fill;i++){ printf("B"); }
            printf(" (%d)",blue_hearts_fill);
        } else {
            printf(" Blue Hearts: %d\n",blue_hearts_fill);
        }


        printf("\n [*] Pick Ups:\n");
        printf("  %.2d / 99 Coins\n",coins);
        printf("  %.2d / 99 Bombs\n",bombs);
        printf("  %.2d / 99 Keys\n\n",keys);
        Sleep(1000);
        system("cls");
        }
        return 0;
    }

};
Isaac::Isaac():proc_name("isaac-ng.exe") {}


void logo() {
string logo = "\n\n";
logo += "            __ _            _                _\n";
logo += "     /\\    / _| |          | |              | |\n";
logo += "    /  \\  | |_| |_ ___ _ __| |__   __ _  ___| | __\n";
logo += "   / /\\ \\ |  _| __/ _ \\ '__| '_ \\ / _` |/ __| |/ /\n";
logo += "  / ____ \\| | | ||  __/ |  | | | | (_| | (__|   <\n";
logo += " /_/    \\_\\_|  \\__\\___|_|  |_| |_|\\__,_|\\___|_|\\_\\\n";
logo += "\n";
cout << logo;
}

void menu_dialog(){
    logo();
    printf("\n");
    printf("[*] Status:\n");
    printf("\t1.) GAME STATUS MONITOR\n");
    printf("\t2.) Synchronize data [!]\n");
    printf("\t3.) Modify Value\n");

    printf("\n");
    printf("[*] Cheats:\n");
    printf("\tP.) Max Out Pick Ups\n");
    printf("\tR.) Full Red Hearts\n");
    printf("\tB.) Full Blue Hearts\n");
    printf("\n\tS.) SUPER REGENERATION\n");
    printf("\n");

}


int main() {
    string choice;
    int choice_int;

    while(true){
        Isaac game_instance;
        menu_dialog();
        show_status_stop = 0;
        cout << "> ";
        cin >> choice;
        if( choice == "cls" || choice == "clear" ){system("cls");continue;}
        choice_int = (int)choice[0];
        game_instance.update_isaac();
        game_instance.gather_stats();
        system("cls");
        switch(choice_int){
            case 49:
                game_instance.show_stats();
            break;
            case 50:
                system("cls");
                game_instance.show_addresses();
                printf("\n");
            break;
            case 51:
                game_instance.super_regeneration(3000);
            break;
            case 52:
                cout << (char)choice_int;
            break;

            case 112:
                Sleep(3000);
                game_instance.max_out_pick_ups();
                break; // p

            case 114:
                Sleep(3000);
                game_instance.full_red_hearts();
            break; // r

            case 98:
                Sleep(3000);
                game_instance.full_blue_hearts();
            break; // b

            case 115:
                Sleep(3000);
                game_instance.super_regeneration(500);
            break; // s

            default:
                printf("[-] Invalid option.");
                Sleep(1000);
                system("cls");
            break;
        }
    }






    return 0;
}
