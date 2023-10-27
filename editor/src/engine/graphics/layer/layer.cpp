#include "./layer.h"

namespace spright
{
namespace engine
{
    Layer::Layer(std::shared_ptr<Renderer2D> renderer) : m_Renderer(renderer)
    {
    }

    void Layer::render(const Camera &camera)
    {
        m_Group.render(camera, *m_Renderer.get());
    }

    Renderable2D &Layer::add(const Renderable2D &renderable)
    {
        Renderable2D &newRenderable = m_Group.add(renderable);

        return newRenderable;
    }
} // namespace engine
} // namespace spright
