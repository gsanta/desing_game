#include "./tile_holder.h"

namespace spright
{
namespace engine
{
    TileHolder::TileHolder(const BoundsInt &tileBounds) : m_Group(group), m_TileBounds(tileBounds)
    {
        m_TileIndexes = new Renderable2D *[m_IndexSize]();
    }

    Rect2D *TileHolder::getAtTileIndex(int tilePos) const
    {
        return static_cast<Rect2D *>(m_TileIndexes[tilePos]);
    }

    Rect2D *TileHolder::getAtTilePos(int x, int y) const
    {
        return getAtTileIndex(getTileIndex(x, y));
    }

    Rect2D &TileHolder::add(const Rect2D &rect, const Vec2Int &tilePos) {
        int tileIndex = m_TileBounds.getWidth() * tilePos.y + tilePos.x;

        Rect2D &newRect = m_Group.add(rect);
        m_TileIndexes[tileIndex] = &newRect;

        newRect.setTileIndex(tileIndex);

        return newRect;
    }

    const BoundsInt &TileHolder::getTileBounds() const
    {
        return m_TileBounds;
    }
}
}
