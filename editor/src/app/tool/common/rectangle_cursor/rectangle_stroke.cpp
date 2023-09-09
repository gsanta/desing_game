#include "./rectangle_stroke.h"

namespace spright
{
namespace editor
{
    RectangleStroke::RectangleStroke()
    {
    }

    RectangleStroke::RectangleStroke(int rectangleSize) : m_Size(rectangleSize)
    {
    }

    void editor::RectangleStroke::draw(TileLayer &drawLayer, const Vec2 &pos)
    {
        setPosition(drawLayer, pos);
    }

    void RectangleStroke::clear(TileLayer &drawLayer)
    {
        m_TopLine = nullptr;
        m_RightLine = nullptr;
        m_BottomLine = nullptr;
        m_LeftLine = nullptr;
        drawLayer.clear();
    }

    float RectangleStroke::getStrokeWidth()
    {
        return m_StrokeWidth;
    }

    void RectangleStroke::init(TileLayer &drawLayer, float tileSize)
    {
        float rectangleArea = tileSize * static_cast<float>(m_Size);

        unsigned int color = 0x800099ff;

        m_TopLine =
            &drawLayer.add(Rect2D(0, 0, tileSize, tileSize, color));
        // m_RightLine =
        //     &drawLayer.add(Rect2D(rectangleArea / 2.0f, -rectangleArea / 2.0f, m_StrokeWidth, rectangleArea, color));
        // m_BottomLine =
        //     &drawLayer.add(Rect2D(-rectangleArea / 2.0f, -rectangleArea / 2.0f, rectangleArea, m_StrokeWidth, color));
        // m_LeftLine =
        //     &drawLayer.add(Rect2D(-rectangleArea / 2.0f, -rectangleArea / 2.0f, m_StrokeWidth, rectangleArea, color));
    }

    void RectangleStroke::setPosition(TileLayer &drawLayer, const Vec2 &pos)
    {
        float halfRectangleSize = drawLayer.getTileSize() * static_cast<float>(m_Size) / 2.0f;

        float tileSize = drawLayer.getTileSize();

        unsigned int color = 0x800099ff;

        int tileIndex = drawLayer.getTileIndex(pos);
        float halfTileSize = drawLayer.getTileSize() / 2.0f;
        Vec2 centerPos = drawLayer.getCenterPos(tileIndex);

        std::cout << "pos2: " << pos.x << std::endl;

        if (!m_TopLine) {
                m_TopLine = &drawLayer.add(
                    Rect2D(Rect2D(0, 0, tileSize, tileSize, color)));
        }
            m_TopLine->setCenterPosition(centerPos);

        //     if (m_Size % 2 == 0)
        // {
        //     bottomLeft += Vec2(-halfTileSize, -halfTileSize);
        // }

        // float rectangleArea = drawLayer.getTileSize() * static_cast<float>(m_Size);

        // unsigned int color = 0xff0099ff;

        // if (!m_TopLine)
        // {
        //     m_TopLine = &drawLayer.add(
        //         Rect2D(-rectangleArea / 2.0f, rectangleArea / 2.0f, rectangleArea, m_StrokeWidth, color));
        // }
        // m_TopLine->setCenterPosition(bottomLeft + Vec2(0, halfRectangleSize));
        // if (!m_RightLine)
        // {
        //     m_RightLine = &drawLayer.add(
        //         Rect2D(rectangleArea / 2.0f, -rectangleArea / 2.0f, m_StrokeWidth, rectangleArea, color));
        // }
        // m_RightLine->setCenterPosition(bottomLeft + Vec2(halfRectangleSize, 0));
        // if (!m_BottomLine)
        // {
        //     m_BottomLine = &drawLayer.add(
        //         Rect2D(-rectangleArea / 2.0f, -rectangleArea / 2.0f, rectangleArea, m_StrokeWidth, color));
        // }
        // m_BottomLine->setCenterPosition(bottomLeft + Vec2(0, -halfRectangleSize));
        // if (!m_LeftLine)
        // {
        //     m_LeftLine = &drawLayer.add(
        //         Rect2D(-rectangleArea / 2.0f, -rectangleArea / 2.0f, m_StrokeWidth, rectangleArea, color));
        // }
        // m_LeftLine->setCenterPosition(bottomLeft + Vec2(-halfRectangleSize, 0));
    }
} // namespace editor
} // namespace spright
