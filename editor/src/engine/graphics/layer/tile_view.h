#pragma once

#include "../../../maths/vec2.h"
#include "../../../maths/vec2_int.h"
#include "../renderable/bounds_int.h"
#include "../renderable/rect2d.h"

namespace spright
{
namespace engine
{
    class TileView
    {
    public:
        virtual Rect2D *getAtTilePos(int x, int y) const = 0;

        virtual Rect2D *getAtTileIndex(int tilePos) const = 0;

        virtual Rect2D &add(const Rect2D &rect, const Vec2Int &tilePos) = 0;

        virtual const BoundsInt &getTileBounds() const = 0;

        virtual int getTileIndex(int tileX, int tileY) const = 0;

        virtual std::vector<Rect2D *> &getTiles() = 0;

        virtual const std::vector<Rect2D *> &getTiles() const = 0;
    };
} // namespace engine
} // namespace spright
