#pragma once

#include "shared.hpp"

#include "hook.hpp"
#include "concurrency.hpp"
#include "thread.hpp"

#include "loader/component_loader.hpp"

namespace scheduler
{
    using namespace std::literals;

    enum pipeline
    {
        client,
        server,
        cgame,
        renderer,
        async,
        count
    };

    static constexpr bool cond_continue = false;
    static constexpr bool cond_end = true;

    void schedule(const std::function<bool()>& callback, pipeline type = pipeline::async, std::chrono::milliseconds delay = 0ms);
    void loop(const std::function<void()>& callback, pipeline type = pipeline::async, std::chrono::milliseconds delay = 0ms);
    void once(const std::function<void()>& callback, pipeline type = pipeline::async, std::chrono::milliseconds delay = 0ms);
}