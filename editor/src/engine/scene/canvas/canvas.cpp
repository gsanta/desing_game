#include "./canvas.h"

namespace spright
{
namespace engine
{
    Canvas::Canvas(const std::string &uuid, std::string type, const Bounds &bounds, const Renderer2D &renderer)
        : m_Uuid(uuid), m_Type(type), m_Bounds(bounds), m_Renderer(std::unique_ptr<Renderer2D>(renderer.clone()))
    {
    }

    Canvas::Canvas(const Canvas &other)
        : m_Bounds(other.m_Bounds), m_Type(other.m_Type), m_GizmoLayer(other.m_GizmoLayer), m_Uuid(other.m_Uuid)
    {
        m_Renderer.reset(other.m_Renderer->clone());

        for (const auto &entry : other.m_Components)
        {
            m_Components[entry.first] = std::shared_ptr<CanvasComponent>(entry.second->clone(*this));
        }
    }

    Canvas &Canvas::operator=(const Canvas &other)
    {
        m_Bounds = other.m_Bounds;
        m_GizmoLayer = other.m_GizmoLayer;
        m_Uuid = other.m_Uuid;
        m_Type = other.m_Type;

        m_Renderer.reset(other.m_Renderer->clone());

        m_Components.clear();
        for (const auto &entry : other.m_Components)
        {
            m_Components[entry.first] = std::shared_ptr<CanvasComponent>(entry.second->clone(*this));
        }

        return *this;
    }

    const Bounds &Canvas::getBounds() const
    {
        return m_Bounds;
    }

    const std::string Canvas::getUuid() const
    {
        return m_Uuid;
    }

    void Canvas::render(const Camera &camera, Canvas::RenderTarget target)
    {
    }

    Renderer2D &Canvas::getRenderer()
    {
        return *m_Renderer;
    }

    Group<Renderable2D> &Canvas::getGizmoLayer()
    {
        return m_GizmoLayer;
    }

    const std::string &Canvas::getType() const
    {
        return m_Type;
    }
} // namespace engine
} // namespace spright
