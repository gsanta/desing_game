#pragma once

#include "../../algorithm/tile_operations.h"
#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/layer/tile_view.h"
#include "../select_tool/selection_buffer.h"
#include "../tool/tool_context.h"

#include <memory>
#include <vector>

namespace spright
{
namespace editor
{
    using namespace engine;

    /*
    // Can be used by tools that executes an action on the original shape multiple times on pointer move
    */
    class RestorableArea
    {
    public:
        void saveArea(const TileLayer &activeLayer, const SelectionBuffer &selectionBuffer);

        const std::vector<int> &restoreArea(TileLayer &activeLayer, const SelectionBuffer &selectionBuffer);

    private:
        BoundsInt getBoundsOfImpactedArea(const BoundsInt &selectionBounds, const BoundsInt &maxBounds) const;

    private:
        Vec2 m_AreaCenter;

        std::unique_ptr<TileView> m_OrigTiles;

        std::vector<int> m_OrigIndexes;
    };
} // namespace editor
} // namespace spright
