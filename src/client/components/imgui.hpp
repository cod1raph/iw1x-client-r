#pragma once

#include "shared.hpp"

#include "string.hpp"

#include "loader/component_loader.hpp"

#include "ui.hpp"
#include "movement.hpp"
#include "view.hpp"

#include <imgui.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_win32.h>

namespace imgui
{
    extern bool displayed;
    extern bool waitForMenuKeyRelease;

    void menu_updates_settings();
    void toggle_menu(bool closedUsingButton);
    void new_frame();
    void draw_menu();
    void draw_menu_tab_Security();
    void draw_menu_tab_UI();
    void draw_menu_tab_View();
    void draw_menu_tab_Movement();
    void end_frame();
}