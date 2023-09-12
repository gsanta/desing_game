#pragma once

#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/renderable/bounds.h"

#include <algorithm>
#include <vector>

namespace spright
{
namespace editor
{
    using namespace engine;

    class SelectionBuffer
    {
    public:
        void add(int tileIndex, const TileLayer &layer);

        void clear();

        const std::vector<int> &getTileIndexes();

        void setTileIndexes(std::vector<int> indexes, const TileLayer &layer);

        bool containsIndex(int index);

    private:
        std::vector<int> m_TileIndexes;

        BoundsInt m_SelectionTileBounds;

        Bounds m_SelectionBounds;

        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();
    };
} // namespace editor
} // namespace spright
