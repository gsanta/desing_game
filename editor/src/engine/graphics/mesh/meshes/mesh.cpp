#include "mesh.h"

namespace spright
{
namespace engine
{
    Mesh::Mesh(int vertexCount)
    {
        createArrays(vertexCount);
    }

    Mesh::Mesh(int vertexCount, const Vec3 *positions) : Mesh(vertexCount, positions, nullptr)
    {
    }

    Mesh::Mesh(int vertexCount, const Vec3 *positions, const unsigned int *colors)
    {
        m_VertexCount = vertexCount;
        createArrays(vertexCount);

        std::copy_n(positions, vertexCount, m_Positions);
        if (colors != nullptr)
        {
            std::copy_n(colors, vertexCount, m_Colors);
        }

        calcBounds();
    }

    Mesh::Mesh(const Mesh &other) : m_VertexCount(other.m_VertexCount), m_Name(other.m_Name), m_Bounds(other.m_Bounds)
    {
        createArrays(other.m_VertexCount);
        std::copy_n(other.m_Positions, m_VertexCount, m_Positions);
        std::copy_n(other.m_Normals, m_VertexCount, m_Normals);
        std::copy_n(other.m_Colors, m_VertexCount, m_Colors);
    }

    Mesh &Mesh::operator=(const Mesh &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] m_Positions;
        delete[] m_Normals;
        delete[] m_Colors;

        createArrays(other.m_VertexCount);
        m_VertexCount = other.m_VertexCount;
        m_Name = other.m_Name;
        m_Bounds = other.m_Bounds;

        std::copy_n(other.m_Positions, m_VertexCount, m_Positions);
        std::copy_n(other.m_Normals, m_VertexCount, m_Normals);
        std::copy_n(other.m_Colors, m_VertexCount, m_Colors);
        return *this;
    }

    Mesh::~Mesh()
    {
        delete[] m_Positions;
        delete[] m_Normals;
        delete[] m_Colors;
    }

    const Vec3 *Mesh::getPositions() const
    {
        return m_Positions;
    }

    const Bounds3 &Mesh::getBounds3() const
    {
        return m_Bounds;
    }

    void Mesh::submit(Renderer2D &renderer) const
    {
        VertexData *&buffer = renderer.getBuffer();
        const Mat4 *transformation = renderer.getTransformation();

        for (int i = 0; i < m_VertexCount; i++)
        {
            buffer->vertex = *transformation * m_Positions[i];
            buffer->tid = 0.0f;
            buffer->color = m_Colors[i];
            buffer++;
        }

        int indexCount = m_VertexCount + m_VertexCount / 2;

        renderer.setIndexCount(renderer.getIndexCount() + m_VertexCount);
    }

    void Mesh::translate(const Vec3 &amount)
    {
        for (int i = 0; i < m_VertexCount; i++)
        {
            m_Positions[i].add(amount);
        }
        calcBounds();
    }

    bool Mesh::operator==(const Mesh &rhs)
    {
        return m_Positions[0] == rhs.m_Positions[0];
    }

    bool Mesh::operator!=(const Mesh &rhs)
    {
        return !(*this == rhs);
    }

    Mesh *Mesh::clone() const
    {
        return new Mesh(*this);
    }

    void Mesh::setName(const std::string &name)
    {
        m_Name = name;
    }

    const std::string &Mesh::getName() const
    {
        return m_Name;
    }

    void Mesh::calcNormals()
    {
        for (int i = 0; i < m_VertexCount; i += 3)
        {
            Vec3 normal = (m_Positions[i] - m_Positions[i + 1]).cross(m_Positions[i] - m_Positions[i + 2]);

            m_Normals[i] = normal;
            m_Normals[i + 1] = normal;
            m_Normals[i + 2] = normal;
        }
    }

    void Mesh::calcBounds()
    {
        Vec3 min = m_Positions[0];
        Vec3 max = m_Positions[0];

        for (int i = 1; i < m_VertexCount; i++)
        {
            for (int xyz = 0; xyz < 3; xyz++)
            {
                if (min[xyz] > m_Positions[i][xyz])
                {
                    min[xyz] = m_Positions[i][xyz];
                }
                else if (min[xyz] < m_Positions[i][xyz])
                {
                    max[xyz] = m_Positions[i][xyz];
                }
            }
        }

        m_Bounds = Bounds3(min, max);
    }

    void Mesh::createArrays(int positionsCount)
    {
        m_VertexCount = positionsCount;
        m_Positions = new Vec3[positionsCount];
        m_Normals = new Vec3[positionsCount];
        m_Colors = new int[positionsCount];
    }
} // namespace engine
} // namespace spright
