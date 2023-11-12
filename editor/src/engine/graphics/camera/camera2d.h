#pragma once

#include "camera.h"

namespace spright
{
namespace engine
{
    using namespace ::spright::maths;

    class Camera2d : public Camera
    {
    public:
        Camera2d(const BoundsInt &screenBounds, float near = -10.0f, float far = 10.0f, int zoomFactor = 17);

        void lookAt(const Vec3 &from);

        void translate2D(Vec2 delta);

        void setTranslate(Vec2 translate);

        void zoomToFit(const Bounds &bounds);

        void setDirection(const Vec3 &direction);

        Vec2 getCenter2D();

        Vec2 screenToWorldPos(float x, float y) const override;

        Vec2Int worldToScreenPos(float x, float y) const override;

        // Arc rotate camera

        void front();

        void back();

        void left();

        void right();

        void top();

        void bottom();

        Camera *clone() const override;

    protected:
        void updateProjectionMatrix() const override;

    private:
        Vec3 m_Direction;

        // arc rotate camera

        float m_Radius = 5.0;
    };
} // namespace engine
} // namespace spright
