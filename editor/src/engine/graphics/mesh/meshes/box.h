#pragma once

#include "../../colors.h"
#include "./mesh.h"

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
        void calcPositions(const Vec3 &pos, float width, float height, float depth);
    };
} // namespace engine
} // namespace spright
