#include "./canvas.h"

namespace spright
{
namespace engine
{
    Canvas::Canvas(const std::string &uuid,
                   const Bounds &bounds,
                   const Renderer2D &renderer,
                   const Layer &decorationLayer)
        : m_Uuid(uuid), m_Bounds(bounds), m_Renderer(std::unique_ptr<Renderer2D>(renderer.clone())),
          m_DecorationLayer(decorationLayer)
    {
    }

    Canvas::Canvas(const Canvas &other)
        : m_Bounds(other.m_Bounds), m_DecorationLayer(other.m_DecorationLayer),
          m_Uuid(other.m_Uuid)
    {
        m_Renderer.reset(other.m_Renderer->clone());

        if (other.m_Camera) {
            m_Camera.reset(new Camera(*other.m_Camera));
        }
    }

    Canvas &Canvas::operator=(const Canvas &other) {
        m_Bounds = other.m_Bounds;
        m_DecorationLayer = other.m_DecorationLayer;
        m_Uuid = other.m_Uuid;

        m_Renderer.reset(other.m_Renderer->clone());

        if (other.m_Camera) {
            m_Camera.reset(new Camera(*other.m_Camera));
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

    Canvas *Canvas::clone() const
    {
        return new Canvas(m_Uuid, m_Bounds, *m_Renderer, m_DecorationLayer);
    }

    void Canvas::render(const Camera &camera, Canvas::RenderTarget target)
    {
    }

    Renderer2D &Canvas::getRenderer()
    {
        return *m_Renderer;
    }

    Layer &Canvas::getDecorationLayer()
    {
        return m_DecorationLayer;
    }

    void Canvas::setCamera(const Camera &camera) {
        m_Camera.reset(new Camera(camera));
    }
} // namespace engine
} // namespace spright
