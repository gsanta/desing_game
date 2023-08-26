#pragma once

#include "../../../maths/vec2.h"
#include "../../../maths/vec2_int.h"
#include "../renderable/rect2d.h"

namespace spright
{
namespace engine
{
    class TileView {
    public:
        virtual Rect2D *getAtTilePos(int x, int y) const = 0;

        virtual Vec2 getWorldPos(const Vec2Int tilePos) const = 0;
    };
}
}
