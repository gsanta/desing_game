#pragma once

#include "../vec3.h"
#include "bounds.h"

namespace spright
{
namespace maths
{
    struct Bounds3
    {

        float minX;

        float maxX;

        float minY;

        float maxY;

        float minZ;

        float maxZ;

        Bounds3(float x1, float y1, float z1, float x2, float y2, float z2);

        Bounds3(const Vec3 &coord1, const Vec3 &coord2);

        Bounds3() = default;

        operator Bounds() const;

        Vec3 min() const;

        Vec3 max() const;

        float width() const;

        float height() const;

        float depth() const;

        Vec3 center() const;
    };
} // namespace maths
} // namespace spright
