#include "rect2d.h"

namespace spright
{
namespace engine
{
    Rect2D::Rect2D(float x, float y, float width, float height, unsigned int color)
        : Renderable2D(NUM_VERTICES), m_Color(color), m_Size(Vec2(width, height))
    {
        calcPositions(Vec3(x, y, 0));
        calcColors();
        calcBounds();
    }

    Rect2D::Rect2D(const Rect2D &rect2d)
        : Renderable2D(rect2d), m_Size(rect2d.m_Size), m_Color(rect2d.m_Color)
    {
    }

    bool Rect2D::isEqual(const Renderable2D &rhs) const
    {
        Rect2D rect2d = dynamic_cast<const Rect2D &>(rhs);

        return Renderable2D::isEqual(rect2d) && m_Size == rect2d.m_Size;
    }


    int Rect2D::getTileIndex()
    {
        return m_TileIndex;
    }

    void Rect2D::setTileIndex(int index)
    {
        m_TileIndex = index;
    }

    Vec3 Rect2D::getPosition()
    {
        return getBounds3().center();
    }

    Vec2 Rect2D::getPosition2d() const
    {
        return getBounds().getCenter();
    }

    void Rect2D::setSize(Vec2 size)
    {
        this->m_Size = size;
        calcPositions(getBounds3().center());
        calcBounds();
    }

    Vec2 Rect2D::getSize()
    {
        return m_Size;
    }

    void Rect2D::setPosition2d(Vec2 position)
    {
        Vec3 currPos = getBounds3().center();
        calcPositions(Vec3(position.x, position.y, currPos.z));
        calcBounds();
    }

    const unsigned int Rect2D::getColor() const
    {
        return m_Color;
    }

    void Rect2D::setColor(unsigned int color)
    {
        m_Color = color;
        calcColors();
    }

    bool Rect2D::contains(Vec2 point)
    {
        const Bounds &bounds = getBounds();
        return point.x > bounds.minX && point.x < bounds.maxX && point.y > bounds.minY && point.y < bounds.maxY;
    }

    void Rect2D::setZ(float z)
    {
        Vec3 position = getPosition();
        position.z = z;
        calcPositions(position);
        calcBounds();
    }

    nlohmann::json Rect2D::getJson()
    {
        Vec3 pos = getBounds3().center();
        nlohmann::json json = {
            {"posX", pos.x},
            {"posY", pos.y},
            {"posZ", pos.z},
            {"sizeX", m_Size.x},
            {"sizeY", m_Size.y},
        };

        return json;
    }

    Rect2D *Rect2D::clone() const
    {
        return new Rect2D(*this);
    }

    void Rect2D::calcPositions(const Vec3& pos)
    {
        float x = pos.x - m_Size.x / 2.0;
        float y = pos.y - m_Size.y / 2.0;
        float z = pos.z;
        float width = m_Size.x;
        float height = m_Size.y;

        Vec3 corners[8];
        corners[0] = Vec3(x, y, z);                  // bottom left
        corners[1] = Vec3(x, y + height, z);         // top left
        corners[2] = Vec3(x + width, y + height, z); // top right
        corners[3] = Vec3(x + width, y, z);          // bottom right

        m_Positions[0] = corners[0];
        m_Positions[1] = corners[1];
        m_Positions[2] = corners[2];
        m_Positions[3] = corners[0];
        m_Positions[4] = corners[2];
        m_Positions[5] = corners[3];
    }

    void Rect2D::calcColors()
    {
        for (int i = 0; i < NUM_VERTICES; i++)
        {
            m_Colors[i] = m_Color;
        }
    }
} // namespace engine
} // namespace spright
