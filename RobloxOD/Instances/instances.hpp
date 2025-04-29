#include <Windows.h>
#include <iostream>
#include <cstdint>
#include "../Process/process.hpp"
#include "../Memory/memory.hpp"
#include "../Offsets/offsets.hpp"
#include <vector>

class data
{
public:
	std::string torbxstring(uintptr_t address);
};

class instances
{
public:
	std::uintptr_t Address;
	std::string torbxstring(uintptr_t address);
    std::string getname(uintptr_t address)
    {
        uintptr_t nameptr = memory->read<uintptr_t>(address + Offsets::Name);

        std::string name;

        if (memory->read<int>(nameptr + 0x10) >= 16)
        {
            uintptr_t nameptr2 = memory->read<uintptr_t>(nameptr);

            while (memory->read<char>(nameptr2) != '\0')
            {
                name += memory->read<char>(nameptr2);
                nameptr2++;
            }
        }
        else
        {
            name = memory->read<std::string>(nameptr);
        }

        return name;
    }
    uintptr_t findfirstchild(uintptr_t address, std::string name)
    {
        for (auto child : this->getchildren(address))
        {
            if (this->getname(child) == name)
            {
                return child;
            }
        }

        return 0;
    }


    std::vector<uintptr_t> getchildren(uintptr_t address)
    {
        std::vector<uintptr_t> children;

        uintptr_t start = memory->read<uintptr_t>(address + Offsets::Children);
        uintptr_t end = memory->read<uintptr_t>(start + Offsets::ChildrenEnd);

        for (auto i = memory->read<uintptr_t>(start); i < end; i += 0x10)
        {
            children.push_back(memory->read<uintptr_t>(i));
        }

        return children;
    }
};

static auto rbx_dm = std::make_unique<data>();
static auto rbx = std::make_unique<instances>();
