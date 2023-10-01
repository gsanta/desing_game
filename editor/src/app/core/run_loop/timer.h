#pragma once

namespace spright
{
namespace editor
{
    class Timer
    {
    public:
        virtual void reset() = 0;

        virtual long elapsed() = 0;

        static Timer *getTimer();
    };
} // namespace editor
} // namespace spright
