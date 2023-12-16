#pragma once

#include "../../colors.h"
#include "./mesh.h"
#include <map>

namespace spright
{
namespace engine
{
    class Box : public Mesh
    {
    public:
        enum Face
        {
            from,
            back,
            right,
            left,
            top,
            bottom
        };

        static const int NUM_VERTICES = 36;

        static const int NUM_FACES = 6;

        static const int NUM_INDEXES_PER_FACE = 6;

        static const float DEFAULT_SIZE;

        static const int DEFAULT_COLOR = COLOR_WHITE;

        Box(const Vec3 &pos = Vec3(0, 0, 0),
            float width = DEFAULT_SIZE,
            float height = DEFAULT_SIZE,
            float depth = DEFAULT_SIZE,
            unsigned int color = DEFAULT_COLOR);

        Box(const Box &other) = default;

        Box *clone() const override;

    private:
        void calcPositions();

        void calcColors();

    private:
        Vec3 m_Position;

        float m_Width;

        float m_Height;

        float m_Depth;

        int m_TileIndex = -1;

        unsigned int m_Color;

        std::map<Box::Face, unsigned int> m_FaceColors;
    };
} // namespace engine
} // namespace spright
