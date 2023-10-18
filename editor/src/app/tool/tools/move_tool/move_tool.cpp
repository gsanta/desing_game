#include "./move_tool.h"

namespace spright
{
namespace editor
{
    MoveTool::MoveTool() : Tool("move")
    {
    }

    void MoveTool::pointerDown(const ToolContext &context)
    {
        const TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();

        m_Undo.reset(new TileUndo(*context.doc.document, context.tools));

        const SelectionBuffer &selectionBuffer = context.tools->getSelectTool().getSelectionBuffer();

        for (int index : selectionBuffer.getTileIndexes()) {
            m_Undo->addTile(std::make_shared<Rect2D>(*tempLayer.getAtTileIndex(index)), nullptr);
        }

        m_Undo->setPrevSelection(selectionBuffer.getTileIndexes());
    }


    void MoveTool::pointerMove(const ToolContext &context)
    {
        TileLayer &toolLayer = context.doc.activeDrawing->getToolLayer();
        TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();

        m_SelectionMover.move(toolLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
        m_SelectionMover.move(tempLayer, context.pointer.curr, context.pointer.prev, context.pointer.down);
    }

    void MoveTool::pointerUp(const ToolContext &context)
    {
        const TileLayer &tempLayer = context.doc.activeDrawing->getTempLayer();

        const SelectionBuffer &selectionBuffer = context.tools->getSelectTool().getSelectionBuffer();

        for (int index : selectionBuffer.getTileIndexes())
        {
            m_Undo->addTile(nullptr, std::make_shared<Rect2D>(*tempLayer.getAtTileIndex(index)));
        }

        m_Undo->setNewSelection(selectionBuffer.getTileIndexes());

        context.doc.document->getHistory()->add(std::make_shared<TileUndo>(*m_Undo.get()));
    }
} // namespace editor
} // namespace spright
