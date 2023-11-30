
#pragma once

#include "../../../../engine/scene/containers/tile_layer.h"
#include "../../../../engine/graphics/renderable/rect2d.h"
#include "../../../core/history/undoable.h"
#include "../../../document/document.h"

namespace spright
{
namespace editor
{
    class EraseUndo : public Undoable
    {
    public:
        EraseUndo(Document &document);

        void undo(Document &document) const override;

        void redo(Document &document) const override;

        void addTile(std::shared_ptr<Rect2D> rect);

    private:
        std::vector<std::shared_ptr<Rect2D>> m_Rects;

        size_t m_TileLayerPos;

        size_t m_FramePos;

        std::string m_DrawingId;
    };

} // namespace editor
} // namespace spright
