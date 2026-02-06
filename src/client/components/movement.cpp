#include "pch.h"
#if 1
#include "movement.h"

namespace movement
{
    utils::hook::detour hook_IN_MouseMove;

    stock::cvar_t* sensitivity_adsScaleEnable;
    stock::cvar_t* sensitivity_adsScale;
    stock::cvar_t* sensitivity_adsScaleSniperEnable;
    stock::cvar_t* sensitivity_adsScaleSniper;
    stock::cvar_t* m_rawinput;
    
    static void Cmd_LookBack()
    {
        stock::cl->viewangles[stock::YAW] += 180;
    }
    
    static float originalCGZoomSensitivity()
    {
        return *stock::fov_visible / cvars::vm::cg_fov->value; // See 30032fe8
    }
    static float scaledCGZoomSensitivity()
    {
        if (!*stock::pm)
            return originalCGZoomSensitivity();
        
        stock::weaponInfo_t* weaponInfo = stock::BG_GetInfoForWeapon((*stock::pm)->ps->weapon);
        
        if (*weaponInfo->adsOverlayShader) // sniper
        {
            if (sensitivity_adsScaleSniperEnable->integer)
                return originalCGZoomSensitivity() * sensitivity_adsScaleSniper->value;
            else
                return originalCGZoomSensitivity();
        }
        else if (sensitivity_adsScaleEnable->integer)
            return originalCGZoomSensitivity() * sensitivity_adsScale->value;
        else
            return originalCGZoomSensitivity();
    }
    static void check_scale_sensitivity() // See 30032e20
    {
        if (*stock::ads_progress == 1)
        {
            stock::cg->zoomSensitivity = scaledCGZoomSensitivity();
        }
        else if (*stock::ads_progress != 0)
        {
            auto unknown = (bool*)ABSOLUTE_CGAME_MP(0x30209458); // True when zoomed out before max in, = "ads aborted"?

            if (*unknown)
                stock::cg->zoomSensitivity = scaledCGZoomSensitivity();
            else
                stock::cg->zoomSensitivity = originalCGZoomSensitivity();
        }
        else
        {
            stock::cg->zoomSensitivity = originalCGZoomSensitivity();
        }
    }
    static __declspec(naked) void stub_CG_CalcViewValues_ret()
    {
        __asm
        {
            fstp st(0)
            call check_scale_sensitivity
            ret
        }
    }

    static void rawInput_move()
    {
        auto delta_x = window::rawinput_x_current - window::rawinput_x_old;
        auto delta_y = window::rawinput_y_current - window::rawinput_y_old;

        window::rawinput_x_old = window::rawinput_x_current;
        window::rawinput_y_old = window::rawinput_y_current;

        stock::CL_MouseEvent(delta_x, delta_y);
    }
    static void stub_IN_MouseMove()
    {
        // Apply raw input only when player can move // TODO: Maybe hook CG_MouseEvent instead then
        if (m_rawinput->integer)
        {
            if (*stock::cls_keyCatchers == 0) // TODO: Figure out why have to use "== 0" instead of "& KEYCATCH_CGAME"
            {
                rawInput_move();
                return;
            }

            // If a .menu is displayed, and cl_bypassMouseInput is enabled, player can move (e.g. wm_quickmessage.menu)
            if ((*stock::cls_keyCatchers & stock::KEYCATCH_UI) && cvars::cl_bypassMouseInput->integer)
            {
                rawInput_move();
                return;
            }

            if (cvars::r_fullscreen->integer && *stock::cgvm != NULL)
            {
                // .menu + console opened = player can't move
                if (*stock::cls_keyCatchers == 3)
                {
                    hook_IN_MouseMove.invoke();
                    return;
                }

                if (*stock::cls_keyCatchers & stock::KEYCATCH_CONSOLE)
                {
                    rawInput_move();
                    return;
                }
            }

            if (*stock::cls_keyCatchers & stock::KEYCATCH_MESSAGE)
            {
                rawInput_move();
                return;
            }
        }

        hook_IN_MouseMove.invoke();
    }
    
    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            sensitivity_adsScaleEnable = stock::Cvar_Get("sensitivity_adsScaleEnable", "0", stock::CVAR_ARCHIVE);
            sensitivity_adsScale = stock::Cvar_Get("sensitivity_adsScale", "1", stock::CVAR_ARCHIVE);
            sensitivity_adsScaleSniperEnable = stock::Cvar_Get("sensitivity_adsScaleSniperEnable", "0", stock::CVAR_ARCHIVE);
            sensitivity_adsScaleSniper = stock::Cvar_Get("sensitivity_adsScaleSniper", "1", stock::CVAR_ARCHIVE);
            m_rawinput = stock::Cvar_Get("m_rawinput", "0", stock::CVAR_ARCHIVE);
            
            stock::Cmd_AddCommand("lookback", Cmd_LookBack);

            hook_IN_MouseMove.create(0x00461850, stub_IN_MouseMove); // To apply raw input
        }

        void post_cgame() override
        {
            utils::hook::jump(ABSOLUTE_CGAME_MP(0x30032fe8), stub_CG_CalcViewValues_ret); // To apply ADS sensitivity scale
        }
    };
}

REGISTER_COMPONENT(movement::component)
#endif