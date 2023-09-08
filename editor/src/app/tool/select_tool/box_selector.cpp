#include "box_selector.h"

namespace spright
{
namespace editor
{
    BoxSelector::BoxSelector(std::shared_ptr<SelectionBuffer> selectionBuffer) : m_SelectionBuffer(selectionBuffer)
    {
    }

    BoxSelector::~BoxSelector()
    {
    }

    void BoxSelector::select(const TileLayer &layer, const Vec2 &curr, const Vec2 &prev, const Vec2 &start)
    {
        float tileSize = layer.getTileSize();

        unsigned int color = 0x800099ff;

        BoundsInt bounds = calcSelectionBounds(layer, curr, start);

        // layer.clear();
        // clearSprites(layer);
        m_SelectionBuffer->clear();

        for (float i = bounds.minX; i < bounds.maxX; i += tileSize)
        {
            for (float j = bounds.minY; j < bounds.maxY; j += tileSize)
            {
                Rect2D rect(i, j, tileSize, tileSize, color);
                // rect.setCenterPosition(layer.getWorldPos(i, j));
                int tileIndex = layer.getTileIndex(rect.getCenterPosition2d());
                if (layer.getAtTileIndex(tileIndex) != nullptr)
                {
                    // layer.add(rect);
                    m_SelectionBuffer->add(tileIndex);
                }
            }
        }
    }

    bool BoxSelector::isSelectionChanged(const TileLayer &layer, const Vec2 &curr, const Vec2 &prev, const Vec2 &start) const
    {
        BoundsInt currBounds = calcSelectionBounds(layer, curr, start);
        BoundsInt prevBounds = calcSelectionBounds(layer, prev, start);

        return prevBounds != currBounds;
    }

    // void BoxSelector::setMoveStart(Vec2 pos)
    // {
    //     m_IsMoveStarted = true;
    //     m_MoveStart = pos;
    //     m_MovePrev = pos;
    // }

    // Vec2 BoxSelector::setMoveEnd(Vec2 pos)
    // {
    //     if (!m_IsMoveStarted)
    //     {
    //         throw "Call setMoveStart before calling setMoveEnd";
    //     }

    //     Vec2 delta = pos - m_MoveStart;
    //     Vec2 deltaPrev = m_MovePrev - m_MoveStart;

    //     float tileSize = m_Layer.getTileSize();

    //     float tiledDeltaPrevX = static_cast<int>(deltaPrev.x / tileSize) * tileSize;
    //     float tiledDeltaPrevY = static_cast<int>(deltaPrev.y / tileSize) * tileSize;
    //     Vec2 tileDeltaPrev = Vec2(tiledDeltaPrevX, tiledDeltaPrevY);

    //     float tiledDeltaX = static_cast<int>(delta.x / tileSize) * tileSize;
    //     float tiledDeltaY = static_cast<int>(delta.y / tileSize) * tileSize;
    //     Vec2 tileDelta = Vec2(tiledDeltaX, tiledDeltaY);

    //     for (Rect2D *sprite : m_Layer.getTiles())
    //     {
    //         sprite->translate(-tileDeltaPrev);
    //         sprite->translate(tileDelta);
    //     }

    //     m_MovePrev = pos;

    //     Vec2 diff = tileDelta - tileDeltaPrev;

    //     m_Bounds.translate(diff.x, diff.y);

    //     return diff;
    // }

    void BoxSelector::clear()
    {

    }

    BoundsInt BoxSelector::calcSelectionBounds(const TileLayer &layer, const Vec2 &vec1, const Vec2 &vec2) const
    {
        Bounds bounds(vec1, vec2);

        Vec2 bottomLeft = bounds.getBottomLeft();
        Vec2 topRight = bounds.getTopRight();

        float tileSize = layer.getTileSize();

        unsigned int color = 0x800099ff;

        float xStart = static_cast<int>(bottomLeft.x / tileSize) * tileSize - tileSize;
        float xEnd = static_cast<int>(topRight.x / tileSize) * tileSize;
        float yStart = static_cast<int>(bottomLeft.y / tileSize) * tileSize - tileSize;
        float yEnd = static_cast<int>(topRight.y / tileSize) * tileSize;

        return BoundsInt(xStart, yStart, xEnd, yEnd);
    }

    void BoxSelector::clearSprites(TileLayer &layer)
    {
        for (int tileIndex : m_SelectionBuffer->getTileIndexes())
        {
            layer.removeAt(tileIndex);
        }
    }
} // namespace editor
} // namespace spright
