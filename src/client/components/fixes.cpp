#include "pch.h"
#if 1
#include "shared.hpp"

#include "hook.hpp"

#include "loader/component_loader.hpp"

namespace fixes
{
    utils::hook::detour hook_UI_StartServerRefresh;
    utils::hook::detour hook_CL_Disconnect;
    utils::hook::detour hook_CL_RefPrintf;

    uintptr_t pfield_charevent_return = 0x40CB77;
    uintptr_t pfield_charevent_continue = 0x40CB23;
    static __declspec(naked) void stub_Field_CharEvent_ignore_console_char()
    {
        // See https://github.com/xtnded/codextended-client/blob/45af251518a390ab08b1c8713a6a1544b70114a1/cl_input.cpp#L77

        __asm
        {
            cmp ebx, 0x20;
            jge check;
            jmp pfield_charevent_return;

        check:
            cmp ebx, 0x7E;
            jl checked;
            jmp pfield_charevent_return;

        checked:
            jmp pfield_charevent_continue;
        }
    }

    static void stub_UI_StartServerRefresh(stock::qboolean full)
    {
        if (*stock::refreshActive)
            return;
        hook_UI_StartServerRefresh.invoke(full);
    }

    static char* stub_strncpy_remove_squares_hostname(char* dest, const char* src, int destsize)
    {
#pragma warning(push)
#pragma warning(disable: 4996)
        strncpy(dest, utils::string::clean(src, false).c_str(), destsize); // destsize is already max-1 (=31), so not using _TRUNCATE, not to lose a char
#pragma warning(pop)
        return dest;
    }
    
    static void stub_CL_Disconnect(stock::qboolean showMainMenu)
    {
        hook_CL_Disconnect.invoke(showMainMenu);
        stock::Cvar_Set("timescale", "1");
        stock::Cvar_Set("fs_game", "");
    }

    static void stub_CL_RefPrintf(int print_level, const char* fmt, ...)
    {
        va_list argptr;
        char msg[stock::MAXPRINTMSG];

        va_start(argptr, fmt);
        vsnprintf_s(msg, sizeof(msg), _TRUNCATE, fmt, argptr);
        va_end(argptr);

        if (print_level == stock::PRINT_ALL)
        {
            stock::Com_Printf("%s", msg);
        }
        else if (print_level == stock::PRINT_WARNING)
        {
            stock::Com_Printf("%s%s", stock::S_COLOR_YELLOW, msg);
        }
        else if (print_level == stock::PRINT_DEVELOPER)
        {
            stock::Com_Printf("%s%s", stock::S_COLOR_RED, msg);
        }
    }
    
    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            /*
            Prevent the CD Key error when joining a server (occurs when joined a fs_game server previously)
            ("CD Key is not valid. Please enter...")
            See https://github.com/xtnded/codextended-client/blob/45af251518a390ab08b1c8713a6a1544b70114a1/fixes.cpp#L21
            */
            utils::hook::nop(0x0042d122, 5);

            // Prevent displaying squares in server name (occurs when hostname contains e.g. SOH chars)
            utils::hook::call(0x412A2C, stub_strncpy_remove_squares_hostname); // CL_SetServerInfo
            utils::hook::call(0x0041333b, stub_strncpy_remove_squares_hostname); // CL_ServerStatus
            
            // Prevent inserting the char of the console key in the text field (e.g. Superscript Two gets inserted using french keyboard)
            utils::hook::jump(0x40CB1E, stub_Field_CharEvent_ignore_console_char);

            // Reset timescale cvar after leaving server
            // Reset fs_game cvar after leaving server
            hook_CL_Disconnect.create(0x0040ef90, stub_CL_Disconnect);

            // Fix printing of OpenGL extensions causing "Buffer overrun" on some PCs
            hook_CL_RefPrintf.create(0x00411460, stub_CL_RefPrintf);
        }

        void post_ui_mp() override
        {
            // Prevent displaying servers twice (occurs if double click Refresh List)
            hook_UI_StartServerRefresh.create(ABSOLUTE_UI_MP(0x4000ea90), stub_UI_StartServerRefresh);

            // Prevent removing the 8 first chars of path when downloading
            utils::hook::nop(ABSOLUTE_UI_MP(0x4000e13a), 3);
            utils::hook::nop(ABSOLUTE_UI_MP(0x4000e155), 3);
        }
    };
}

REGISTER_COMPONENT(fixes::component)
#endif