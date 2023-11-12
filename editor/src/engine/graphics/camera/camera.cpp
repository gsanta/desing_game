#include "camera.h"

namespace spright
{
namespace engine
{
    Camera::Camera(const BoundsInt &screenBounds, float near, float far, int zoomFactor)
        : m_ScreenBounds(screenBounds), m_Near(near), m_Far(far), m_ZoomFactor(zoomFactor)
    {
        m_View = Mat4::lookAt(Vec3(0, 0, m_Z), Vec3(0, 0, 0), Vec3(0, 1, 0));
    }

    void Camera::setZoom(float zoom)
    {
        m_Zoom = zoom;
    }

    void Camera::zoomIn()
    {
        m_Zoom *= 1.05;
    }

    void Camera::zoomOut()
    {
        m_Zoom /= 1.05;
    }

    float Camera::getZoom()
    {
        return m_Zoom;
    }

    const Mat4 &Camera::getViewMatrix() const
    {
        return m_View;
    }

    const Mat4 &Camera::getProjectionMatrix() const
    {
        updateProjectionMatrix();
        return m_Proj;
    }

    void Camera::setScreenBounds(const BoundsInt &screenBounds)
    {
        m_ScreenBounds = screenBounds;
    }

    float Camera::getScaleFactor() const
    {
        return ((float)m_ZoomFactor) * m_Zoom;
    }
}
}
