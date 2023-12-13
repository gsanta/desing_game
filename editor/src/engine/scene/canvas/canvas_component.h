#pragma once

namespace spright
{
namespace engine
{
    class Canvas;

    class CanvasComponent
    {
    public:
        virtual ~CanvasComponent() = default;

        virtual void onAddedToCanvas(Canvas &canvas) {};

        virtual CanvasComponent *clone(Canvas &canvas) = 0;
    };

} // namespace engine
} // namespace spright
