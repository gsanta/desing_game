
#include "./selection_mover.h"

namespace spright
{
namespace editor
{
    Vec2 SelectionMover::move(TileLayer &layer, const Vec2 &curr, const Vec2 &prev, const Vec2 &start)
    {
        Vec2 deltaToStart = calcMoveToStart(layer, prev, start);
        Vec2 deltaToCurr = calcMoveToCurr(layer, curr, start);

        for (Rect2D *tile : layer.getTiles())
        {
            translate(*tile, deltaToStart, deltaToCurr);
        }

        Vec2 diff = deltaToCurr - deltaToStart;

        return diff;
    }

    Vec2 SelectionMover::move(TileLayer &layer,
                              const std::vector<int> &tileIndexes,
                              const Vec2 &curr,
                              const Vec2 &prev,
                              const Vec2 &start)
    {
        Vec2 deltaToStart = calcMoveToStart(layer, prev, start);
        Vec2 deltaToCurr = calcMoveToCurr(layer, curr, start);

        for (int tileIndex : tileIndexes)
        {
            std::cout << tileIndex << std::endl;
            Rect2D *tile = layer.getAtTileIndex(tileIndex);
            if (tile != nullptr)
            {
                translate(*tile, deltaToStart, deltaToCurr);
            }
        }

        std::cout << "----" << std::endl;

        Vec2 diff = deltaToCurr - deltaToStart;

        return diff;
    }

    Vec2 SelectionMover::calcMoveToStart(TileLayer &layer, const Vec2 &prev, const Vec2 &start)
    {
        Vec2 deltaPrev = prev - start;

        float tileSize = layer.getTileSize();

        float tiledDeltaPrevX = static_cast<int>(deltaPrev.x / tileSize) * tileSize;
        float tiledDeltaPrevY = static_cast<int>(deltaPrev.y / tileSize) * tileSize;
        return Vec2(tiledDeltaPrevX, tiledDeltaPrevY);
    }

    Vec2 SelectionMover::calcMoveToCurr(TileLayer &layer, const Vec2 &curr, const Vec2 &start)
    {
        Vec2 delta = curr - start;

        float tileSize = layer.getTileSize();

        float tiledDeltaX = static_cast<int>(delta.x / tileSize) * tileSize;
        float tiledDeltaY = static_cast<int>(delta.y / tileSize) * tileSize;
        return Vec2(tiledDeltaX, tiledDeltaY);
    }

    void SelectionMover::translate(Rect2D &tile, Vec2 &deltaToStart, const Vec2 &deltaToCurr)
    {
        tile.translate(-deltaToStart);
        tile.translate(deltaToCurr);
    }
} // namespace editor
} // namespace spright
