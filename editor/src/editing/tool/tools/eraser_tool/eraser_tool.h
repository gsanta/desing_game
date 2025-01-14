#pragma once

#include "../../../../engine/graphics/mesh/meshes/rect2d.h"
#include "../../../../engine/graphics/mesh/meshes/renderable2d.h"
#include "../../../../engine/scene/canvas/tile_canvas.h"
#include "../../../document/document_store.h"
#include "../../../history/document_history.h"
#include "../../context/tool_context.h"
#include "../../cursor/rectangle_cursor/rectangle_cursor.h"
#include "../../pixel_tool.h"
#include "erase_undo.h"
#include "eraser.h"

#include <memory>
#include <vector>

namespace spright
{
namespace editing
{
    using namespace spright::maths;
    using namespace spright::engine;

    class EraserTool : public PixelTool
    {
    public:
        EraserTool(int eraserSize);

        void pointerDown(const ToolContext &) override;

        void pointerMove(const ToolContext &) override;

        void setOptions(std::string json) override;

        std::string getOptions() override;

        void setEraserSize(int size);

    private:
        void erase(const ToolContext &context, bool isPointerMove);

    private:
        DocumentStore *m_documentStore;

        Eraser m_Eraser;

        int m_Size;

        bool m_IsMoveSelection = false;

        float m_NoMovementTolerance = 0.1f;
    };
} // namespace editing
} // namespace spright
