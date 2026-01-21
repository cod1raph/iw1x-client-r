#pragma once

class component_interface
{
public:
    virtual ~component_interface() noexcept
    {
    }

    virtual void post_start() noexcept
    {
    }

    virtual void post_load() noexcept
    {
    }

    virtual void pre_destroy() noexcept
    {
    }

    virtual void post_unpack() noexcept
    {
    }
    
    virtual void post_cgame() noexcept
    {
    }
    virtual void post_ui_mp() noexcept
    {
    }
    
    virtual void* load_import([[maybe_unused]] const std::string& library, [[maybe_unused]] const std::string& function) noexcept
    {
        return nullptr;
    }
};