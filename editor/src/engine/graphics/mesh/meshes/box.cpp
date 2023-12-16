#include "box.h"

namespace spright
{
namespace engine
{
    const float Box::DEFAULT_SIZE = 1.0f;

    Box::Box(const Vec3 &pos, float width, float height, float depth, unsigned int color)
        : Mesh(36), m_Position(pos), m_Width(width), m_Height(height), m_Depth(depth), m_Color(color)
    {
        calcPositions();
        calcColors();
    }

    Box *Box::clone() const
    {
        return new Box(*this);
    }

    void Box::calcPositions()
    {
        float halfWidth = m_Width / 2.0;
        float halfHeight = m_Height / 2.0;
        float halfDepth = m_Depth / 2.0;

        Vec3 corners[8];
        corners[0] = Vec3(m_Position.x - halfWidth, m_Position.y - halfHeight, m_Position.z + halfDepth); // bottom left front
        corners[1] = Vec3(m_Position.x - halfWidth, m_Position.y + halfHeight, m_Position.z + halfDepth); // top left front
        corners[2] = Vec3(m_Position.x + halfWidth, m_Position.y + halfHeight, m_Position.z + halfDepth); // top right front
        corners[3] = Vec3(m_Position.x + halfWidth, m_Position.y - halfHeight, m_Position.z + halfDepth); // bottom right front
        corners[4] = Vec3(m_Position.x - halfWidth, m_Position.y - halfHeight, m_Position.z - halfDepth); // bottom left back
        corners[5] = Vec3(m_Position.x - halfWidth, m_Position.y + halfHeight, m_Position.z - halfDepth); // top left back
        corners[6] = Vec3(m_Position.x + halfWidth, m_Position.y + halfHeight, m_Position.z - halfDepth); // top right back
        corners[7] = Vec3(m_Position.x + halfWidth, m_Position.y - halfHeight, m_Position.z - halfDepth); // bottom right back

        m_Positions[0] = corners[0]; // front
        m_Positions[1] = corners[1];
        m_Positions[2] = corners[2];
        m_Positions[3] = corners[0];
        m_Positions[4] = corners[2];
        m_Positions[5] = corners[3];

        m_Positions[6] = corners[7]; // back
        m_Positions[7] = corners[6];
        m_Positions[8] = corners[5];
        m_Positions[9] = corners[7];
        m_Positions[10] = corners[5];
        m_Positions[11] = corners[4];

        m_Positions[12] = corners[3]; // right
        m_Positions[13] = corners[2];
        m_Positions[14] = corners[6];
        m_Positions[15] = corners[3];
        m_Positions[16] = corners[6];
        m_Positions[17] = corners[7];

        m_Positions[18] = corners[4]; // left
        m_Positions[19] = corners[5];
        m_Positions[20] = corners[1];
        m_Positions[21] = corners[4];
        m_Positions[22] = corners[1];
        m_Positions[23] = corners[0];

        m_Positions[24] = corners[1]; // top
        m_Positions[25] = corners[5];
        m_Positions[26] = corners[6];
        m_Positions[27] = corners[1];
        m_Positions[28] = corners[6];
        m_Positions[29] = corners[2];

        m_Positions[30] = corners[7]; // bottom
        m_Positions[31] = corners[4];
        m_Positions[32] = corners[0];
        m_Positions[33] = corners[7];
        m_Positions[34] = corners[0];
        m_Positions[35] = corners[3];

        m_Bounds = Bounds3(corners[0].x, corners[0].y, corners[0].z, corners[6].x, corners[6].y, corners[6].z);
    }

    void Box::calcColors() {
        for (int i = 0; i < Box::NUM_VERTICES; i++)
        {
            m_Colors[i] = m_Color;
        }

        for (int faceIndex = 0; faceIndex < Box::NUM_FACES; faceIndex++)
        {
            auto it = m_FaceColors.find(static_cast<Box::Face>(faceIndex));
            if (it != m_FaceColors.end())
            {
                unsigned int color = it->second;

                int posStart = faceIndex * Box::NUM_INDEXES_PER_FACE;

                std::fill(m_Colors + posStart, m_Colors + posStart + Box::NUM_INDEXES_PER_FACE, color);
            }
        }
    }
} // namespace engine
} // namespace spright
