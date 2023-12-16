#include "canvas_border_component.h"

namespace spright
{
namespace editing
{
    CanvasBorderComponent::CanvasBorderComponent(Canvas *canvas) : m_Canvas(canvas)
    {
    }

    CanvasBorderComponent::CanvasBorderComponent(const CanvasBorderComponent &other)
    {
    }

    void CanvasBorderComponent::onAddedToCanvas(Canvas &canvas)
    {
        m_Canvas = &canvas;
        Bounds bounds = canvas.getBounds();

        float halfWidth = bounds.getWidth() / 2.0;
        float halfHeight = bounds.getHeight() / 2.0;
        float minX = bounds.minX;
        float minY = bounds.minY;
        float maxX = bounds.maxX;
        float maxY = bounds.maxY;

        float borderWidth = 0.2;

        Rect2D rects[] = {
            Rect2D(0, halfHeight + borderWidth / 2.0, bounds.getWidth(), borderWidth, COLOR_WHITE),                     // top
            Rect2D(halfWidth + borderWidth / 2.0, 0, borderWidth, bounds.getHeight(), COLOR_WHITE), // right
            Rect2D(0, -halfHeight - borderWidth / 2.0, bounds.getWidth(), borderWidth, COLOR_WHITE),      // bottom
            Rect2D(-halfWidth - borderWidth / 2.0, 0, borderWidth, bounds.getHeight(), COLOR_WHITE) // left
        };

        for (int i = 0; i < 4; i++)
        {
            Renderable2D &mesh = canvas.getGizmoLayer().add(rects[i]);
            mesh.setName(m_MeshNames[i]);
        }
    }

    void CanvasBorderComponent::setSelected(bool isSelected)
    {
        for (int i = 0; i < 4; i++)
        {
            Renderable2D *mesh = m_Canvas->getGizmoLayer().getByName(m_MeshNames[i]);

            Rect2D *rect = dynamic_cast<Rect2D *>(mesh);

            rect->setColor(isSelected ? COLOR_SELECTED : COLOR_UNSELECTED);
        }
    }

    CanvasBorderComponent *CanvasBorderComponent::clone(Canvas &canvas)
    {
        return new CanvasBorderComponent(&canvas);
    }
} // namespace editing
} // namespace spright
