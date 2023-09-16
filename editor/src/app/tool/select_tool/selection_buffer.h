#pragma once

#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/renderable/bounds_int.h"
#include "../../document/document_store.h"

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
        SelectionBuffer(std::shared_ptr<DocumentStore> documentStore);

        void add(int tileIndex, const TileLayer &layer);

        void clear();

        const std::vector<int> &getTileIndexes();

        void setTileIndexes(std::vector<int> indexes, const TileLayer &layer);

        bool containsIndex(int index);

        const BoundsInt &getSelectionBounds();

    private:
        void updateBounds();

    private:
        std::shared_ptr<DocumentStore> m_DocumentStore;

        std::vector<int> m_TileIndexes;

        BoundsInt m_SelectionTileBounds;

        bool m_IsBoundsDirty = false;

        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int maxX = std::numeric_limits<int>::min();
        int maxY = std::numeric_limits<int>::min();
    };
} // namespace editor
} // namespace spright
