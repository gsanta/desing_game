#include "drawing3d.h"

namespace spright
{
namespace engine
{
    Drawing3d::Drawing3d(const std::string &uuid,
                         const Bounds &bounds,
                         const Layer &decorationLayer,
                         const Renderer2D &renderer)
        : Canvas(uuid, bounds, renderer, decorationLayer)
    {
    }

    Drawing3d &Drawing3d::operator=(const Drawing3d &other)
    {
        Canvas::operator=(other);

        m_Group = other.m_Group;
        return *this;
    }

    Renderable &Drawing3d::add(const Renderable &renderable)
    {
        Renderable &newRenderable = m_Group.add(renderable);

        Vec3 center = getBounds().getCenter();
        newRenderable.setPosition(newRenderable.getPosition() + Vec3(center.x, center.y, 0));

        return newRenderable;
    }

    Drawing3d *Drawing3d::clone() const
    {
        return new Drawing3d(*this);
    }

    void Drawing3d::render(const Camera &camera, Canvas::RenderTarget target)
    {
        m_Group.render(camera, getRenderer());

        if (target == Screen)
        {
            getDecorationLayer().render(camera, getRenderer());
        }
    }

} // namespace engine
} // namespace spright
