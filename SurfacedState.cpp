#include "SurfacedState.hpp"
#include "Context.hpp"
#include "SubmergedState.hpp"
#include <iostream>

void SurfacedState::handle(Context& ctx)
{
    auto status = ctx.trigger();
    // std::cout << "[Surfaced] Analyse ping...\n";
    std::cout << "[" << ctx.triggerStatusToString(status) << "]" << "Analyse ping..." << std::endl;

    if (ctx.ping_count < ctx.max_ping_startup)
    {
        if (status == Context::TriggerStatus::SUBMERGED)
        {
            std::cout << "[Surfaced] but Submerged detected → Force the ping" << std::endl;
        }
        ctx.ping();
        ctx.ping_count++;
        ctx.delay(1);
    }
    if ((ctx.ping_count >= ctx.max_ping_startup))
    {
        // Here to force ctx.ping_count to be greater than max_ping_startup and not interrupt it
        // Check the status before incrementing the counter
        if (status == Context::TriggerStatus::SUBMERGED)
        {
            ctx.set_state(std::make_unique<SubmergedState>());
            return;
        }
        ctx.delay_timer += 10;
        ctx.ping();
        ctx.ping_count++;
        ctx.delay(ctx.delay_timer);
    }
}
