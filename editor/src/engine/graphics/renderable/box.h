#pragma once

#include "../colors.h"
#include "../mesh/meshes/mesh.h"

namespace spright
{
namespace engine
{
    class Box : public Mesh
    {
    public:
        Box(const Vec3 &pos, float width, float height, float depth, unsigned int color);

        Box(const Box& other) = default;

        Box *clone() const override;

    private:
        void calcPositions(const Vec3 &pos, float width, float height, float depth);
    };
} // namespace engine
} // namespace spright
