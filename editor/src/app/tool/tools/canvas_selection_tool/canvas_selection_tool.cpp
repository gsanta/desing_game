#include "canvas_selection_tool.h"

namespace spright
{
namespace editor
{
    CanvasSelectionTool::CanvasSelectionTool() : Tool("canvas_selection")
    {
    }

    void CanvasSelectionTool::pointerDown(const ToolContext &context)
    {
        Document *document = context.doc.document;

        for (size_t i = 0; i < document->getDrawings().size(); i++)
        {
            if (document->getDrawings()[i].getBounds().contains(context.pointer.curr.x, context.pointer.curr.y))
            {
                document->setActiveDrawing(i);
                break;
            }
        }

        Drawing *activeDrawing = document->getActiveDrawing();
        if (activeDrawing)
        {
            activeDrawing->getDecorationLayer().clear();

            Bounds bounds = activeDrawing->getBounds();

            Rect2D rect(bounds.getBottomLeft().x - 0.5, bounds.getBottomLeft().y, 0.5, bounds.getHeight(), COLOR_BLUE);
            activeDrawing->getDecorationLayer().add(rect);
        }
    }
} // namespace editor
} // namespace spright
