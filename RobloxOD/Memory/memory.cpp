#include "memory.hpp"
#include <thread>
#include <chrono>

bool Memory_::ismemvalid(uintptr_t address)
{
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQueryEx(mainHandle, reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi)))
	{
		return mbi.State == MEM_COMMIT && (mbi.Protect & (PAGE_READWRITE | PAGE_READONLY | PAGE_EXECUTE_READWRITE));
	}
	return false;
}

std::string Memory_::read_std_string(uintptr_t address) {
	size_t length = read<size_t>(address + 0x10);
	if (length == 0 || length > 256) return "";

	uintptr_t data = address;
	if (length >= 16) {
		data = read<uintptr_t>(address);
	}

	std::string out;
	for (size_t i = 0; i < length; ++i) {
		out.push_back(read<char>(data + i));
	}

	return out;
}

bool Memory_::ispagephys(uintptr_t address)
{
	// Modify this if needed
	return true;
}

void Memory_::initialize(HANDLE hProc)
{
	mainHandle = hProc;
	NTDLLHANDLE = GetModuleHandleA("ntdll.dll");
}

bool Memory_::read_array(uintptr_t address, void* buffer, size_t size)
{
	SIZE_T read = 0;
	return ReadProcessMemory(mainHandle, reinterpret_cast<LPCVOID>(address), buffer, size, &read);
}
