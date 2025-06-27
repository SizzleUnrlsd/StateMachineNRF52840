#include "InitState.hpp"
#include "Context.hpp"

int main(void)
{
    Context ctx;
    ctx.set_state(std::make_unique<InitState>());

    ctx.is_conf_ok = true;
    ctx.set_trigger(Context::TriggerStatus::SUBMERGED);

    ctx.run();
    return 0;
}
