#include "arc_rotate_camera.h"

namespace spright
{
namespace engine
{
    ArcRotateCamera::ArcRotateCamera(const BoundsInt &screenBounds, float near, float far, int zoomFactor)
        : Camera(screenBounds, near, far, zoomFactor)
    {
    }

    void ArcRotateCamera::setPos(const Vec3 &pos)
    {
        m_Pos = pos;

        m_View = Mat4::lookAt(pos, Vec3(0, 0, 0), Vec3(0, 1, 0));
    }

    Vec2 ArcRotateCamera::screenToWorldPos(float x, float y) const
    {
        return {0, 0};
    }

    Vec2Int ArcRotateCamera::worldToScreenPos(float x, float y) const
    {
        return {0, 0};
    }

    Camera *ArcRotateCamera::clone() const
    {
        return new ArcRotateCamera(*this);
    }


    void ArcRotateCamera::updateProjectionMatrix() const
    {
        int twiceScaleFactor = getScaleFactor() * 2.0f;
        m_Proj = Mat4::orthographic(-m_ScreenBounds.getWidth() / (twiceScaleFactor + 0.4f),
                                    m_ScreenBounds.getWidth() / (twiceScaleFactor + 0.4f),
                                    -m_ScreenBounds.getHeight() / (twiceScaleFactor + 0.4f),
                                    m_ScreenBounds.getHeight() / (twiceScaleFactor + 0.4f),
                                    m_Near,
                                    m_Far);
    }
} // namespace engine
} // namespace spright
