#include "./selection_buffer.h"

namespace spright
{
namespace editor
{
    void SelectionBuffer::add(int tileIndex, const TileLayer &layer)
    {
        m_TileIndexes.push_back(tileIndex);
    }

    void SelectionBuffer::clear()
    {
        m_TileIndexes.clear();
    }

    const std::vector<int> &SelectionBuffer::getTileIndexes()
    {
        return m_TileIndexes;
    }

    void SelectionBuffer::setTileIndexes(std::vector<int> indexes, const TileLayer &layer)
    {
        m_TileIndexes = indexes;
    }

    bool SelectionBuffer::containsIndex(int index)
    {
        if (std::find(m_TileIndexes.begin(), m_TileIndexes.end(), index) != m_TileIndexes.end())
        {
            return true;
        }
        return false;
    }

    const Bounds &SelectionBuffer::getSelectionBounds(const TileLayer &layer)
    {
        if (m_SelectionBounds.isNull())
        {
            m_SelectionBounds =
                Bounds(layer.getBottomLeftPos(m_SelectionTileBounds.getBottomLeft()),
                       layer.getBottomLeftPos(m_SelectionTileBounds.getTopRight()) + layer.getTileSize());
        }

        return m_SelectionBounds;
    }

    void SelectionBuffer::updateBounds(int tileIndex, const TileLayer &layer)
    {
        Vec2Int tilePos = layer.getTilePos(tileIndex);

        if (m_SelectionTileBounds.isDefault())
        {
            m_SelectionTileBounds = BoundsInt(tilePos, tilePos);
        }
        else
        {
            m_SelectionTileBounds.expand(tilePos);
        }
    }

} // namespace editor
} // namespace spright
