#include "pch.h"
#if 1
#include "ui.h"

namespace ui
{
    stock::cvar_t* cg_drawDisconnect;
    stock::cvar_t* cg_drawWeaponSelect;
    stock::cvar_t* cg_drawPing;
    stock::cvar_t* cg_drawFPS_custom;

    utils::hook::detour hook_CG_DrawWeaponSelect;
    
    static void stub_CG_DrawDisconnect()
    {
        if (!cg_drawDisconnect->integer)
            return;
        utils::hook::invoke<void>(ABSOLUTE_CGAME_MP(0x30015450));
    }

    static void stub_CG_DrawWeaponSelect()
    {
        if (!cg_drawWeaponSelect->integer)
            return;
        hook_CG_DrawWeaponSelect.invoke();
    }

    static void draw_ping()
    {
        if (!cg_drawPing->integer)
            return;

        if (*stock::clc_demoplaying)
            return;
        
        int* clSnap_ping = (int*)0x0143b148; // TODO: Verify and clean
        //int* cl_snap_ping = (int*)0x01432978;
        
        constexpr auto background_width = 50;
        constexpr auto background_height = 15;
        constexpr auto background_x = 640 - background_width;
        constexpr auto background_y = 23;
        float background_color[4] = {0, 0, 0, 0.6f};

        // Draw background
        (*stock::cgame_mp::syscall)(stock::CG_R_SETCOLOR, background_color);
        auto shader = (stock::qhandle_t)(*stock::cgame_mp::syscall)(stock::CG_R_REGISTERSHADERNOMIP, "black", 5);			
        stock::CG_DrawPic(background_x, background_y, background_width, background_height, shader);
        (*stock::cgame_mp::syscall)(stock::CG_R_SETCOLOR, NULL);

        // Draw text
        const auto fontID = 1;
        const auto scale = 0.21f;
        float text_color[4] = {1, 1, 1, 1};
        std::string text = utils::string::va("Ping: %i", *clSnap_ping);
        stock::SCR_DrawString(background_x + 3, background_y + 11, fontID, scale, text_color, text.c_str(), NULL, NULL, NULL);
    }
    
    static void stub_CG_DrawFPS_CG_DrawBigString(float x, float y, const char* s, float alpha)
    {
        if (cg_drawFPS_custom->integer)
        {
            int fps = 0;
            sscanf_s(s, "%i", &fps);
            
            constexpr auto background_width = 50;
            constexpr auto background_height = 15;
            constexpr auto background_x = 640 - background_width;
            constexpr auto background_y = 5;
            float background_color[4] = { 0, 0, 0, 0.6f };

            // Draw background
            (*stock::cgame_mp::syscall)(stock::CG_R_SETCOLOR, background_color);
            auto shader = (stock::qhandle_t)(*stock::cgame_mp::syscall)(stock::CG_R_REGISTERSHADERNOMIP, "black", 5);
            stock::CG_DrawPic(background_x, background_y, background_width, background_height, shader);
            (*stock::cgame_mp::syscall)(stock::CG_R_SETCOLOR, NULL);

            // Draw text
            const auto fontID = 1;
            const auto scale = 0.21f;
            float text_color[4] = { 1, 1, 1, 1 };
            std::string text = utils::string::va("FPS: %i", fps);
            stock::SCR_DrawString(background_x + 3, background_y + 11, fontID, scale, text_color, text.c_str(), NULL, NULL, NULL);
        }
        else
        {
            stock::CG_DrawBigString(x, y, s, alpha);
        }
    }
    
    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            cg_drawWeaponSelect = stock::Cvar_Get("cg_drawWeaponSelect", "1", stock::CVAR_ARCHIVE);
            cg_drawDisconnect = stock::Cvar_Get("cg_drawDisconnect", "1", stock::CVAR_ARCHIVE);
            cg_drawPing = stock::Cvar_Get("cg_drawPing", "0", stock::CVAR_ARCHIVE);
            cg_drawFPS_custom = stock::Cvar_Get("cg_drawFPS_custom", "0", stock::CVAR_ARCHIVE);

            scheduler::loop(draw_ping, scheduler::pipeline::cgame);
        }

        void post_cgame() override
        {
            utils::hook::call(ABSOLUTE_CGAME_MP(0x30014c73), stub_CG_DrawFPS_CG_DrawBigString);

            utils::hook::jump(ABSOLUTE_CGAME_MP(0x300159CC), stub_CG_DrawDisconnect);
            utils::hook::jump(ABSOLUTE_CGAME_MP(0x300159D4), stub_CG_DrawDisconnect);
            
            hook_CG_DrawWeaponSelect.create(ABSOLUTE_CGAME_MP(0x30037790), stub_CG_DrawWeaponSelect);
        }
    };
}

REGISTER_COMPONENT(ui::component)
#endif