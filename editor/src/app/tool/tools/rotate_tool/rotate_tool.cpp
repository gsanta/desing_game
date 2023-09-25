#include "./shear_tool.h"

namespace spright
{
namespace editor
{
    RotateTool::RotateTool() : Tool("shear")
    {
    }

    void RotateTool::execute(ToolContext &toolContext)
    {
        const BoundsInt &selectionBounds = toolContext.tool.selectionBuffer->getTileBounds();

        rotate(toolContext.doc.activeDrawing->getActiveLayer(),
               BoundsInt(selectionBounds.getBottomLeft(), selectionBounds.getTopRight()),
               1.5708f);

        // toolContext.tool.selectionBuffer->setTileIndexes(newIndexes, toolContext.doc.activeDrawing->getActiveLayer());

        // toolContext.tools->getSelectTool().setSelection(newIndexes, *toolContext.doc.activeDrawing);
    }
} // namespace editor
} // namespace spright
