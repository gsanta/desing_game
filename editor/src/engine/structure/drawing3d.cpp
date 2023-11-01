#include "drawing3d.h"

namespace spright
{
namespace engine
{
    Drawing3d::Drawing3d(const std::string &uuid, const Bounds &bounds, const Layer &decorationLayer, std::shared_ptr<Renderer2D> renderer)
        : Canvas(uuid, bounds, decorationLayer), m_Renderer(renderer)
    {
    }

    Renderable3d &Drawing3d::add(const Renderable3d &renderable)
    {
        Renderable3d &newRenderable = m_Group.add(renderable);

        return newRenderable;
    }

    void Drawing3d::render(const Camera &camera) {
        m_Group.render(camera, *m_Renderer);
    }

} // namespace engine
} // namespace spright
