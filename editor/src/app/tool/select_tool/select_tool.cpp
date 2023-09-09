#include "select_tool.h"

namespace spright
{
namespace editor
{

    SelectTool::SelectTool()
        : Tool("select", std::make_shared<RectangleCursor>(1, true)),
          m_SelectionBuffer(std::make_shared<SelectionBuffer>())
    {
        m_BoxSelector = std::make_unique<BoxSelector>(m_SelectionBuffer);
        m_SelectionMover = std::make_unique<SelectionMover>(m_SelectionBuffer);
    }

    void SelectTool::pointerDown(const ToolContext &context)
    {
        if (context.doc.hasActiveDrawing())
        {
            TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();
            TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();

            int tileIndex = foregroundLayer.getTileIndex(context.pointer.curr);

            m_IsMove = foregroundLayer.getAtTileIndex(tileIndex) != nullptr;
        }
    }

    void SelectTool::pointerUp(const ToolContext &context)
    {
        if (!context.doc.hasActiveDrawing())
        {
            return;
        }

        if (!m_IsMove)
        {
            if (context.pointer.downDelta().length() < m_NoMovementTolerance)
            {
                TileLayer &foregroundLayer = context.doc.activeDrawing->getForegroundLayer();

                m_BoxSelector->clear();
                context.doc.activeDrawing->getState().clearBounds();
            }
            else
            {
                // Vec2 bottomLeft = m_BoxSelector->getBounds().getBottomLeft();
                // Vec2 topRight = m_BoxSelector->getBounds().getTopRight();

                // context.doc.activeDrawing->getState().setBounds(Bounds(bottomLeft, topRight));
            }
        }
    }

    void SelectTool::pointerMove(const ToolContext &context)
    {
        if (!context.pointer.isLeftButtonDown())
        {
            return;
        }

        TileLayer &tempLayer = context.doc.activeDrawing->getForegroundLayer();
        TileLayer &activeLayer = context.doc.activeDrawing->getActiveLayer();
        if (m_IsMove)
        {

            m_SelectionMover->move(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);

            m_SelectionMover->move(activeLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
        }
        else
        {
            if (m_BoxSelector->isSelectionChanged(tempLayer,
                                                  context.pointer.curr,
                                                  context.pointer.prev,
                                                  context.pointer.down))
            {
                tempLayer.clear();
                m_BoxSelector->select(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
                fillTempLayer(tempLayer);
            }
        }
    }

    void SelectTool::setSelectedTiles(std::vector<int> indexes)
    {
        m_SelectionBuffer->setTileIndexes(std::move(indexes));
    }


    std::shared_ptr<SelectionBuffer> SelectTool::getSelectionBuffer()
    {
        return m_SelectionBuffer;
    }

    void SelectTool::fillTempLayer(TileLayer &tempLayer)
    {
        float tileSize = tempLayer.getTileSize();
        unsigned int color = 0x800099ff;

        for (int index : m_SelectionBuffer->getTileIndexes())
        {
            Vec2 bottomLeft = tempLayer.getBottomLeftPos(index);
            Rect2D rect(bottomLeft.x, bottomLeft.y, tileSize, tileSize, color);

            tempLayer.add(rect);
        }
    }
} // namespace editor
} // namespace spright
