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

        float minX = bounds.minX;
        float minY = bounds.minY;
        float maxX = bounds.maxX;
        float maxY = bounds.maxY;

        Rect2D rects[] = {
            Rect2D(minX, maxY, maxX - minX, 0.2, COLOR_WHITE),       // top
            Rect2D(maxX, minY, 0.2, maxY - minY, COLOR_WHITE),       // right
            Rect2D(minX, minY - 0.2, maxX - minX, 0.2, COLOR_WHITE), // bottom
            Rect2D(minX - 0.2, minY, 0.2, maxY - minY, COLOR_WHITE)  // left
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
            Renderable2D *rect = m_Canvas->getGizmoLayer().getByName(m_MeshNames[i]);

            rect->setColor(isSelected ? COLOR_SELECTED : COLOR_UNSELECTED);
        }
    }

    CanvasBorderComponent *CanvasBorderComponent::clone(Canvas &canvas)
    {
        return new CanvasBorderComponent(&canvas);
    }
} // namespace editing
} // namespace spright
