#include "./rect_selector.h"

namespace spright
{
namespace editor
{

    RectSelector::RectSelector(TileLayer &tileLayer) : m_Layer(tileLayer)
    {
    }

    void RectSelector::setSelection(const Vec2 &pos1, const Vec2 &pos2)
    {
        m_Sprites.clear();
        m_OrigPositions.clear();

        float startX = pos1.x < pos2.x ? pos1.x : pos2.x;
        float endX = pos1.x < pos2.x ? pos2.x : pos1.x;
        float startY = pos1.y < pos2.y ? pos1.y : pos2.y;
        float endY = pos1.y < pos2.y ? pos2.y : pos1.y;

        Bounds selectionBounds = Bounds::createWithPositions(startX, endX, startY, endY);

        auto it = m_Layer.getRenderables().begin();
        while (it != m_Layer.getRenderables().end())
        {
            Vec2 pos = (*it)->getCenterPosition2d();

            if (selectionBounds.contains(pos.x, pos.y))
            {
                Rect2D *sprite = *it;
                m_Sprites.push_back(sprite);
                m_OrigPositions.push_back(Vec2(sprite->getPosition().x, sprite->getPosition().y));
            }
            ++it;
        }
    }

    void RectSelector::moveSelectionWith(const Vec2 &delta)
    {
        for (int i = 0; i < m_Sprites.size(); i++)
        {
            Rect2D *sprite = m_Sprites[i];

            sprite->translate(delta);
        }

        for (Rect2D *sprite : m_Sprites)
        {
            Vec2Int tilePos = m_Layer.getTilePos(sprite->getPosition2d());
            int newTileIndex = m_Layer.getTileIndex(tilePos.x, tilePos.y);
            m_Layer.updateTileIndex(sprite, newTileIndex);
        }
    }

    const std::vector<Rect2D *> RectSelector::getSelection() const
    {
        return m_Sprites;
    }
} // namespace editor
} // namespace spright
