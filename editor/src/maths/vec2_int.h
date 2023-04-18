#pragma once

namespace spright
{
namespace maths
{
    class Vec2Int
    {
    public:
        Vec2Int();

        Vec2Int(int x, int y);

        Vec2Int operator+(const Vec2Int &right);

        Vec2Int operator-(const Vec2Int &right);

        friend bool operator==(const Vec2Int &, const Vec2Int &);

        friend bool operator!=(const Vec2Int &, const Vec2Int &);

    public:
        int x;
        int y;
    };
} // namespace maths
} // namespace spright
