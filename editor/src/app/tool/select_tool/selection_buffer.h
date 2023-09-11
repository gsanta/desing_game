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

        const Bounds &getSelectionBounds(const TileLayer &layer);

    private:
        void updateBounds(int tileIndex, const TileLayer &layer);

    private:
        std::vector<int> m_TileIndexes;

        BoundsInt m_SelectionTileBounds;

        Bounds m_SelectionBounds;
    };
} // namespace editor
} // namespace spright
