#include "bounds.h"

namespace spright { namespace engine {
    Bounds::Bounds(float bottomLeftX, float bottomLeftY, float width, float height)
    {
        minX = bottomLeftX;
        minY = bottomLeftY;
        maxX = minX + width;
        maxY = minY + height;
    }

    Bounds::Bounds() : Bounds(0, 0, 0, 0) {}

    Bounds Bounds::createWithPositions(float minX, float maxX, float minY, float maxY) {
        return Bounds(minX, minY, maxX - minX, maxY - minY);
    }

    Vec2 Bounds::getCenter() const
    {
        return Vec2(minX + (maxX - minX) / 2.0, minY + (maxY - minY) / 2.0);
    }

    float Bounds::getWidth() const {
        return maxX - minX;
    }

    float Bounds::getHeight() const {
        return maxY - minY;
    }

    void Bounds::setSize(float newWidth, float newHeight)
    {
        float deltaWidth = (newWidth - getWidth()) / 2.0f;

        minX -= deltaWidth;
        maxX += deltaWidth;


        float deltaHeight = (newHeight - getHeight()) / 2.0f;

        maxY += deltaHeight;
        minY -= deltaHeight;
    }


    bool operator==(const Bounds& lhs, const Bounds& rhs) {
        return lhs.minX == rhs.minX && lhs.maxX == rhs.maxX && lhs.minY == rhs.minY && lhs.maxY == rhs.maxY;
    }

    bool operator!=(const Bounds& lhs, const Bounds& rhs) {
        return !(lhs == rhs);
    }
}}

