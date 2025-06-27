#pragma once
#include "IState.hpp"
#include "Context.hpp"

class Context;
class ConfState;

class InitState : public IState
{
    public:
        void handle(Context& ctx) override;
};
