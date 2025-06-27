#include "ConfState.hpp"
#include "Context.hpp"
#include "InitState.hpp"
#include "SubmergedState.hpp"
#include "SurfacedState.hpp"
#include <iostream>

void ConfState::handle(Context& ctx)
{
    std::cout << "[Conf] Checking configuration..." << std::endl;
    if (!ctx.is_conf_ok)
    {
        std::cout << "Invalid configuration. Returning to Init." << std::endl;
        ctx.set_state(std::make_unique<InitState>());
    }
    else
    {
        std::cout << "Configuration OK. Waiting for trigger..." << std::endl;
        auto status = ctx.trigger();
        if (status == Context::TriggerStatus::SUBMERGED)
        {
            ctx.set_state(std::make_unique<SubmergedState>());
        }
        else
        {
            ctx.set_state(std::make_unique<SurfacedState>());
        }
    }
}
