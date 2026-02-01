#include "pch.h"
#if 1
#include "shared.h"

#include "hook.h"

#include "loader/component_loader.h"

namespace test
{
    //utils::hook::detour hook_Test;

#if 0
    static void stub_Test(const char* s, const char* key)
    {
        std::stringstream ss;
        ss << "####### test: s: " << s << " , key: " << key << std::endl;
        OutputDebugString(ss.str().c_str());


    }
#endif

#if 0
    static void stub_Test()
    {
        OutputDebugString("stub_Test\n");
        return;
        
        //hook_Test.invoke();
    }
#endif
    
    class component final : public component_interface
    {
    public:
        void post_unpack() override
        {
            //stock::Cmd_AddCommand("test", Command_test);
            //hook_Test.create(0x00413260, stub_Test);
            //utils::hook::call(0x0041333b, stub_Test);
        }
        void post_cgame() override
        {
            //hook_Test.create(ABSOLUTE_CGAME_MP(0x30028a70), stub_Test);
        }
        void post_ui_mp() override
        {
            //utils::hook::call(ABSOLUTE_UI_MP(0x4000acee), stub_Test);
            //hook_Test.create(ABSOLUTE_UI_MP(0x4000c500), stub_Test);
        }
    };
}

REGISTER_COMPONENT(test::component)
#endif