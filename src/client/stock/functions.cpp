#include "pch.h"

#include "shared.h"

namespace stock
{
    int Cmd_Argc()
    {
        return *cmd_argc;
    }
    
    char* Cmd_Argv(int arg)
    {
        return cmd_argv[arg];
    }
    
    weaponInfo_t* BG_GetInfoForWeapon(int weaponNum)
    {
        auto cg_weapons_ptr = *reinterpret_cast<uintptr_t*>(*cg_weapons);
        return reinterpret_cast<weaponInfo_t**>(cg_weapons_ptr)[weaponNum];
    }
    
    const char* Info_ValueForKey(const char* buffer, const char* key)
    {
        __asm
        {
            mov ebx, key;
            mov ecx, buffer;
            mov eax, 0x0044ada0;
            call eax;
        }
    }
}