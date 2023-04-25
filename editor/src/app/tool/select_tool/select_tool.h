#pragma once

#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../../engine/graphics/renderable/bounds.h"
#include "../../document/drawing.h"
#include "../common/selection_box.h"
#include "../tool/tool.h"
#include "../tool/tool_context.h"
#include "./rect_selector.h"

#include <memory>
#include <vector>

namespace spright
{
namespace editor
{
    using namespace ::spright::maths;
    using namespace ::spright::engine;
    using namespace editor;

    class SelectTool : public Tool
    {
    public:
        void pointerDown(const ToolContext &) override;

        void pointerUp(const ToolContext &) override;

        void pointerMove(const ToolContext &) override;

    private:
        void makePointSelection(const ToolContext &);

    private:
        SelectionBox m_SelectionBox;

        RectSelector m_RectSelector;

        vector<Rect2D *> m_Data;

        vector<Vec2> m_OrigPositions;

        float m_NoMovementTolerance = 0.1f;

        bool m_IsMove = false;
    };
} // namespace editor
} // namespace spright
