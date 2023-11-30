#pragma once
#include "../../document/document_store.h"
#include "../../../engine/scene/canvas/tile_canvas.h"

namespace spright
{
namespace editor
{
    struct DocumentInfo
    {
        Drawing *prevDrawing = nullptr;

        Drawing *activeDrawing = nullptr;

        Document *document = nullptr;

        bool hasActiveDrawing() const;

        bool hasPrevDrawing() const;

        bool isLeavingDrawing() const;

        void setActiveDocumentChanging(bool isChanging);

        void setActiveDrawing(Drawing *activeDrawing);

    private:
        bool m_IsActiveDrawingChanging;
    };
} // namespace editor
} // namespace spright
