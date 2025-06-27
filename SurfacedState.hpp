#pragma once
#include "IState.hpp"

class Context;
class SubmergedState;

class SurfacedState : public IState
{
    public:
        void handle(Context& ctx) override;
};
