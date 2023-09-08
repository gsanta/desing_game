#pragma once
#include <vector>

namespace spright
{
namespace editor
{

    class SelectionBuffer
    {
    public:
        void add(int tileIndex);

        void clear();

        const std::vector<int> &getTileIndexes();

        void setTileIndexes(std::vector<int> indexes);

    private:
        std::vector<int> m_TileIndexes;
    };
} // namespace editor
} // namespace spright
