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
        // m_SelectionTileBounds.minX = std::numeric_limits<int>::max();
        // m_SelectionTileBounds.minY = std::numeric_limits<int>::max();
        // m_SelectionTileBounds.maxX = std::numeric_limits<int>::min();
        // m_SelectionTileBounds.maxY = std::numeric_limits<int>::min();
        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();
        // m_SelectionTileBounds = BoundsInt();
        m_SelectionBounds = Bounds();
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
} // namespace editor
} // namespace spright
