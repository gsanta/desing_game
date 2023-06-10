#pragma once

#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../../maths/vec2.h"

namespace spright
{
namespace editor
{
    using namespace engine;
    using namespace maths;

    class TempRectDrawer
    {
    public:
        void draw(TileLayer &tileLayer, Vec2 from, Vec2 to, int color);

        void reset();

        const Bounds &getBounds() const;

    private:
        void drawFilled(TileLayer &tileLayer, Vec2 from, Vec2 to, int color);

    private:
        Rect2D *m_FilledRect = nullptr;
    };
} // namespace editor
} // namespace spright
