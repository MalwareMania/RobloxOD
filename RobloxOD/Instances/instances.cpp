#include "instances.hpp"
#include <vector>


// idk why i made this lol

std::string instances::torbxstring(uintptr_t address)
{
    const auto size = memory->read<size_t>(address + 0x10);
    if (size >= 16)
        address = memory->read<uintptr_t>(address);

    std::string str;
    uint8_t code = 0;
    for (int i = 0; (code = memory->read<uint8_t>(address + i)); i++)
        str.push_back(code);

    return str;
}


std::string data::torbxstring(uintptr_t address)
{
    const auto size = memory->read<size_t>(address + 0x10);
    if (size >= 16)
        address = memory->read<uintptr_t>(address);

    std::string str;
    uint8_t code = 0;
    for (int i = 0; (code = memory->read<uint8_t>(address + i)); i++)
        str.push_back(code);

    return str;
}
