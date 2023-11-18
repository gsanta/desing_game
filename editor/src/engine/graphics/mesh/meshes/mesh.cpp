#include "mesh.h"

namespace spright
{
namespace engine
{
    Mesh::Mesh(const Vec3 &pos, unsigned int color) : m_Color(color)
    {
        m_Position = pos;
    }

    Mesh::Mesh(int positionCount, unsigned int color)
    {
        m_PositionsCount = positionCount;

        m_Positions = new Vec3[m_PositionsCount];
    }

    Mesh::Mesh(const Mesh &other)
        : m_Color(other.m_Color), m_Position(other.m_Position), m_PositionsCount(other.m_PositionsCount)
    {
        m_Positions = new Vec3[m_PositionsCount];
        for (int i = 0; i < m_PositionsCount; ++i)
        {
            m_Positions[i] = other.m_Positions[i];
        }
    }

    Mesh &Mesh::operator=(const Mesh &other)
    {
        if (this != &other)
        {
            m_Color = other.m_Color;
            m_Position = other.m_Position;

            delete[] m_Positions;

            m_PositionsCount = other.m_PositionsCount;

            m_Positions = new Vec3[m_PositionsCount];
            for (int i = 0; i < m_PositionsCount; ++i)
            {
                m_Positions[i] = other.m_Positions[i];
            }
        }
        return *this;
    }

    Mesh::~Mesh()
    {
        delete[] m_Positions;
    }

    const Vec3 &Mesh::getPosition() const
    {
        return m_Position;
    }

    void Mesh::setPosition(const Vec3 &pos)
    {
        m_Position = pos;
    }

    void Mesh::submit(Renderer2D &renderer) const
    {
        VertexData *&buffer = renderer.getBuffer();
        const Mat4 *transformation = renderer.getTransformation();

        for (int i = 0; i < m_PositionsCount; i++)
        {
            buffer->vertex = *transformation * m_Positions[i];
            buffer->tid = 0.0f;
            buffer->color = m_Color;
            buffer++;
        }

        // every four positions creates two triangles, reusing two positions
        int indexCount = m_PositionsCount + m_PositionsCount / 2;

        renderer.setIndexCount(renderer.getIndexCount() + indexCount);
    }

    bool Mesh::operator==(const Mesh &rhs)
    {
        return rhs.m_Color == m_Color && rhs.m_Position == m_Position;
    }

    bool Mesh::operator!=(const Mesh &rhs)
    {
        return !(*this == rhs);
    }
} // namespace engine
} // namespace spright
