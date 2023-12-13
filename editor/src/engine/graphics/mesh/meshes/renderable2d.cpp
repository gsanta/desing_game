#include "renderable2d.h"

namespace spright
{
namespace engine
{
    Renderable2D::Renderable2D(int vertexCount, const Vec3 *positions, const unsigned int *colors): Mesh(vertexCount, positions, colors)
    {
    }

    Renderable2D::Renderable2D(const Bounds &bounds, unsigned int color)
        : Mesh(Vec3(bounds.getCenter(), 0), color)
    {
    }

    Renderable2D::Renderable2D(const Renderable2D &other) : Mesh(other)
    {
    }

    bool Renderable2D::isEqual(const Renderable2D &rhs) const
    {
        return m_VertexCount == rhs.m_VertexCount && m_Color == rhs.m_Color;
    }

    bool operator==(const Renderable2D &lhs, const Renderable2D &rhs)
    {
        return typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs);
    }

    bool operator!=(const Renderable2D &lhs, const Renderable2D &rhs)
    {
        return !(lhs == rhs);
    }

    const Bounds &Renderable2D::getBounds() const {
        return m_Bounds;
    }
} // namespace engine
} // namespace spright
