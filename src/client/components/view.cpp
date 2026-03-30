#include "pch.h"
#if 1
#include "view.hpp"

namespace view
{
    stock::cvar_t* cg_fovScaleEnable;
    stock::cvar_t* cg_fovScale;
    
    static float scaledFOV(float fov)
    {
        int* flag = (int*)ABSOLUTE_CGAME_MP(0x302071dc);
        if (*flag & stock::EF_MG42_ACTIVE)
            return 55;

        if (cg_fovScaleEnable->integer)
            return fov * cg_fovScale->value;

        return fov;
    }
    
    static __declspec(naked) void stub_CG_CalcFov_return()
    {
        __asm
        {
            sub esp, 0x4;
            fstp dword ptr[esp];			
            push dword ptr[esp];
            call scaledFOV;
            add esp, 0x4;

            fstp dword ptr[esp];
            fld dword ptr[esp];
            add esp, 0x4;

            pop ecx;
            ret;
        }
    }
    
    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            cg_fovScaleEnable = stock::Cvar_Get("cg_fovScaleEnable", "0", stock::CVAR_ARCHIVE);
            cg_fovScale = stock::Cvar_Get("cg_fovScale", "1", stock::CVAR_ARCHIVE);
            
            // Increase min number of segments in RB_SurfaceCylinder, so big cylinders look more rounded.
            constexpr auto minSegments = 32;
            utils::hook::set<uint8_t>(0x00511403 + 2, static_cast<uint8_t>(minSegments));
            utils::hook::set(0x0051140c + 4, minSegments);
        }

        void post_cgame() override
        {
            utils::hook::jump(ABSOLUTE_CGAME_MP(0x30032f2a), stub_CG_CalcFov_return);
        }
    };
}

REGISTER_COMPONENT(view::component)
#endif