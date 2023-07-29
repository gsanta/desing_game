#pragma once

#include "./undoable.h"

namespace spright
{
namespace editor
{
    class TileUndo : Undoable
    {
    public:
        void undo(AbstractEditor &editor) const override;

        void redo(AbstractEditor &editor) const override;

        void setTileLayer(size_t drawingPos, size_t framePos, size_t tileLayerPos);

        void addTile(std::shared_ptr<Rect2D> prevRect, std::shared_ptr<Rect2D> newRect);

    private:
        std::vector<std::shared_ptr<Rect2D>> m_PrevList;

        std::vector<std::shared_ptr<Rect2D>> m_NewList;

        size_t m_TileLayerPos;

        size_t m_FramePos;

        size_t m_DrawingPos;
    };

} // namespace editor
} // namespace spright
