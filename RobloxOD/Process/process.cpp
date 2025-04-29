#include "process.hpp"

DWORD Process_::get_process_id()
{
    PROCESSENTRY32W entry = { sizeof(PROCESSENTRY32W) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                this->process_id = entry.th32ProcessID;
                CloseHandle(snapshot);
                return this->process_id;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}
uintptr_t Process_::get_module_base(DWORD pid)
{
    MODULEENTRY32W entry = { sizeof(entry) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    if (Module32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szModule, L"RobloxPlayerBeta.exe") == 0) {
                CloseHandle(snapshot);
                return reinterpret_cast<uintptr_t>(entry.modBaseAddr);
            }
        } while (Module32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return 0;
}



HANDLE Process_::open_handle()
{
    HANDLE poses = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->process_id);
    this->process_handle = reinterpret_cast<uintptr_t>(poses);
    return poses;
}
