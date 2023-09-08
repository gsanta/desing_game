#include "./selection_buffer.h"

namespace spright
{
namespace editor
{
    void SelectionBuffer::add(int tileIndex)
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

    void SelectionBuffer::setTileIndexes(std::vector<int> indexes) {
        m_TileIndexes = indexes;
    }

} // namespace editor
} // namespace spright
