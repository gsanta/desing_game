#include "./rotate_tool.h"

namespace spright
{
namespace editor
{
    RotateTool::RotateTool() : Tool("rotate")
    {
        m_Timer = Timer::getTimer();
    }

    void RotateTool::pointerDown(const ToolContext &toolContext)
    {
        m_Timer->reset();

        m_OrigIndexes.clear();

        TileLayer &activeLayer = toolContext.doc.activeDrawing->getActiveLayer();

        m_OrigTiles.reset(new TileView(activeLayer.getBounds(), activeLayer.getTileSize()));

        const BoundsInt &selectionBounds = toolContext.tool.selectionBuffer->getTileBounds();

        Vec2Int center = selectionBounds.getCenter();
        m_RotationCenter = activeLayer.getCenterPos(center);

        tile_operation_copy_area(activeLayer, *m_OrigTiles, selectionBounds, selectionBounds.getBottomLeft());

        for (Rect2D *tile : m_OrigTiles->getTiles()) {
            m_OrigIndexes.push_back(m_OrigTiles->getTileIndex(tile->getCenterPosition2d()));
        }
    }

    void RotateTool::pointerMove(const ToolContext &toolContext)
    {
        if (m_Timer->elapsed() > 500)
        {
            m_Timer->reset();

            TileLayer &activeLayer = toolContext.doc.activeDrawing->getActiveLayer();

            const std::vector<int> &oldIndexes = toolContext.tools->getSelectTool().getSelectionBuffer().getTileIndexes();

            for (int index : oldIndexes) {
                activeLayer.removeAt(index);
            }

            tile_operation_copy_all(*m_OrigTiles, activeLayer);

            toolContext.tools->getSelectTool().setSelection(m_OrigIndexes, *toolContext.doc.activeDrawing);

            const BoundsInt &selectionBounds = toolContext.tool.selectionBuffer->getTileBounds();

            Vec2 dir = toolContext.pointer.curr - m_RotationCenter;

            double angle = std::atan2(dir.y, dir.x) - 3.141 / 2.0;

            std::cout << "rotation: " << (angle / 3.14 * 180) << std::endl;

            std::vector<int> newIndexes =
                rotate(toolContext.doc.activeDrawing->getActiveLayer(),
                       BoundsInt(selectionBounds.getBottomLeft(), selectionBounds.getTopRight()),
                       angle);

            toolContext.tools->getSelectTool().setSelection(newIndexes, *toolContext.doc.activeDrawing);
        }
    }

    void RotateTool::pointerUp(const ToolContext &toolContext)
    {
    }

    void RotateTool::setRotationInRad(float rad)
    {
        m_RotateInRad = rad;
    }

    void RotateTool::execute(ToolContext &toolContext)
    {
        const BoundsInt &selectionBounds = toolContext.tool.selectionBuffer->getTileBounds();

        std::vector<int> newIndexes = rotate(toolContext.doc.activeDrawing->getActiveLayer(),
                                             BoundsInt(selectionBounds.getBottomLeft(), selectionBounds.getTopRight()),
                                             m_RotateInRad);

        toolContext.tools->getSelectTool().setSelection(newIndexes, *toolContext.doc.activeDrawing);
    }
} // namespace editor
} // namespace spright
