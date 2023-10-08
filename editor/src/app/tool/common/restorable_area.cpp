#include "./restorable_area.h"

namespace spright
{
namespace editor
{

    void RestorableArea::saveArea(const TileLayer &activeLayer, const SelectionBuffer &selectionBuffer)
    {
        m_OrigIndexes.clear();
        m_OrigTiles.reset(new TileView(activeLayer.getBounds(), activeLayer.getTileSize()));

        const BoundsInt &selectionBounds = selectionBuffer.getTileBounds();
        const BoundsInt impactBounds = getBoundsOfImpactedArea(selectionBounds, activeLayer.getTileBounds());

        Vec2Int center = selectionBounds.getCenter();
        m_AreaCenter = activeLayer.getCenterPos(center);

        tile_operation_copy_area(activeLayer, *m_OrigTiles, impactBounds, impactBounds.getBottomLeft());

        for (Rect2D *tile : m_OrigTiles->getTiles())
        {
            m_OrigIndexes.push_back(m_OrigTiles->getTileIndex(*tile));
        }
    }

    const std::vector<int> &RestorableArea::restoreArea(TileLayer &activeLayer, const SelectionBuffer &selectionBuffer)
    {
        const std::vector<int> &oldIndexes = selectionBuffer.getTileIndexes();

        for (int index : oldIndexes)
        {
            activeLayer.removeAt(index);
        }

        tile_operation_copy_all(*m_OrigTiles, activeLayer);

        return m_OrigIndexes;
    }

    /*
    // Get the maximum area that can be impacted by the rotation, so original state can be restored
    */
    BoundsInt RestorableArea::getBoundsOfImpactedArea(const BoundsInt &selectionBounds,
                                                      const BoundsInt &maxBounds) const
    {
        Vec2Int center = selectionBounds.getCenter();
        int size = selectionBounds.getWidth() > selectionBounds.getHeight() ? selectionBounds.getWidth()
                                                                            : selectionBounds.getHeight();
        int halfSize = ((int)size / 2.0) + 1;

        int bottomLeftX = center.x - halfSize > maxBounds.minX ? center.x - halfSize : maxBounds.minX;
        int bottomLeftY = center.y - halfSize > maxBounds.minY ? center.y - halfSize : maxBounds.minY;
        int topRightX = center.x + halfSize < maxBounds.maxX ? center.x + halfSize : maxBounds.maxX;
        int topRightY = center.y + halfSize < maxBounds.maxY ? center.y + halfSize : maxBounds.maxY;

        return BoundsInt(bottomLeftX, bottomLeftY, topRightX, topRightY);
    }
}
}
