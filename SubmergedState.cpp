#include "SubmergedState.hpp"
#include "Context.hpp"
#include "SurfacedState.hpp"
#include <iostream>

void SubmergedState::handle(Context& ctx)
{
    std::cout << "[Submerged] Reset counters.\n";
    ctx.ping_count = 0;
    auto status = ctx.trigger();
    if (status == Context::TriggerStatus::SUBMERGED)
    {
        ctx.set_state(std::make_unique<SubmergedState>());
    }
    if (status == Context::TriggerStatus::SURFACED)
    {
        ctx.set_state(std::make_unique<SurfacedState>());
    }
    ctx.delay_timer = 1; // Reset delay timer
    ctx.delay(ctx.delay_timer);
}
