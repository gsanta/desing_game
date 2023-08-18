#include "camera.h"

namespace spright
{
namespace engine
{

    Camera::Camera(const Window * window, float near, float far, int scaleFactor)
        : m_Window(window), m_Near(near), m_Far(far), m_ScaleFactor(scaleFactor)
    {
        m_View = Mat4::lookAt(Vec3(0, 0, m_Z), Vec3(0, 0, 0), Vec3(0, 1, 0));
    }

    void Camera::translate2D(Vec2 translate)
    {
        m_Translate += translate;
        Vec3 eye(m_Translate.x, m_Translate.y, m_Z);
        Vec3 at(m_Translate.x, m_Translate.y, 0);
        m_View = Mat4::lookAt(eye, at, Vec3(0, 1, 0));
    }

    void Camera::zoom(float zoomFactor)
    {
        m_Zoom += zoomFactor;
    }

    void setScaleFactor(int scaleFactor) {

    }

    float Camera::getZoom()
    {
        return m_Zoom;
    }

    const Mat4 Camera::getProjectionMatrix() const
    {
        int twiceScaleFactor = getScaleFactor() * 2;
        return Mat4::otrthographic(-m_Window->getWidth() / twiceScaleFactor,
                                   m_Window->getWidth() / twiceScaleFactor,
                                   -m_Window->getHeight() / twiceScaleFactor,
                                   m_Window->getHeight() / twiceScaleFactor,
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
        float w = (float) m_Window->getWidth() / (float) getScaleFactor();
        float h = (float) m_Window->getHeight() / (float) getScaleFactor();

        const Mat4 mat4 = spright::maths::Mat4::scale(Vec3(1.0 / getScaleFactor(), 1.0 / getScaleFactor(), 1));
        Vec4 result = mat4 * Vec4(x, -y, 0.0f, 1.0f);

        // from the screen's top/left zero pos to center zero pos
        const Mat4 mat2 =
            spright::maths::Mat4::translation(Vec3(m_Translate.x - w / 2.0f, m_Translate.y + h / 2.0f, 0.0f));
        result = mat2 * result;

        return {result.x, result.y};
    }

    Vec2Int Camera::worldToScreenPos(float x, float y) const
    {
        Vec2 pos(x, y);
        pos -= m_Translate;

        float scaleX = m_Window->getWidth() / getScaleFactor();
        float scaleY = m_Window->getHeight() / getScaleFactor();

        pos *= Vec2(scaleX, scaleY);

        return {(int)pos.x, (int)pos.y};
    }

    float Camera::getScaleFactor() const
    {
        return ((float) m_ScaleFactor) * m_Zoom;
    }
} // namespace engine
} // namespace spright
