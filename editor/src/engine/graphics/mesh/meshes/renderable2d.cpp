#include "renderable2d.h"

namespace spright
{
namespace engine
{
    Renderable2D::Renderable2D(int vertexCount) : Mesh(vertexCount)
    {
    }

    Renderable2D::Renderable2D(int vertexCount, const Vec3 *positions, const unsigned int *colors)
        : Mesh(vertexCount, positions, colors)
    {
    }

    Renderable2D::Renderable2D(const Renderable2D &other) : Mesh(other)
    {
    }

    bool Renderable2D::isEqual(const Renderable2D &rhs) const
    {
        return m_VertexCount == rhs.m_VertexCount;
    }

    bool operator==(const Renderable2D &lhs, const Renderable2D &rhs)
    {
        return typeid(lhs) == typeid(rhs) && lhs.isEqual(rhs);
    }

    bool operator!=(const Renderable2D &lhs, const Renderable2D &rhs)
    {
        return !(lhs == rhs);
    }

    const Bounds Renderable2D::getBounds() const
    {
        // return m_Bounds;
        return Bounds(m_Bounds.minX, m_Bounds.minY, m_Bounds.maxX, m_Bounds.maxY);
    }
} // namespace engine
} // namespace spright
