#include "./tile_undo.h"

namespace spright
{
namespace editor
{

    void TileUndo::undo(AbstractEditor &editor) const
    {
        TileLayer &tileLayer =
            editor.getActiveDocument().getDrawings()[m_DrawingPos].getFrames()[m_FramePos].getLayers()[m_TileLayerPos];

        for (std::shared_ptr<Rect2D> rect : m_NewList)
        {
            tileLayer.remove(*rect);
        }

        for (std::shared_ptr<Rect2D> rect : m_PrevList)
        {
            tileLayer.add(*rect);
        }
    }

    void TileUndo::redo(AbstractEditor &editor) const
    {
        TileLayer &tileLayer =
            editor.getActiveDocument().getDrawings()[m_DrawingPos].getFrames()[m_FramePos].getLayers()[m_TileLayerPos];

        for (std::shared_ptr<Rect2D> rect : m_NewList)
        {
            tileLayer.add(*rect);
        }
    }

    void TileUndo::setTileLayer(size_t drawingPos, size_t framePos, size_t tileLayerPos)
    {
        m_DrawingPos = drawingPos;
        m_FramePos = framePos;
        m_TileLayerPos = tileLayerPos;
    }

    void TileUndo::addTile(std::shared_ptr<Rect2D> prevRect, std::shared_ptr<Rect2D> newRect)
    {
        if (prevRect)
        {
            m_PrevList.push_back(prevRect);
        }

        if (newRect)
        {
            m_NewList.push_back(newRect);
        }
    }
} // namespace editor
} // namespace spright
