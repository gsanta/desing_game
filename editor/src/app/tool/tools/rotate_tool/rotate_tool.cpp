#include "./rotate_tool.h"

namespace spright
{
namespace editor
{
    RotateTool::RotateTool() : Tool("rotate")
    {
    }

    void RotateTool::setRotationInRad(float rad)
    {
        m_RotateInRad = rad;
    }

    void RotateTool::execute(ToolContext &toolContext)
    {
        const BoundsInt &selectionBounds = toolContext.tool.selectionBuffer->getTileBounds();

        rotate(toolContext.doc.activeDrawing->getActiveLayer(),
               BoundsInt(selectionBounds.getBottomLeft(), selectionBounds.getTopRight()),
               m_RotateInRad);
    }
} // namespace editor
} // namespace spright
