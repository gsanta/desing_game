#include "canvas_selection_tool.h"

namespace spright
{
namespace editing
{
    CanvasSelectionTool::CanvasSelectionTool() : PixelTool("canvas_selection")
    {
    }

    void CanvasSelectionTool::pointerDown(const ToolContext &context)
    {
        Document *document = context.doc.document;

        document->getActiveCanvas()->getDecorationLayer().clear();

        for (size_t i = 0; i < document->getCanvasCount(); i++)
        {
            if (document->getCanvas(i)->getBounds().contains(context.pointer.curr.x, context.pointer.curr.y))
            {
                document->setActiveCanvas(*document->getCanvas(i));
                break;
            }
        }

        Canvas *activeCanvas = document->getActiveCanvas();
        Bounds bounds = activeCanvas->getBounds();

        float minX = bounds.minX;
        float minY = bounds.minY;
        float maxX = bounds.maxX;
        float maxY = bounds.maxY;

        activeCanvas->getDecorationLayer().clear();

        Rect2D top(minX, maxY, maxX - minX, 0.2, COLOR_BLUE);
        Rect2D right(maxX, minY, 0.2, maxY - minY, COLOR_BLUE);
        Rect2D bottom(minX, minY - 0.2, maxX - minX, 0.2, COLOR_BLUE);
        Rect2D left(minX - 0.2, minY, 0.2, maxY - minY, COLOR_BLUE);

        activeCanvas->getDecorationLayer().add(top);
        activeCanvas->getDecorationLayer().add(right);
        activeCanvas->getDecorationLayer().add(bottom);
        activeCanvas->getDecorationLayer().add(left);
    }
} // namespace editing
} // namespace spright
