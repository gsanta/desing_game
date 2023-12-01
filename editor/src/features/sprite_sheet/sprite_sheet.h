#pragma once
#include "../../engine/scene/canvas/tile_canvas.h"
#include "../../editing/algorithm/tile_operations.h"
#include "../../editing/document/document.h"
#include "../../editing/document/factory/document_factory.h"

#include <memory.h>

namespace spright
{
namespace editor
{
    /**
     * This class represents an exported sprite sheet within the document.
     * A sprite sheet can be exported from a regular drawing with multiple frames and unfolds all of the frames
     * onto a single-frame drawing.
    */
    class SpriteSheet
    {
    public:
        SpriteSheet(std::shared_ptr<DocumentFactory> documentFactory, Document *document);

        Drawing &generateSpriteSheet(Drawing &drawing);

    private:
        std::shared_ptr<DocumentFactory> m_DocumentFactory;

        Document *m_Document;
    };
} // namespace editor
} // namespace spright
