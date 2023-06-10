#include "temp_rect_drawer.h"

namespace spright
{
namespace editor
{

    void TempRectDrawer::draw(TileLayer &tileLayer, Vec2 from, Vec2 to, int color)
    {
        drawFilled(tileLayer, from, to, color);
    }

    void TempRectDrawer::reset()
    {
        m_FilledRect = nullptr;
    }

    const Bounds &TempRectDrawer::getBounds() const
    {
        return m_FilledRect->getBounds();
    }

    void TempRectDrawer::drawFilled(TileLayer &tileLayer, Vec2 from, Vec2 to, int color)
    {
        if (m_FilledRect == nullptr)
        {
            m_FilledRect = &tileLayer.add(Rect2D(0, 0, 0.1f, 0.1f, color));
        }

        maths::Vec2 downTilePos = tileLayer.getCenterPos(from);
        maths::Vec2 currTilePos = tileLayer.getCenterPos(to);

        float left = downTilePos.x < currTilePos.x ? downTilePos.x : currTilePos.x;
        float right = downTilePos.x > currTilePos.x ? downTilePos.x : currTilePos.x;
        float bottom = downTilePos.y < currTilePos.y ? downTilePos.y : currTilePos.y;
        float top = downTilePos.y > currTilePos.y ? downTilePos.y : currTilePos.y;

        float halfTileSize = tileLayer.getTileSize() / 2.0f;
        m_FilledRect->setPosition(maths::Vec2(left - halfTileSize, bottom - halfTileSize));
        m_FilledRect->setSize(maths::Vec2(right - left, top - bottom));
    }
} // namespace editor
} // namespace spright
