//
// This class can select and move 2d sprites within a rectanglular area.
//

#pragma once
#include "../../../engine/graphics/layer/tileLayer.h"
#include "../../../engine/graphics/renderable/bounds.h"
#include "../../../engine/graphics/renderable/rect2d.h"

#include <vector>

namespace spright
{
namespace editor
{
    using namespace maths;
    using namespace engine;

    class RectSelector
    {
    public:
        RectSelector(TileLayer &tileLayer);

        void setSelection(const Vec2 &pos1, const Vec2 &pos2);

        void moveSelectionWith(const Vec2 &delta);

        const std::vector<Rect2D *> getSelection() const;

    private:
        TileLayer &m_Layer;

        std::vector<Rect2D *> m_Sprites;

        std::vector<Vec2> m_OrigPositions;
    };
} // namespace editor
} // namespace spright
