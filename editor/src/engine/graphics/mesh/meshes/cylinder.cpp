#include "cylinder.h"

namespace spright
{
namespace engine
{
    Cylinder::Cylinder(const Vec3 &pos,
                       float height,
                       float diameterTop,
                       float diameterBottom,
                       int tessellation,
                       unsigned int color)
        : Mesh(tessellation * 6), m_Pos(pos), m_Height(height), m_DiameterTop(diameterTop),
          m_DiameterBottom(diameterBottom), m_Tessellation(tessellation), m_Color(color)
    {
        calcPositions();
        calcColors();
    }

    void Cylinder::calcPositions()
    {
        int tessellation = m_Tessellation;
        float diameterTop = m_DiameterTop;
        float diameterBottom = m_DiameterBottom;
        float height = m_Height;
        int subdivisions = 1;
        float arc = 1.0;

        float angleStep = (M_PI * 2 * arc) / tessellation;

        Vec3 bottomPositions[tessellation];
        Vec3 topPositions[tessellation];

        for (int i = 0; i <= subdivisions; i++)
        {
            float h = i / subdivisions;
            float radius = (h * (diameterTop - diameterBottom) + diameterBottom) / 2;

            for (int j = 0; j < tessellation; j++)
            {
                float angle = j * angleStep;

                float x = std::cos(-angle) * radius;
                float y = -height / 2 + h * height;
                float z = std::sin(-angle) * radius;

                if (i == 0)
                {
                    bottomPositions[j] = Vec3(x, y, z) + m_Pos;
                }
                else
                {
                    topPositions[j] = Vec3(x, y, z) + m_Pos;
                }
            }
        }

        int counter = 0;
        for (int i = 0; i < tessellation; i++)
        {
            int iPlus1 = i == tessellation - 1 ? 0 : i + 1;

            m_Positions[counter++] = bottomPositions[i];
            m_Positions[counter++] = topPositions[i];
            m_Positions[counter++] = topPositions[iPlus1];
            m_Positions[counter++] = bottomPositions[i];
            m_Positions[counter++] = topPositions[iPlus1];
            m_Positions[counter++] = bottomPositions[iPlus1];
        }
    }

    void Cylinder::calcColors() {
        for (int i = 0; i < m_VertexCount; i++)
        {
            m_Colors[i] = m_Color;
        }
    }
} // namespace engine
} // namespace spright
