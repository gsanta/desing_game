#pragma once

#include "../../../engine/graphics/renderable/rect2d.h"
#include "../../document/document_store.h"
#include "../../document/drawing.h"
#include "../common/selection_box.h"
#include "../tool/tool.h"
#include "../tool/tool_context.h"

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
        SelectTool(DocumentStore *documentHandler);

        void pointerDown(const ToolContext &) override;

        void pointerUp(const ToolContext &) override;

        void pointerMove(const ToolContext &) override;

    private:
        void makeSelection(const ToolContext &);

        void makePointSelection(const ToolContext &);

        void moveSelection(Vec2 tileDelta, Drawing *activeDrawing);

    private:
        DocumentStore *m_DocumentStore;

        std::unique_ptr<SelectionBox> m_SelectionBox;

        vector<Rect2D *> m_Data;

        vector<Vec2> m_OrigPositions;

        float m_NoMovementTolerance = 0.1f;

        bool m_IsMove = false;
    };
} // namespace editor
} // namespace spright
