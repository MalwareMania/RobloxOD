#include <Windows.h>
#include <iostream>
#include <memory>
#include <Tlhelp32.h>

class Process_
{
private:
	uintptr_t process_id;
	uintptr_t process_handle;
public:
	DWORD get_process_id();
	uintptr_t get_module_base(DWORD pid);
	HANDLE open_handle();
};

static auto process = std::make_unique<Process_>();
