#pragma once

#include "camera.h"

namespace spright
{
namespace engine
{
    using namespace ::spright::maths;

    class ArcRotateCamera : public Camera
    {
    public:
        ArcRotateCamera(const BoundsInt &screenBounds, float near = -10.0f, float far = 10.0f, int zoomFactor = 17);

        void setPos(const Vec3 &pos);

        Vec2 screenToWorldPos(float x, float y) const override;

        Vec2Int worldToScreenPos(float x, float y) const override;

        Camera *clone() const override;

    private:
        void updateProjectionMatrix() const override;

    private:
        Vec3 m_Pos;

        Vec3 m_Front;

        Vec3 m_Up = Vec3(0.0, 1.0, 0.0);
    };
} // namespace engine
} // namespace spright
