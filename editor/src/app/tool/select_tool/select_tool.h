#pragma once

#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../document/document_store.h"
#include "../../document/drawing.h"
#include "../common/rectangle_cursor/rectangle_cursor.h"
#include "../tool/tool.h"
#include "../tool/tool_context.h"
#include "./box_selector.h"
#include "./rect_selector.h"
#include "./selection_buffer.h"
#include "./selection_mover.h"

#include <memory>
#include <vector>
#include <limits>

namespace spright
{
namespace editor
{
    using namespace ::spright::maths;
    using namespace ::spright::engine;

    class SelectTool : public Tool
    {
    public:
        SelectTool();

        void pointerDown(const ToolContext &) override;

        void pointerUp(const ToolContext &) override;

        void pointerMove(const ToolContext &) override;

        void setSelectedTiles(std::vector<int> indexes);

        std::shared_ptr<SelectionBuffer> getSelectionBuffer();

        const Bounds &getSelectionBounds() const;

    private:
        void fillTempLayer(TileLayer &tempLayer);

        void recalcTileIndexesAndBounds(TileLayer &layer);

    private:
        DocumentStore *m_DocumentStore;

        std::shared_ptr<SelectionBuffer> m_SelectionBuffer;

        std::unique_ptr<BoxSelector> m_BoxSelector;

        std::unique_ptr<SelectionMover> m_SelectionMover;

        RectSelector m_RectSelector;

        vector<Vec2> m_OrigPositions;

        Bounds m_SelectionBounds;

        float m_NoMovementTolerance = 0.1f;

        bool m_IsMove = false;
    };
} // namespace editor
} // namespace spright
