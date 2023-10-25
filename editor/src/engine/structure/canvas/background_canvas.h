#pragma once

#include "../../graphics/renderable/bounds.h"
#include "canvas.h"

namespace spright
{
namespace engine
{
    /**
     * It is used as the big canvas for the entire document, it contains the other, smaller canvases like (Drawing.h).
     * It can be used to render graphics that are not related to a specific Drawing, like a global cursor and listens to global
     * pointer events.
    */
    class BackgroundCanvas : public Canvas
    {
    public:
        BackgroundCanvas(const Bounds &bounds);
    };

} // namespace engine
} // namespace spright
