#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>

using _NtUnlockVirtualMemory = NTSTATUS(NTAPI*)(HANDLE, PVOID*, PSIZE_T, ULONG);

class Memory_
{
private:
    HANDLE mainHandle = nullptr;
    HMODULE NTDLLHANDLE = nullptr;

    bool ismemvalid(uintptr_t address);
    bool ispagephys(uintptr_t address);

public:
    void initialize(HANDLE hProc);
    std::string read_std_string(uintptr_t address);

    template <typename T>
    auto read_on_module(uintptr_t address) -> T;

    auto read_string_unknown(uintptr_t address) -> std::string {
        std::string result;
        char character = 0;
        int offset = 0;
        result.reserve(204);
        while (offset < 200) {
            character = read<char>(address + offset);
            if (character == 0) break;
            offset += sizeof(character);
            result.push_back(character);
        }
        return result;
    }

    template <typename T>
    T read(uintptr_t address);

    template <typename T>
    bool write(uintptr_t address, const T& value);

    bool read_array(uintptr_t address, void* buffer, size_t size);
};

static auto memory = std::make_unique<Memory_>();

template <typename T>
T Memory_::read(uintptr_t address)
{
    T val{};
    MEMORY_BASIC_INFORMATION mbi;


    for (int i = 0; i < 5; i++)
    {
        if (!ismemvalid(address) || !ispagephys(address))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (!VirtualQueryEx(mainHandle, reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi)))
            continue;

        auto NtUnlock = reinterpret_cast<_NtUnlockVirtualMemory>(
            GetProcAddress(NTDLLHANDLE, "NtUnlockVirtualMemory"));

        if (NtUnlock)
        {
            PVOID base = mbi.AllocationBase;
            SIZE_T region = mbi.RegionSize;
            NtUnlock(mainHandle, &base, &region, 1);
        }

        if (!ReadProcessMemory(mainHandle, reinterpret_cast<LPCVOID>(address), &val, sizeof(T), nullptr))
            continue;

        break;
    }
    return val;
}

template <typename T>
bool Memory_::write(uintptr_t address, const T& value)
{
    MEMORY_BASIC_INFORMATION mbi;

    for (int i = 0; i < 5; i++)
    {
        if (!ismemvalid(address) || !ispagephys(address))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (!VirtualQueryEx(mainHandle, reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi)))
            continue;

        auto NtUnlock = reinterpret_cast<_NtUnlockVirtualMemory>(
            GetProcAddress(NTDLLHANDLE, "NtUnlockVirtualMemory"));

        if (NtUnlock)
        {
            PVOID base = mbi.AllocationBase;
            SIZE_T region = mbi.RegionSize;
            NtUnlock(mainHandle, &base, &region, 1);
        }

        if (!WriteProcessMemory(mainHandle, (LPVOID)address, &value, sizeof(T), nullptr))
            continue;

        return true;
    }

    return false;
}
