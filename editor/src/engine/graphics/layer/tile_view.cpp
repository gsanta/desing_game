#include "./tile_view.h"

namespace spright
{
namespace engine
{
    TileView::TileView(const Bounds &bounds, float tileSize) : m_Bounds(bounds), m_TileSize(tileSize)
    {
        m_TileBounds =
            BoundsInt(0, 0, ceil((bounds.maxX - bounds.minX) / tileSize), ceil((bounds.maxY - bounds.minY) / tileSize));
        m_IndexSize = m_TileBounds.getWidth() * m_TileBounds.getHeight();
        m_TileIndexes = new Renderable2D *[m_IndexSize]();
    }

    TileView::TileView(const TileView &tileHolder)
        : m_TileBounds(tileHolder.m_TileBounds), m_IndexSize(tileHolder.m_IndexSize)
    {
        m_TileIndexes = new Renderable2D *[m_IndexSize]();
    }

    TileView::~TileView()
    {
        delete[] m_TileIndexes;
    }

    TileView &TileView::operator=(const TileView &that)
    {
        if (this != &that)
        {
            m_TileSize = that.m_TileSize;
            m_Bounds = that.m_Bounds;
            m_TileBounds = that.m_TileBounds;
            m_IndexSize = m_TileBounds.getWidth() * m_TileBounds.getHeight();
            m_TileIndexes = new Renderable2D *[m_IndexSize]();

            m_Group.clear();
            // delete[] m_TileIndexes;

            // init();
            // copyGroup(that.m_Group);
        }

        return *this;
    }


    Rect2D *TileView::getAtTileIndex(int tilePos) const
    {
        if (tilePos >= m_IndexSize || tilePos < 0)
        {
            return nullptr;
        }

        return static_cast<Rect2D *>(m_TileIndexes[tilePos]);
    }

    Rect2D *TileView::getAtTilePos(int x, int y) const
    {
        return getAtTileIndex(getTileIndex(x, y));
    }

    int TileView::getTileIndex(int tileX, int tileY) const
    {
        return m_TileBounds.getWidth() * tileY + tileX;
    }

    Vec2Int TileView::getTilePos(int tileIndex) const
    {
        return Vec2Int(getColumn(tileIndex), getRow(tileIndex));
    }

    Rect2D &TileView::add(const Rect2D &rect, const Vec2Int &tilePos)
    {
        int tileIndex = m_TileBounds.getWidth() * tilePos.y + tilePos.x;

        Rect2D &newRect = m_Group.add(rect);
        m_TileIndexes[tileIndex] = &newRect;

        newRect.setTileIndex(tileIndex);

        return newRect;
    }

    void TileView::removeAt(int tileIndex)
    {
        Vec2Int tilePos = getTilePos(tileIndex);

        int index = m_TileBounds.getWidth() * tilePos.y + tilePos.x;

        Rect2D *rect = getAtTileIndex(tileIndex);

        if (rect)
        {
            m_TileIndexes[index] = nullptr;
            m_Group.remove(*rect);
        }
    }


    std::vector<Rect2D *> &TileView::getTiles()
    {
        return m_Group.getRenderables();
    }

    const std::vector<Rect2D *> &TileView::getTiles() const
    {
        return m_Group.getRenderables();
    }

    const Bounds &TileView::getBounds() const
    {
        return m_Bounds;
    }

    const BoundsInt &TileView::getTileBounds() const
    {
        return m_TileBounds;
    }

    unsigned int TileView::getColumn(int tileIndex) const
    {
        return tileIndex % m_TileBounds.getWidth();
    }

    unsigned int TileView::getRow(int tileIndex) const
    {
        return tileIndex / m_TileBounds.getWidth();
    }
} // namespace engine
} // namespace spright
