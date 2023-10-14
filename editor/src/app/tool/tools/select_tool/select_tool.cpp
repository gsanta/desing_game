#include "select_tool.h"

#include "../rotate_tool/rotate_tool.h"
#include "../shear_tool/shear_tool.h"

namespace spright
{
namespace editor
{
    SelectTool::SelectTool()
        : Tool("select", std::make_shared<RectangleCursor>(1)), m_BoxSelector(m_SelectionBuffer),
          m_WandSelector(m_SelectionBuffer)
    {
        m_SelectionMover = std::make_unique<SelectionMover>();
    }

    void SelectTool::pointerDown(const ToolContext &context)
    {
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();

        int tileIndex = toolLayer.getTileIndex(context.pointer.curr);

        m_Phase = toolLayer.getAtTileIndex(tileIndex) == nullptr ? selection : manipulation;

        if (m_Phase == selection)
        {
            startSelection(context);
        }
        else
        {
            startManipulation(context);
        }
    }

    void SelectTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isDown)
        {
            return;
        }

        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        if (m_Phase == selection)
        {
            moveSelection(context);
        }
        else
        {
            moveManipulation(context);
        }
    }

    void SelectTool::pointerUp(const ToolContext &context)
    {
        // TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();
        // TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();

        // recalcTileIndexesAndBounds(activeLayer, toolLayer);

        if (m_Phase == selection)
        {
            endSelection(context);
        }
        else
        {
            endManipulation(context);
        }

        m_Phase = selection;
    }

    void SelectTool::startManipulation(const ToolContext &context)
    {
        if (m_Mode == manip_rotate)
        {
            context.tools->getRotateTool().pointerDown(context);
        }
        else if (m_Mode == manip_shear)
        {
            context.tools->getShearTool().pointerDown(context);
        }
    }

    void SelectTool::moveManipulation(const ToolContext &context)
    {
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();

        switch (m_Mode)
        {
        case manip_rotate:
            context.tools->getRotateTool().pointerMove(context);
            break;
        case manip_shear:
            context.tools->getShearTool().pointerMove(context);
            break;
        case manip_move:
        default:
            m_SelectionMover->move(toolLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
            m_SelectionMover->move(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
            break;
        }
    }

    void SelectTool::endManipulation(const ToolContext &context)
    {
        if (m_Mode == manip_rotate)
        {
            context.tools->getRotateTool().pointerUp(context);
        }
        else if (m_Mode == manip_shear)
        {
            context.tools->getShearTool().pointerUp(context);
        }

        TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();

        recalcTileIndexesAndBounds(tempLayer, toolLayer);
    }

    void SelectTool::startSelection(const ToolContext &context)
    {
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();

        m_SelectionBuffer.clear();
        toolLayer.clear();
    }

    void SelectTool::moveSelection(const ToolContext &context)
    {
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        if (m_SelectionType == rectangle)
        {
            if (!m_BoxSelector.isSelectionChanged(toolLayer,
                                                  context.pointer.curr,
                                                  context.pointer.prev,
                                                  context.pointer.down))
            {
                return;
            }

            toolLayer.clear();
            m_BoxSelector.select(activeLayer, toolLayer, context.pointer.curr, context.pointer.down);
        }
        else if (m_SelectionType == wand)
        {
            // no op
        }
    }

    void SelectTool::endSelection(const ToolContext &context)
    {
        TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

        bool removeSelection = context.pointer.downDelta().length() < m_NoMovementTolerance && m_SelectionType != wand;

        if (removeSelection)
        {
            tile_operation_copy_all(tempLayer, activeLayer);

            tempLayer.clear();
            toolLayer.clear();
            m_SelectionBuffer.clear();
        } else {
            if (m_SelectionType == wand)
            {
                m_WandSelector.select(activeLayer, toolLayer, context.pointer.curr, context.pointer.down);
            }

            tile_operation_copy_indexes(activeLayer, tempLayer, m_SelectionBuffer.getTileIndexes());
            tile_operation_remove_indexes(activeLayer, m_SelectionBuffer.getTileIndexes());

            recalcTileIndexesAndBounds(tempLayer, toolLayer);
        }
    }

    void SelectTool::setMode(SelectionManipulationMode mode)
    {
        m_Mode = mode;
    }

    void SelectTool::setSelectionType(SelectionType selectionType)
    {
        m_SelectionType = selectionType;
    }

    void SelectTool::setSelection(const std::vector<int> &indexes, Drawing &drawing, TileLayer &layer)
    {
        TileLayer &toolLayer = drawing.getToolLayer();

        m_SelectionBuffer.setTileIndexes(indexes, layer);

        const BoundsInt &bounds = m_SelectionBuffer.getTileBounds();

        m_BoxSelector.select(layer,
                             toolLayer,
                             toolLayer.getCenterPos(bounds.getBottomLeft()),
                             toolLayer.getCenterPos(bounds.getTopRight() + -1));
    }

    void SelectTool::recalcTileIndexesAndBounds(TileLayer &tempLayer, TileLayer &toolLayer)
    {
        std::vector<int> currentTileIndexes = m_SelectionBuffer.getTileIndexes();
        std::vector<int> newTileIndexes;

        for (int tileIndex : m_SelectionBuffer.getTileIndexes())
        {
            Rect2D *tile = tempLayer.getAtTileIndex(tileIndex);
            if (tile != nullptr)
            {
                newTileIndexes.push_back(tempLayer.updateTileIndex(tile));
            }
        }

        m_SelectionBuffer.setTileIndexes(newTileIndexes, tempLayer);

        for (Rect2D *tile : toolLayer.getTiles())
        {
            toolLayer.updateTileIndex(tile);
        }
    }

    SelectionBuffer &SelectTool::getSelectionBuffer()
    {
        return m_SelectionBuffer;
    }
} // namespace editor
} // namespace spright
