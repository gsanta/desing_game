#pragma once

#include "../../../../engine/graphics/mesh/meshes/rect2d.h"
#include "../../../../engine/graphics/mesh/meshes/renderable2d.h"
#include "../../../../engine/scene/canvas/canvas.h"
#include "../../../../engine/scene/canvas/canvas_component.h"

namespace spright
{
namespace editing
{
    using namespace engine;

    class CanvasBorderComponent : public CanvasComponent
    {
    public:
        const static int COLOR_SELECTED = COLOR_BLUE;

        const static int COLOR_UNSELECTED = COLOR_WHITE;

        CanvasBorderComponent() = default;

        CanvasBorderComponent(Canvas *canvas);

        CanvasBorderComponent(const CanvasBorderComponent &other);

        void onAddedToCanvas(Canvas &canvas) override;

        void setSelected(bool isSelected);

        CanvasBorderComponent *clone(Canvas &canvas) override;

    private:
        Canvas *m_Canvas;

        std::string m_MeshNames[4] = {"top-border", "right-border", "bottom-border", "left-border"};
    };

} // namespace editing
} // namespace spright
