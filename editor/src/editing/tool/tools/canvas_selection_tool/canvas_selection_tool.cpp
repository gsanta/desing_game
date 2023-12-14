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

        Canvas *canvas = document->getActiveCanvas();

        if (canvas)
        {
            canvas->getComponent<CanvasBorderComponent>()->setSelected(false);
        }

        for (size_t i = 0; i < document->getCanvasCount(); i++)
        {
            if (document->getCanvas(i)->getBounds().contains(context.pointer.curr.x, context.pointer.curr.y))
            {
                document->setActiveCanvas(*document->getCanvas(i));
                break;
            }
        }

        if (document->getActiveCanvas())
        {
            document->getActiveCanvas()->getComponent<CanvasBorderComponent>()->setSelected(true);
        }
    }
} // namespace editing
} // namespace spright
