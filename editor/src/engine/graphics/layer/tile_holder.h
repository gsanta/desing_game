/*
 * A basic implementation of TileView, which can be used for temporary storage of tiles (like shearing algorithm
 * which needs to copy tiles to a temporary place and then back to the original TileLayer)
 */

#pragma once

#include "../renderable/bounds_int.h"
#include "../renderable/rect2d.h"
#include "./tile_view.h"
#include "group.h"

namespace spright
{
namespace engine
{
    class TileHolder : public TileView
    {
    public:
        TileHolder(const BoundsInt &tileBounds);

        Rect2D *getAtTilePos(int x, int y) const override;

        Rect2D *getAtTileIndex(int tilePos) const override;

        Rect2D &add(const Rect2D &rect, const Vec2Int &tilePos) override;

        const BoundsInt &getTileBounds() const override;

        std::vector<Rect2D *> &getTiles();

        const std::vector<Rect2D *> &getTiles() const;

    private:
        Group<Rect2D> m_Group;

        BoundsInt m_TileBounds;

        Renderable2D **m_TileIndexes;
    };
} // namespace engine
} // namespace spright
