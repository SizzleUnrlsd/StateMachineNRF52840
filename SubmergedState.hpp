#pragma once
#include "IState.hpp"

class Context;
class SurfacedState;

class SubmergedState : public IState
{
    public:
        void handle(Context& ctx) override;
};
