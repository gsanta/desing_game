#include "../../document/drawing.h"

namespace spright
{
namespace editor
{
    /**
     * This class represents an exported sprite sheet within the document.
     * A sprite sheet can be exported from a regular drawing with multiple frames and unfolds all of the frames
     * onto a single-frame drawing.
    */
    class SpriteSheet {
    public:
        SpriteSheet(DocumentFactory documentFactory);

        void createSpriteSheet(Drawing &drawing);

    };
}
}
