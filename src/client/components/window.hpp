#pragma once

#include "shared.hpp"

#include "hook.hpp"
#include "string.hpp"

#include "loader/component_loader.hpp"

#include "imgui.hpp"
#include "movement.hpp"
#include "scheduler.hpp"
#include "security.hpp"

#include <hidusage.h>

namespace window
{
    extern int rawinput_x_current;
    extern int rawinput_y_current;
    extern int rawinput_x_old;
    extern int rawinput_y_old;

    extern char sys_cmdline[stock::MAX_STRING_CHARS];

    void MSG(const std::string& text, UINT flags = MB_OK);
}