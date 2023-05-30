#pragma once

namespace spright
{
namespace engine
{

    class BoundsInt
    {
    public:
        int minX;

        int maxX;

        int minY;

        int maxY;

        BoundsInt();

        BoundsInt(int minX, int maxX, int minY, int maxY);

        friend bool operator==(const BoundsInt &, const BoundsInt &);

        friend bool operator!=(const BoundsInt &, const BoundsInt &);

        int getWidth() const;

        int getHeight() const;
    };

} // namespace engine
} // namespace spright
