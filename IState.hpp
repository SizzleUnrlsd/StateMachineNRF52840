#pragma once

class Context;

class IState
{
    public:
        virtual ~IState() = default;
        virtual void handle(Context& ctx) = 0;
};