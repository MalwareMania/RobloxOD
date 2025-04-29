#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>
#include <array>
#include "Instances/instances.hpp"
#include "scheduler.hpp"

int main()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 11);
    std::string text = R"(
  _____       _     _             ______      _                        _ 
 |  __ \     | |   | |           |  ____|    | |                      | |
 | |__) |___ | |__ | | _____  __ | |__  __  _| |_ ___ _ __ _ __   __ _| |
 |  _  // _ \| '_ \| |/ _ \ \/ / |  __| \ \/ / __/ _ \ '__| '_ \ / _` | |
 | | \ \ (_) | |_) | | (_) >  <  | |____ >  <| ||  __/ |  | | | | (_| | |
 |_|  \_\___/|_.__/|_|\___/_/\_\ |______/_/\_\\__\___|_|  |_| |_|\__,_|_|
                                                                         
                                                                         
)";

    auto ntdllhandle = GetModuleHandleA("ntdll.dll");
    std::cout << text << "\n";
    std::cout << "[+] Roblox External V1.0\n";
    DWORD pid = 0;
    bool printed = false;

    while ((pid = process->get_process_id()) == 0)
    {
        if (!printed)
        {
            std::cout << "[+] Waiting for RobloxPlayerBeta.exe...\n";
            printed = true;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "[+] Getting Process ID...\n";
    Sleep(1000);
    std::cout << "[+] Got Process ID: " << pid << "\n";
    std::cout << "[+] Getting Module Base Address...\n";
    Sleep(3000);
    uintptr_t base = process->get_module_base(pid);
    std::cout << "[+] Got Module Base Address: " << base << "\n";
    std::cout << "[+] Found Ntdll Handle At: " << reinterpret_cast<void*>(ntdllhandle) << "\n";
    std::cout << "[+] Found Hyperion Base At: " << reinterpret_cast<void*>(base) << "\n";

    HANDLE hProc = process->open_handle();
    if (!hProc) {
        std::cerr << "[-] Failed to open Roblox process.\n";
        return 1;
    }

    std::cout << "[+] Got Roblox Handle: " << hProc << "\n";

    memory->initialize(hProc);

    std::cout << "[+] Initiliazed\n\n";


    auto datamodel = scheduler->getdatamodel();
    auto humanoid = scheduler->gethumanoid();
    auto playerlist = scheduler->getplayerlist();
    auto scriptcontext = scheduler->getscriptcontext();
    auto rootpart = scheduler->gethumanoidrootpart();
    scheduler->set_walkspeed(50.0f);
    std::cout << "[+] Found Data Model At: 0x" << std::hex << datamodel << "\n";
    std::cout << "[+] Found Humanoid At: 0x" << std::hex << humanoid << "\n";
    std::cout << "[+] Found ScriptContext At: 0x" << std::hex << scriptcontext << "\n";
    std::cout << "[+] Found HumanoidRootPart at: 0x" << std::hex << rootpart << "\n";
    std::cout << "[+] Set Speed to 50\n";
    std::cout << "[+] Getting PlayerList...\n";
    for (auto player : playerlist)
    {
        std::string name = rbx->getname(player);
        std::cout << "Player: " << name << "\n";
    }

    CloseHandle(hProc);
    system("pause");
    return 0;
}
