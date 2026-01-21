#include "pch.h"
#if 1
#include "movement.h"

namespace movement
{
    stock::cvar_t* sensitivity_adsScaleEnable;
    stock::cvar_t* sensitivity_adsScale;
    stock::cvar_t* sensitivity_adsScaleSniperEnable;
    stock::cvar_t* sensitivity_adsScaleSniper;
    stock::cvar_t* m_rawinput;
    
    static void Cmd_LookBack()
    {
        stock::cl->viewangles[stock::YAW] += 180;
    }
    
    static float originalCGZoomSensitivity() noexcept
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

    static void cg_zoomSensitivity_scale() // See 30032e20
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
    
    static __declspec(naked) void stub_CG_zoomSensitivity_calculation() noexcept
    {
        __asm
        {
            fstp st(0)
            call cg_zoomSensitivity_scale
            ret
        }
    }
    
    class component final : public component_interface
    {
    public:
        void post_unpack() noexcept override
        {
            sensitivity_adsScaleEnable = stock::Cvar_Get("sensitivity_adsScaleEnable", "0", stock::CVAR_ARCHIVE);
            sensitivity_adsScale = stock::Cvar_Get("sensitivity_adsScale", "1", stock::CVAR_ARCHIVE);
            sensitivity_adsScaleSniperEnable = stock::Cvar_Get("sensitivity_adsScaleSniperEnable", "0", stock::CVAR_ARCHIVE);
            sensitivity_adsScaleSniper = stock::Cvar_Get("sensitivity_adsScaleSniper", "1", stock::CVAR_ARCHIVE);
            m_rawinput = stock::Cvar_Get("m_rawinput", "0", stock::CVAR_ARCHIVE);
            
            stock::Cmd_AddCommand("lookback", Cmd_LookBack);
        }

        void post_cgame() noexcept override
        {
            utils::hook::jump(ABSOLUTE_CGAME_MP(0x30032fe8), stub_CG_zoomSensitivity_calculation);
        }
    };
}

REGISTER_COMPONENT(movement::component)
#endif