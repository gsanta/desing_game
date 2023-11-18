#include "box.h"

namespace spright
{
namespace engine
{
    Box::Box(const Vec3 &pos, float width, float height, float depth, unsigned int color)
        : Mesh(24, color)
    {
        calcPositions(pos, width, height, depth);
    }

    Box *Box::clone() const
    {
        return new Box(*this);
    }

    void Box::calcPositions(const Vec3 &pos, float width, float height, float depth)
    {
        float halfWidth = width / 2.0;
        float halfHeight = height / 2.0;
        float halfDepth = depth / 2.0;

        Vec3 corners[8];
        corners[0] = Vec3(pos.x - halfWidth, pos.y - halfHeight, pos.z + halfDepth); // bottom left front
        corners[1] = Vec3(pos.x - halfWidth, pos.y + halfHeight, pos.z + halfDepth); // top left front
        corners[2] = Vec3(pos.x + halfWidth, pos.y + halfHeight, pos.z + halfDepth); // top right front
        corners[3] = Vec3(pos.x + halfWidth, pos.y - halfHeight, pos.z + halfDepth); // bottom right front
        corners[4] = Vec3(pos.x - halfWidth, pos.y - halfHeight, pos.z - halfDepth); // bottom left back
        corners[5] = Vec3(pos.x - halfWidth, pos.y + halfHeight, pos.z - halfDepth); // top left back
        corners[6] = Vec3(pos.x + halfWidth, pos.y + halfHeight, pos.z - halfDepth); // top right back
        corners[7] = Vec3(pos.x + halfWidth, pos.y - halfHeight, pos.z - halfDepth); // bottom right back

        m_Positions[0] = corners[0]; // front
        m_Positions[1] = corners[1];
        m_Positions[2] = corners[2];
        m_Positions[3] = corners[3];

        m_Positions[4] = corners[7]; // back
        m_Positions[5] = corners[6];
        m_Positions[6] = corners[5];
        m_Positions[7] = corners[4];

        m_Positions[8] = corners[3]; // right
        m_Positions[9] = corners[2];
        m_Positions[10] = corners[6];
        m_Positions[11] = corners[7];

        m_Positions[12] = corners[4]; // left
        m_Positions[13] = corners[5];
        m_Positions[14] = corners[1];
        m_Positions[15] = corners[0];

        m_Positions[16] = corners[1]; // top
        m_Positions[17] = corners[5];
        m_Positions[18] = corners[6];
        m_Positions[19] = corners[2];

        m_Positions[20] = corners[7]; // bottom
        m_Positions[21] = corners[4];
        m_Positions[22] = corners[0];
        m_Positions[23] = corners[3];
    }
} // namespace engine
} // namespace spright
