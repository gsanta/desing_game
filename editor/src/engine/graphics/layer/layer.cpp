#include "./layer.h"

namespace spright
{
namespace engine
{
    void Layer::render(const Camera &camera, Renderer2D& renderer)
    {
        m_Group.render(camera, renderer);
    }

    Renderable2D &Layer::add(const Renderable2D &renderable)
    {
        Renderable2D &newRenderable = m_Group.add(renderable);

        return newRenderable;
    }

    std::vector<Renderable2D *> &Layer::getRenderables()
    {
        return m_Group.getRenderables();
    }

    void Layer::clear()
    {
        m_Group.clear();
    }
} // namespace engine
} // namespace spright
