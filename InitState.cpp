#include "InitState.hpp"
#include "ConfState.hpp"
#include <iostream>

void InitState::handle(Context& ctx)
{
    std::cout << "[Init] Initialisation...\n";
    ctx.set_state(std::make_unique<ConfState>());
}
