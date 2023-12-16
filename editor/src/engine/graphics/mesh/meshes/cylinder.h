#pragma once
#include "./mesh.h"

namespace spright
{
namespace engine
{
    class Cylinder : public Mesh
    {
    public:
        static const int DEFAULT_COLOR = COLOR_WHITE;

        Cylinder(const Vec3 &pos = Vec3(0, 0, 0),
                 float height = 2.0,
                 float diameterTop = 1.0,
                 float diameterBottom = 1.0,
                 int tessellation = 8,
                 unsigned int color = DEFAULT_COLOR);

    private:
        void calcPositions();

        void calcColors();

    private:
        Vec3 m_Pos;

        float m_Height;

        float m_DiameterTop;

        float m_DiameterBottom;

        int m_Tessellation;

        unsigned int m_Color;
    };
} // namespace engine
} // namespace spright
