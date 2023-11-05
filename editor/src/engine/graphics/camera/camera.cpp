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

    void Camera::translate2D(Vec2 delta)
    {
        setTranslate(m_Translate + delta);
    }

    void Camera::setTranslate(Vec2 translate)
    {
        m_Translate = translate;
        Vec3 eye(m_Translate.x, m_Translate.y, m_Z);
        Vec3 at(m_Translate.x, m_Translate.y, 0);
        m_View = Mat4::lookAt(eye, at, Vec3(0, 1, 0));
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

    void Camera::zoomToFit(const Bounds &bounds)
    {
        float windowRatio = m_ScreenBounds.getWidth() / m_ScreenBounds.getHeight();

        float zoom = m_Zoom;

        if (bounds.getWidth() / windowRatio > bounds.getHeight())
        {
            float width = bounds.getWidth();
            zoom = m_ScreenBounds.getWidth() / width / m_ZoomFactor;
        }
        else
        {
            float height = bounds.getHeight();
            zoom = m_ScreenBounds.getHeight() / height / m_ZoomFactor;
        }

        setZoom(zoom);
        setTranslate(bounds.getCenter());
    }

    float Camera::getZoom()
    {
        return m_Zoom;
    }

    const Mat4 Camera::getProjectionMatrix() const
    {
        int twiceScaleFactor = getScaleFactor() * 2.0f;
        return Mat4::otrthographic(-m_ScreenBounds.getWidth() / (twiceScaleFactor + 0.4f),
                                   m_ScreenBounds.getWidth() / (twiceScaleFactor + 0.4f),
                                   -m_ScreenBounds.getHeight() / (twiceScaleFactor + 0.4f),
                                   m_ScreenBounds.getHeight() / (twiceScaleFactor + 0.4f),
                                   m_Near,
                                   m_Far);
    }

    const Mat4 &Camera::getViewMatrix() const
    {
        return m_View;
    }

    Vec2 Camera::getCenter2D()
    {
        return m_Translate;
    }

    Vec2 Camera::screenToWorldPos(float x, float y) const
    {
        float w = (float)m_ScreenBounds.getWidth() / getScaleFactor();
        float h = (float)m_ScreenBounds.getHeight() / getScaleFactor();

        const Mat4 scaleMatrix =
            spright::maths::Mat4::scale(Vec3(1.0f / getScaleFactor(), 1.0f / getScaleFactor(), 1.0f));

        // from the screen's top/left zero pos to center zero pos
        const Mat4 translateMatrix =
            spright::maths::Mat4::translation(Vec3(m_Translate.x - w / 2.0f, m_Translate.y + h / 2.0f, 0.0f));

        Vec4 result = translateMatrix * scaleMatrix * Vec4(x, -y, 0.0f, 1.0f);

        return {result.x, result.y};
    }

    Vec2Int Camera::worldToScreenPos(float x, float y) const
    {
        float scaleX = m_ScreenBounds.getWidth() / getScaleFactor();
        float scaleY = m_ScreenBounds.getHeight() / getScaleFactor();

        const Mat4 translateMatrix = spright::maths::Mat4::translation(
            Vec3(-m_Translate.x + scaleX / 2.0f, -m_Translate.y - scaleY / 2.0f, 0.0f));

        const Mat4 scaleMatrix = spright::maths::Mat4::scale(Vec3(getScaleFactor(), getScaleFactor(), 1));

        Vec4 result = scaleMatrix * translateMatrix * Vec4(x, y, 0.0f, 1.0f);

        return {(int)result.x, (int)-result.y};
    }

    void Camera::setScreenBounds(const BoundsInt &screenBounds)
    {
        m_ScreenBounds = screenBounds;
    }

    float Camera::getScaleFactor() const
    {
        return ((float)m_ZoomFactor) * m_Zoom;
    }
} // namespace engine
} // namespace spright
