#pragma once
#include "IState.hpp"
#include <memory>

class Context;
class InitState;
class SubmergedState;
class SurfacedState;

class ConfState : public IState
{
    public:
        void handle(Context& ctx) override;
};
